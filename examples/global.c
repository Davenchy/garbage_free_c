#include <stdio.h>
#include <string.h>
#include "../garbage.h"

int main(void) {
	char *str = strdup("hello"); /* allocate string */

	global_trace(str); /* trace the str pointer */

	printf("str: %s\n", str); /* now lets print before garbage_free */

	global_free(); /* free all global pointers */

	printf("str: %s\n", str); /* now lets print after garbage_free */

	return 0;
}
