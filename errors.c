#include "shell.h"

/**
 * _eputs - Print a string to stderr.
 * @st: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *st)
{
	int j = 0;

	if (!st)
		return;
	while (st[j] != '\0')
	{
		_eputchar(st[j]);
		j++;
	}
}

/**
 * _eputchar - Write a character to stderr.
 * @ch: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char ch)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buf, n);
		n = 0;
	}
	if (ch != BUF_FLUSH)
		buf[n++] = ch;
	return (1);
}

/**
 * _putfd - Write a character to a given file descriptor.
 * @ch: The character to print.
 * @fldes: The file descriptor to write to.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char ch, int fldes)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(fldes, buf, n);
		n = 0;
	}
	if (ch != BUF_FLUSH)
		buf[n++] = ch;
	return (1);
}

/**
 * _putsfd - Print a string to a given file descriptor.
 * @st: The string to be printed.
 * @fldes: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int _putsfd(char *st, int fldes)
{
	int x = 0;

	if (!st)
		return (0);
	while (*st)
	{
		x += _putfd(*st++, fldes);
	}
	return (x);
}

