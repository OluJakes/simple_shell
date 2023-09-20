#include "shell.h"

/**
 * _myenv - Print the current environment.
 * @inf: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myenv(info_t *inf)
{
	print_list_str(inf->env);
	return (0);
}

/**
 * _getenv - Get the value of an environment variable.
 * @inf: Structure containing potential arguments.
 * @nam: The environment variable name.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *_getenv(info_t *inf, const char *nam)
{
	list_t *node = inf->env;
	char *value;

	while (node)
	{
		value = starts(node->str, nam);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable or modify an existing one.
 * @inf: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _mysetenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable.
 * @inf: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myunsetenv(info_t *inf)
{
	int p;

	if (inf->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (p = 1; p < inf->argc; p++)
		_unsetenv(inf, inf->argv[p]);

	return (0);
}

/**
 * popu_env_list - Populate the environment linked list.
 * @inf: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int popu_env_list(info_t *inf)
{
	list_t *node = NULL;
	size_t t;

	for (t = 0; environ[t]; t++)
		add_node_end(&node, environ[t], 0);
	inf->env = node;
	return (0);
}

