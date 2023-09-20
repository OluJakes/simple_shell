#include "shell.h"

/**
 * pfree - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 if freed, 0 otherwise.
 */
int pfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

