#include "garbage.h"

/**
 * scoped_trace - trace a new @ptr to free later
 * @scope: the used scope object
 * @ptr: the pointer to free later
 * Description:
 *
 * Return: 1 on success otherwise 0
 */
int scoped_trace(garbage *scope, void *ptr)
{
	return (garbage_trace(scope, S_SCOPED, ptr));
}

/**
 * scoped_untrace - untrace pointer and remove from the linked list
 * @scope: the used scope object
 * @ptr: the pointer to untrace
 */
void scoped_untrace(garbage *scope, void *ptr)
{
	garbage_untrace(scope, S_SCOPED, ptr);
}

/**
 * scoped_free - free all traced pointers
 * @scope: the used scope object
 */
void scoped_free(garbage *scope)
{
	garbage_free(scope, S_SCOPED);
}

/**
 * scoped_has - check if scope is tracing a pointer
 * @scope: pointer to the scope object
 * @ptr: the pointer to check
 *
 * Return: 1 if found otherwise 0
 */
int scoped_has(garbage *scope, void *ptr)
{
	garbage gb;

	if (!scope || !ptr)
		return (0);
	gb = *scope;
search:
	if (!gb)
		return (0);
	if (gb->ptr == ptr)
		return (1);
	gb = gb->next;
	goto search;
}
