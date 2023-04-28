#include "garbage.h"

/**
 * global_trace - trace a new @ptr to free later
 * @ptr: the pointer to free later
 * Description:
 *
 * Return: 1 on success otherwise 0
 */
int global_trace(void *ptr)
{
	return (garbage_trace((void *)0, S_GLOBAL, ptr));
}

/**
 * global_untrace - untrace pointer and remove from the linked list
 * @ptr: the pointer to untrace
 */
void global_untrace(void *ptr)
{
	garbage_untrace((void *)0, S_GLOBAL, ptr);
}

/**
 * global_free - free all traced pointers
 */
void global_free(void)
{
	garbage_free((void *)0, S_GLOBAL);
}

/**
 * global_has - check if global scope is tracing a pointer
 * @ptr: the pointer to check
 *
 * Return: 1 if found otherwise zero
 */
int global_has(void *ptr)
{
	garbage gb = garbage_global((void *)0, A_GET);

	if (!ptr)
		return (0);
search:
	if (!gb)
		return (0);
	if (gb->ptr == ptr)
		return (1);
	gb = gb->next;
	goto search;
}
