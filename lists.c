#include "shell.h"

/**
 * add_node - Adds a node to the start of the list.
 * @h_node: Address of pointer to head node.
 * @strfd: str field of node.
 * @node_idx: Node index used by history.
 *
 * Return: Pointer to the new head of the list.
 */
list_t *add_node(list_t **h_node, const char *strfd, int node_idx)
{
	list_t *new_head;

	if (!h_node)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = node_idx;
	if (strfd)
	{
		new_head->str = _strdup(strfd);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *h_node;
	*h_node = new_head;
	return (new_head);
}

/**
 * add_node_end - Adds a node to the end of the list.
 * @h_node: Address of pointer to head node.
 * @strfd: str field of node.
 * @node_idx: Node index used by history.
 *
 * Return: Pointer to the new node.
 */
list_t *add_node_end(list_t **h_node, const char *strfd, int node_idx)
{
	list_t *new_node, *node;

	if (!h_node)
		return (NULL);

	node = *h_node;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = node_idx;
	if (strfd)
	{
		new_node->str = _strdup(strfd);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*h_node = new_node;
	return (new_node);
}

/**
 * print_list_str - Prints only the str element of a list_t linked list.
 * @fnode: Pointer to the first node.
 *
 * Return: Number of nodes in the list.
 */
size_t print_list_str(const list_t *fnode)
{
	size_t g = 0;

	while (fnode)
	{
		_puts(fnode->str ? fnode->str : "(nil)");
		_puts("\n");
		fnode = fnode->next;
		g++;
	}
	return (g);
}

/**
 * delete_node_at_index - Deletes a node at a given index.
 * @fnode: Address of pointer to the first node.
 * @idx: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **fnode, unsigned int idx)
{
	list_t *node, *prev_node;
	unsigned int g = 0;

	if (!fnode || !*fnode)
		return (0);

	if (!idx)
	{
		node = *fnode;
		*fnode = (*fnode)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *fnode;
	while (node)
	{
		if (g == idx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		g++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - Frees all nodes of a list.
 * @hnode_ptr: Address of pointer to head node.
 *
 * Return: void.
 */
void free_list(list_t **hnode_ptr)
{
	list_t *node, *next_node, *head;

	if (!hnode_ptr || !*hnode_ptr)
		return;
	head = *hnode_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*hnode_ptr = NULL;
}

