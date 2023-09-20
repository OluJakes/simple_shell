#include "shell.h"

/**
 * _atoi - Convert a string to an integer.
 * @str: The string to be converted.
 *
 * Return: The converted number if valid, 0 if no numbers are in the string.
 */
int _atoi(char *str)
{
	int x, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (x = 0; str[x] != '\0' && flag != 2; x++)
	{
		if (str[x] == '-')
			sign *= -1;

		if (str[x] >= '0' && str[x] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * _isalpha - Check if a character is alphabetic.
 * @ch: The character to check.
 *
 * Return: 1 if `c` is alphabetic, 0 otherwise.
 */
int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * interactive_chk - Check if the shell is running in interactive mode.
 * @inf: Pointer to a structure containing information.
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */
int interactive_chk(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * del_chk - Check whether a character is a delimiter.
 * @ch: The character to check.
 * @del: The delimiter string to compare with.
 *
 * Return: 1 if `c` is a delimiter, 0 if not.
 */
int del_chk(char ch, char *del)
{
	while (*del)
		if (*del++ == ch)
			return (1);
	return (0);
}

