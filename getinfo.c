#include "shell.h"

/**
 * clear_info - Initializes the info_t struct fields to NULL or 0.
 * @inf: Pointer to the info_t struct to be initialized.
 */
void clear_info(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_info - Initializes the info_t struct with provided arguments.
 * @inf: Pointer to the info_t struct to be initialized.
 * @av: Argument vector.
 */
void set_info(info_t *inf, char **av)
{
	int k = 0;

	inf->fname = av[0];
	if (inf->arg)
	{
		inf->argv = strtowrd(inf->arg, " \t");
		if (!inf->argv)
		{
			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (k = 0; inf->argv && inf->argv[k]; k++)
			;
		inf->argc = k;

		repc_alias(inf);
		repc_vars(inf);
	}
}

/**
 * free_info - Frees the fields of the info_t struct.
 * @inf: Pointer to the info_t struct.
 * @allfds: Boolean, true if freeing all fields.
 */
void free_info(info_t *inf, int allfds)
{
	free_string_array(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (allfds)
	{
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->env)
			free_list(&(inf->env));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		free_string_array(inf->environ);
		inf->environ = NULL;
		pfree((void **)inf->cmd_buf);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(BUF_FLUSH);
	}
}

