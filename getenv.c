#include "shell.h"

/**
 * get_environ - Returns a copy of the environ as a string array.
 * @inf: Structure containing potential arguments.
 *
 * Return: A string array copy of the environ.
 */
char **get_environ(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - Removes an environment variable.
 * @inf: Structure containing potential arguments.
 * @envar: The environment variable to remove.
 *
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int _unsetenv(info_t *inf, char *envar)
{
	list_t *node = inf->env;
	size_t index = 0;
	char *v;

	if (!node || !envar)
		return (0);

	while (node)
	{
		v = starts(node->str, envar);
		if (v && *v == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->env), index);
			index = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (inf->env_changed);
}

/**
 * _setenv - Initializes a new or modifies exixting environment variable
 * @inf: Structure containing potential arguments.
 * @envar: The environment variable property.
 * @enval: The environment variable value.
 *
 * Return: 0 on success, 1 on failure.
 */
int _setenv(info_t *inf, char *envar, char *enval)
{
	char *buff = NULL;
	list_t *node;
	char *v;

	if (!envar || !enval)
		return (0);

	buff = malloc(_strlen(envar) + _strlen(enval) + 2);

	if (!buff)
		return (1);
	_strcpy(buff, envar);
	_strcat(buff, "=");
	_strcat(buff, enval);
	node = inf->env;
	while (node)
	{
		v = starts(node->str, envar);
		if (v && *v == '=')
		{
			free(node->str);
			node->str = buff;
			inf->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(inf->env), buff, 0);
	free(buff);
	inf->env_changed = 1;
	return (0);
}

