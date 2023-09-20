#include "shell.h"

/**
 * shell_loop - Main shell loop
 * @inf: Parameter and return info struct
 * @av: Argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(info_t *inf, char **av)
{
	ssize_t rs = 0;
	int br = 0;

	while (rs != -1 && br != -2)
	{
		clear_info(inf);
		if (interactive_chk(inf))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		rs = get_input(inf);
		if (rs != -1)
		{
			set_info(inf, av);
			br = find_builtin_cmd(inf);
			if (br == -1)
				find_cmd(inf);
		}
		else if (interactive_chk(inf))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_history(inf);
	free_info(inf, 1);
	if (!interactive_chk(inf) && inf->status)
		exit(inf->status);
	if (br == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (br);
}

/**
 * find_builtin_cmd - Finds a builtin command
 * @inf: Parameter and return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin_cmd(info_t *inf)
{
	int n;
	int br = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (n = 0; builtintbl[n].type != NULL; n++)
	{
		if (_strcmp(inf->argv[0], builtintbl[n].type) == 0)
		{
			inf->line_count++;
			br = builtintbl[n].func(inf);
			break;
		}
	}
	return (br);
}

/**
 * find_cmd - Finds a command in PATH
 * @inf: Parameter and return info struct
 *
 * Return: void
 */
void find_cmd(info_t *inf)
{
	char *path = NULL;
	int a, b;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (a = 0, b = 0; inf->arg[a]; a++)
		if (!del_chk(inf->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = find_comm_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_cmd(inf);
	}
	else
	{
		if ((interactive_chk(inf) || _getenv(inf, "PATH=") ||
					inf->argv[0][0] == '/') && is_exec(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_error(inf, "not found\n");
		}
	}
}

/**
 * fork_cmd - Forks a child process to run a command
 * @inf: Parameter and return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_error(inf, "Permission denied\n");
		}
	}
}

