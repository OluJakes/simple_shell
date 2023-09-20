#include "shell.h"

/**
 * starts - Checks if one string starts with another.
 * @hystck: The string to search.
 * @ndle: The substring to find.
 *
 * Return: Pointer to the next character of hystck or NULL if not found.
 */
char *starts(const char *hystck, const char *ndle)
{
	while (*ndle)
	{
		if (*ndle++ != *hystck++)
			return (NULL);
	}

	return ((char *)hystck);
}

/**
 * _strlen - Calculates the length of a string.
 * @ch: The input string.
 *
 * Return: The length of the string.
 */
int _strlen(char *ch)
{
	int length = 0;

	if (!ch)
		return (0);

	while (*ch)
	{
		length++;
		ch++;
	}

	return (length);
}

/**
 * _strcmp - Compares two strings lexicographically.
 * @ch1: The first string.
 * @ch2: The second string.
 *
 * Return: 0 if the strings are equal, a positive value if ch1 > ch2,
 *         and a negative value if ch1 < ch2.
 */
int _strcmp(char *ch1, char *ch2)
{
	while (*ch1 && *ch2)
	{
		if (*ch1 != *ch2)
			return (*ch1 - *ch2);

		ch1++;
		ch2++;
	}

	if (*ch1 == *ch2)
		return (0);
	else
		return (*ch1 < *ch2 ? -1 : 1);
}

/**
 * _strcat - Concatenates two strings.
 * @dest_buff: The destination buffer.
 * @src_buff: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcat(char *dest_buff, char *src_buff)
{
	char *ret = dest_buff;

	while (*dest_buff)
		dest_buff++;

	while (*src_buff)
		*dest_buff++ = *src_buff++;

	*dest_buff = *src_buff;

	return (ret);
}

