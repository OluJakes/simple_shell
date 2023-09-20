#include "shell.h"

/**
 * _strncpy - Copy a string.
 * @destr: The destination string to be copied to.
 * @srcstr: The source string.
 * @c: The number of characters to be copied.
 *
 * Return: The concatenated string.
 */
char *_strncpy(char *destr, char *srcstr, int c)
{
	int i, j;
	char *s = destr;

	i = 0;
	while (srcstr[i] != '\0' && i < c - 1)
	{
		destr[i] = srcstr[i];
		i++;
	}
	if (i < c)
	{
		j = i;
		while (j < c)
		{
			destr[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenate two strings.
 * @destr: The first string.
 * @srcstr: The second string.
 * @b: The maximum number of bytes to be used.
 *
 * Return: The concatenated string.
 */
char *_strncat(char *destr, char *srcstr, int b)
{
	int i, j;
	char *x = destr;

	i = 0;
	j = 0;
	while (destr[i] != '\0')
		i++;
	while (srcstr[j] != '\0' && j < b)
	{
		destr[i] = srcstr[j];
		i++;
		j++;
	}
	if (j < b)
		destr[j] = '\0';
	return (x);
}

/**
 * _strchr - Locate a character in a string.
 * @str: The string to be parsed.
 * @ch: The character to look for.
 *
 * Return: A pointer to the memory area or NULL if not found.
 */
char *_strchr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

