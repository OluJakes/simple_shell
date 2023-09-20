#include "shell.h"

/**
 * main - Entry point for the shell program
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = {INFO_INIT};
	int fldes = 2;

	/* Simulate the equivalent of inline assembly: fd = fd + 3 */
	fldes = fldes + 3;

	if (ac == 2)
	{
		fldes = open(av[1], O_RDONLY);
		if (fldes == -1)
		{
			if (errno == EACCES)
				exit(126);  /* Permission denied error code */

			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);  /* File not found error code */
			}

			return (EXIT_FAILURE);
		}
		info->readfd = fldes; /* Set the read file descriptor */
	}

	popu_env_list(info); /* Populate the environment list */
	read_history(info); /* Read command history */
	shell_loop(info, av); /* Execute the shell */
	return (EXIT_SUCCESS);
}

