#ifndef __GARBAGE_H__

#define __GARBAGE_H__
#define G_GET 0
#define G_SET 1

/**
 * struct garbage_s - a linked list struct to hold list of the traced pointers
 * @ptr: the traced pointer
 * @next: the next object in the linked list
 */
typedef struct garbage_s
{
	void *ptr;
	struct garbage_s *next;
} *garbage;


garbage garbage_global(garbage gb, char mode);
int garbage_trace(void *ptr);
void garbage_untrace(void *ptr);
void garbage_free(void);
garbage garbage_last(garbage gb);

#endif
