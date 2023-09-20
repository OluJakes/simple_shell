#include "shell.h"

/**
 * list_len - Determines the length of a linked list.
 * @fnode: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t list_len(const list_t *fnode)
{
	size_t z = 0;

	while (fnode)
	{
		fnode = fnode->next;
		z++;
	}
	return (z);
}

/**
 * list_to_strings - Converts a linked list of strings to an array of strings.
 * @fnode: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **list_to_strings(list_t *fnode)
{
	list_t *node = fnode;
	size_t z = list_len(fnode), n;
	char **strs;
	char *str;

	if (!fnode || !z)
		return (NULL);
	strs = malloc(sizeof(char *) * (z + 1));
	if (!strs)
		return (NULL);
	for (z = 0; node; node = node->next, z++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (n = 0; n < z; n++)
				free(strs[n]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[z] = str;
	}
	strs[z] = NULL;
	return (strs);
}

/**
 * print_list - Prints all elements of a list_t linked list.
 * @fnode: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list(const list_t *fnode)
{
	size_t z = 0;

	while (fnode)
	{
		_puts(convert_num(fnode->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(fnode->str ? fnode->str : "(nil)");
		_puts("\n");
		fnode = fnode->next;
		z++;
	}
	return (z);
}

/**
 * node_starts_with - Returns a node whose string starts with a prefix.
 * @lhead: Pointer to the list head.
 * @pfix: String to match.
 * @ch: The next character after the prefix to match (-1 if any character).
 *
 * Return: Matched node or NULL.
 */
list_t *node_starts_with(list_t *node, char *pfix, char ch)
{
	char *v = NULL;

	while (node)
	{
		v = starts(node->str, pfix);
		if (v && ((ch == -1) || (*v == ch)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node in a linked list.
 * @lhead: Pointer to the list head.
 * @node_ptr: Pointer to the node.
 *
 * Return: Index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *lhead, list_t *node_ptr)
{
	size_t z = 0;

	while (lhead)
	{
		if (lhead == node_ptr)
			return (z);
		lhead = lhead->next;
		z++;
	}
	return (-1);
}

