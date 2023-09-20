#include "shell.h"

/**
 * **strtowrd - Splits a string into words. Repeated delimiters are ignored.
 * @in_str: The input string.
 * @del_str: The delimiter string.
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtowrd(char *in_str, char *del_str)
{
	int a, b, c, d, nwords = 0;
	char **s;

	if (in_str == NULL || in_str[0] == 0)
		return (NULL);

	if (!del_str)
		del_str = " ";

	for (a = 0; in_str[a] != '\0'; a++)
		if (!del_chk(in_str[a], del_str) && (del_chk(in_str[a + 1], del_str) || !in_str[a + 1]))
			nwords++;

	if (nwords == 0)
		return (NULL);

	s = malloc((1 + nwords) * sizeof(char *));
	if (!s)
		return (NULL);

	for (a = 0, b = 0; b < nwords; b++)
	{
		while (del_chk(in_str[a], del_str))
			a++;

		c = 0;
		while (!del_chk(in_str[a + c], del_str) && in_str[a + c])
			c++;

		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}

		for (d = 0; d < c; d++)
			s[b][d] = in_str[a++];
		s[b][d] = 0;
	}

	s[b] = NULL;
	return (s);
}

/**
 * **strtowrd2 - Splits a string into words.
 * @in_str: The input string.
 * @del_ch: The delimiter character.
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtowrd2(char *in_str, char del_ch)
{
	int a, b, c, d, nwords = 0;
	char **s;

	if (in_str == NULL || in_str[0] == 0)
		return (NULL);

	for (a = 0; in_str[a] != '\0'; a++)
		if ((in_str[a] != del_ch && in_str[a + 1] == del_ch) ||
		    (in_str[a] != del_ch && !in_str[a + 1]) || in_str[a + 1] == del_ch)
			nwords++;

	if (nwords == 0)
		return (NULL);

	s = malloc((1 + nwords) * sizeof(char *));
	if (!s)
		return (NULL);

	for (a = 0, b = 0; b < nwords; b++)
	{
		while (in_str[a] == del_ch && in_str[a] != del_ch)
			a++;

		c = 0;
		while (in_str[a + c] != del_ch && in_str[a + c] && in_str[a + c] != del_ch)
			c++;

		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}

		for (d = 0; d < c; d++)
			s[b][d] = in_str[a++];
		s[b][d] = 0;
	}

	s[b] = NULL;
	return (s);
}

