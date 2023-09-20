#include "shell.h"

/**
 * _erratoi - Convert a string to an integer.
 * @st: The string to be converted.
 *
 * Return: The converted number if successful, -1 on error or no numbers found.
 */
int _erratoi(char *st)
{
	int k = 0;
	unsigned long int result = 0;

	if (*st == '+')
		st++;
	for (k = 0; st[k] != '\0'; k++)
	{
		if (st[k] >= '0' && st[k] <= '9')
		{
			result *= 10;
			result += (st[k] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Print an error message.
 * @inf: The parameter and return info struct.
 * @est: String containing specified error type.
 */
void print_error(info_t *inf, char *est)
{
	_eputs(inf->fname);
	_eputs(": ");
	print_dec(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(est);
}

/**
 * print_dec - Print a decimal (integer) number (base 10).
 * @inp: The input number.
 * @fldes: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_dec(int inp, int fldes)
{
	int (*__putchar)(char) = _putchar;
	int g, count = 0;
	unsigned int _abs_, current;

	if (fldes == STDERR_FILENO)
		__putchar = _eputchar;
	if (inp < 0)
	{
		_abs_ = -inp;
		__putchar('-');
		count++;
	}
	else
		_abs_ = inp;
	current = _abs_;
	for (g = 1000000000; g > 1; g /= 10)
	{
		if (_abs_ / g)
		{
			__putchar('0' + current / g);
			count++;
		}
		current %= g;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_num - Convert a number to a string representation.
 * @num: The number.
 * @base: The base for conversion.
 * @flags: Argument flags.
 *
 * Return: The string representation of the number.
 */
char *convert_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rem_comments - Replace the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 */
void rem_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}

