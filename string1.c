#include "shell.h"

/**
 * _strcpy - Copies a string.
 * @dest_str: The destination string.
 * @src_str: The source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *dest_str, char *src_str)
{
	int n = 0;

	if (dest_str == src_str || src_str == NULL)
		return (dest_str);

	while (src_str[n])
	{
		dest_str[n] = src_str[n];
		n++;
	}
	dest_str[n] = '\0';
	return (dest_str);
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string or NULL on failure.
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*str++)
		len++;

	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);

	for (len++; len--;)
		ret[len] = *--str;

	return (ret);
}

/**
 * _puts - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _puts(char *str)
{
	int n = 0;

	if (!str)
		return;

	while (str[n] != '\0')
	{
		_putchar(str[n]);
		n++;
	}
}

/**
 * _putchar - Writes the character c to stdout.
 * @c: The character to print.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set
 *         appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buff, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buff[i++] = c;
	return (1);
}

