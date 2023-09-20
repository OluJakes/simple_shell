#include "shell.h"

/**
 * get_history_file - Retrieves the history file path.
 * @inf: Pointer to the parameter struct.
 *
 * Return: Allocated string containing the history file path.
 */
char *get_history_file(info_t *inf)
{
	char *buff, *dir;

	dir = _getenv(inf, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - Writes the history to a file.
 * @inf: Pointer to the parameter struct.
 *
 * Return: 1 on success, else -1.
 */
int write_history(info_t *inf)
{
	ssize_t fdir;
	char *fname = get_history_file(inf);
	list_t *node = NULL;

	if (!fname)
		return (-1);

	fdir = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fdir == -1)
		return (-1);
	for (node = inf->history; node; node = node->next)
	{
		_putsfd(node->str, fdir);
		_putfd('\n', fdir);
	}
	_putfd(BUF_FLUSH, fdir);
	close(fdir);
	return (1);
}

/**
 * read_history - Reads history from a file.
 * @inf: Pointer to the parameter struct.
 *
 * Return: Number of history entries read on success, 0 otherwise.
 */
int read_history(info_t *inf)
{
	int n, last = 0, lcount = 0;
	ssize_t fdir, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *fname = get_history_file(inf);

	if (!fname)
		return (0);

	fdir = open(fname, O_RDONLY);
	free(fname);
	if (fdir == -1)
		return (0);
	if (!fstat(fdir, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fdir, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fdir);
	for (n = 0; n < fsize; n++)
		if (buff[n] == '\n')
		{
			buff[n] = 0;
			build_history_list(inf, buff + last, lcount++);
			last = n + 1;
		}
	if (last != n)
		build_history_list(inf, buff + last, lcount++);
	free(buff);
	inf->histcount = lcount;
	while (inf->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	renumber_history(inf);
	return (inf->histcount);
}

/**
 * build_history_list - Adds an entry to the history linked list.
 * @inf: Pointer to the parameter struct.
 * @buff: Buffer containing the history entry.
 * @lcount: The history line count (histcount).
 *
 * Return: Always 0.
 */
int build_history_list(info_t *inf, char *buff, int lcount)
{
	list_t *node = NULL;

	if (inf->history)
		node = inf->history;
	add_node_end(&node, buff, lcount);

	if (!inf->history)
		inf->history = node;
	return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * @inf: Pointer to the parameter struct.
 *
 * Return: The new histcount.
 */
int renumber_history(info_t *inf)
{
	list_t *node = inf->history;
	int n = 0;

	while (node)
	{
		node->num = n++;
		node = node->next;
	}
	return (inf->histcount = n);
}

