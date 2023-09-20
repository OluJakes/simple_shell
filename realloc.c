#include "shell.h"

/**
 * _memset - Fills memory with a constant byte.
 * @dest: The pointer to the memory area.
 * @byte: The byte to fill @dest with.
 * @n: The number of bytes to be filled.
 *
 * Return: A pointer to the memory area @dest.
 */
char *_memset(char *dest, char byte, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = byte;
	return (dest);
}

/**
 * free_string_array - Frees an array of strings.
 * @array: The array of strings.
 */
void free_string_array(char **array)
{
	char **tmp = array;

	if (!array)
		return;
	while (*array)
		free(*array++);
	free(tmp);
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ed block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer to the reallocated block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}

