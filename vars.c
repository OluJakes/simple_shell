#include "shell.h"

/**
 * chn_del - test if current char in buffer is a chain delimiter
 * @inf: the parameter struct
 * @buff: the char buffer
 * @pos: address of current position in buff
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int chn_del(info_t *inf, char *buff, size_t *pos)
{
	size_t z = *pos;

	if (buff[z] == '|' && buff[z + 1] == '|')
	{
		buff[z] = 0;
		z++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buff[z] == '&' && buff[z + 1] == '&')
	{
		buff[z] = 0;
		z++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buff[z] == ';') /* found end of this command */
	{
		buff[z] = 0; /* replace semicolon with null */
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = z;
	return (1);
}

/**
 * chn_chk - checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @buff: the char buffer
 * @pos: address of current position in buff
 * @st_pos: starting position in buff
 * @len: length of buff
 *
 * Return: Void
 */
void chn_chk(info_t *inf, char *buff, size_t *pos, size_t st_pos, size_t len)
{
	size_t z = *pos;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buff[st_pos] = 0;
			z = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buff[st_pos] = 0;
			z = len;
		}
	}

	*pos = z;
}

/**
 * repc_alias - replaces an aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int repc_alias(info_t *inf)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		inf->argv[0] = p;
	}
	return (1);
}

/**
 * repc_vars - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int repc_vars(info_t *inf)
{
	int a = 0;
	list_t *node;

	for (a = 0; inf->argv[a]; a++)
	{
		if (inf->argv[a][0] != '$' || !inf->argv[a][1])
			continue;

		if (!_strcmp(inf->argv[a], "$?"))
		{
			repc_str(&(inf->argv[a]),
				_strdup(convert_num(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[a], "$$"))
		{
			repc_str(&(inf->argv[a]),
				_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inf->env, &inf->argv[a][1], '=');
		if (node)
		{
			repc_str(&(inf->argv[a]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		repc_str(&inf->argv[a], _strdup(""));
	}
	return (0);
}

/**
 * repc_str - replaces string
 * @prev: address of old string
 * @buff: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int repc_str(char **prev, char *buff)
{
	free(*prev);
	*prev = buff;
	return (1);
}

