#include "custom-shell.h"

/**
 * bfree - frees a pointer and the address
 * @ptr: address to free
 *
 * Return: 1 if freed
 */
int make_memory_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
