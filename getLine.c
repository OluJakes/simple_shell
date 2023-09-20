#include "shell.h"

/**
 * input_buf - Reads and buffers chained commands from standard input.
 * @inf: Parameter struct.
 * @buff: Address of the buffer.
 * @varlen: Address of the length variable.
 *
 * Return: The number of bytes read.
 */
ssize_t input_buf(info_t *inf, char **buff, size_t *varlen)
{
	ssize_t bytes_read = 0;
	size_t buffer_len = 0;

	if (!*varlen) /* If the buffer is empty, fill it. */
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		bytes_read = getline(buff, &buffer_len, stdin);
#else
		bytes_read = _getline(inf, buff, &buffer_len);
#endif

		if (bytes_read > 0)
		{
			if ((*buff)[bytes_read - 1] == '\n')
			{
				(*buff)[bytes_read - 1] = '\0'; /* Remove trailing newline. */
				bytes_read--;
			}

			inf->linecount_flag = 1;
			rem_comments(*buff);
			build_history_list(inf, *buff, inf->histcount++);

			/* Check if it's a command chain. */
			{
				*varlen = bytes_read;
				inf->cmd_buf = buff;
			}
		}
	}
	return (bytes_read);
}

/**
 * get_input - Gets a line of input without the newline character.
 * @inf: Parameter struct.
 *
 * Return: The number of bytes read.
 */
ssize_t get_input(info_t *inf)
{
	static char *buff; /* Buffer for command chain with ';' */
	static size_t a, b, varlen;
	ssize_t bytes_read = 0;
	char **buf_p = &(inf->arg), *j;

	_putchar(BUF_FLUSH);
	bytes_read = input_buf(inf, &buff, &varlen);

	if (bytes_read == -1) /* EOF */
		return (-1);

	if (varlen) /* Commands are left in the chain buffer. */
	{
		b = a; /* Initialize a new iterator to the current buffer position. */
		j = buff + a; /* Get a pointer for return. */

		chn_chk(inf, buff, &b, a, varlen);

		while (b < varlen) /* Iterate to the semicolon or the end. */
		{
			if (chn_del(inf, buff, &b))
				break;
			b++;
		}

		a = b + 1; /* Increment past the nullified ';'. */

		if (a >= varlen) /* Reached the end of the buffer? */
		{
			a = varlen = 0; /* Reset the position and length. */
			inf->cmd_buf_type = CMD_NORM;
		}

		*buf_p = j; /* Pass back a pointer to the current command position. */
		return (_strlen(j)); /* Return the length of the current command. */
	}

	*buf_p = buff; /* Otherwise, not a chain, so pass buffer from _getline(). */
	return (bytes_read); /* Return the length of the buffer from _getline(). */
}

/**
 * read_buf - Reads from a buffer.
 * @inf: Parameter struct.
 * @buff: The buffer.
 * @z: The size.
 *
 * Return: The number of bytes read.
 */
ssize_t read_buf(info_t *inf, char *buff, size_t *z)
{
	ssize_t bytes_read = 0;

	if (*z)
		return (0);
	bytes_read = read(inf->readfd, buff, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*z = bytes_read;
	return (bytes_read);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @inf: Parameter struct.
 * @ptr: Address of a pointer to a buffer, which can be preallocated or NULL.
 * @bufflen: Size of the preallocated ptr buffer if not NULL.
 *
 * Return: The number of bytes read.
 */
int _getline(info_t *inf, char **ptr, size_t *bufflen)
{
	static char buff[READ_BUF_SIZE];
	static size_t f, len;
	size_t k;
	ssize_t bytes_read = 0, total_bytes_read = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && bufflen)
		total_bytes_read = *bufflen;
	if (f == len)
		f = len = 0;

	bytes_read = read_buf(inf, buff, &len);

	if (bytes_read == -1 || (bytes_read == 0 && len == 0))
		return (-1);

	c = _strchr(buff + f, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;

	new_p = _realloc(p, total_bytes_read, total_bytes_read ?
			total_bytes_read + k : k + 1);

	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (total_bytes_read)
		_strncat(new_p, buff + f, k - f);
	else
		_strncpy(new_p, buff + f, k - f + 1);

	total_bytes_read += k - f;
	f = k;
	p = new_p;

	if (bufflen)
		*bufflen = total_bytes_read;
	*ptr = p;
	return (total_bytes_read);
}

/**
 * sigintHandler - Handles the Ctrl-C signal,
 * prints a new line and shell prompt.
 * @sig_num: The signal number.
 *
 * Return: Void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

