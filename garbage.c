#include "garbage.h"
#include <stdlib.h>

/**
 * garbage_global - store garbage object globaly
 * @gb: the garbage object value
 * @mode: G_GET for output mode and G_SET for set object mode
 * Description:
 * By default no garbage object stored
 *
 * To change the stored value use the G_SET mode
 *
 * To get the stored value use the G_GET mode
 *
 * Return: the stored object or NULL if no stored data, only outputs if G_GET
 */
garbage garbage_global(garbage gb, char mode)
{
	static garbage cache;
	static char has_value = -1;

	if (mode == G_SET) /* check if it is set mode */
	{
		cache = gb; /* cache the new object */
		has_value = cache ? 1 : -1; /* check if cache is NULL or not */
	}
	/* only send cached object if it is out mode and has cached object */
	return ((mode == G_GET && has_value == 1) ? cache : NULL);
}

/**
 * garbage_last - find and return the last object in the linked list
 * @gb: the starting point for the search
 *
 * Return: the last gb object in the list otherwise NULL
 */
garbage garbage_last(garbage gb)
{
	if (!gb)
		return (NULL);
	while (gb->next)
		gb = gb->next;
	return (gb);
}

/**
 * garbage_trace - trace a new @ptr to free later
 * @ptr: the pointer to free later
 *
 * Return: 1 on success otherwise 0
 */
int garbage_trace(void *ptr)
{
	garbage gb, head;

	if (!ptr) /* only valid pointers allowed */
		return (0);
	gb = malloc(sizeof(struct garbage_s)); /* allocate memory for the object */
	if (!gb) /* check if allocating failed */
		return (0);
	gb->ptr = ptr; /* store the pointer inside the garbage object */

	/* load the current stored linked list head */
	head = garbage_global(NULL, G_GET);
	if (head) /* check if a linked list head is stored */
		garbage_last(head)->next = gb; /* push to the end of the linked list */
	else
		/* otherwise use the current gb object as the head of the linked list */
		garbage_global(gb, G_SET);
	return (1);
}

/**
 * garbage_free - free all traced pointers
 */
void garbage_free(void)
{
	garbage curr = NULL, gb = NULL; 

	gb = garbage_global(NULL, G_GET); /* load current head */
	while (gb)
	{
		curr = gb;
		gb = gb->next;
		free(curr->ptr); /* free the pointer */
		free(curr); /* free the garbage object */
	}
	garbage_global(NULL, G_SET); /* reset the global head */
}

/**
 * garbage_untrace - untrace pointer and remove from the linked list
 * @ptr: the pointer to untrace
 */
void garbage_untrace(void *ptr)
{
	garbage last, gb = garbage_global(NULL, G_GET);

	if (!ptr)
		return;
search:
	if (!gb)
		return;
	if (gb->ptr == ptr)
		goto remove;
	last = gb;
	gb = last->next;
	goto search;
remove:
	if (!last) /* if the gb obj is the head itself */
		garbage_global(gb->next, G_SET); /* set the next object as the new head */
	else
		last->next = gb->next; /* remove from the linked list */
	free(gb); /* free the object memory */
}
