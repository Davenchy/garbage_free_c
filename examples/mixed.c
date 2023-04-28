#include <stdio.h>
#include <string.h>
#include "../garbage.h"

int main(void) {
	garbage scope = NULL; /* create scope object and set it to NULL */
	char *str1 = strdup("hello"); /* allocate str1 */
	char *str2 = strdup("world"); /* allocate str2 */

	/* set the scope argument to NULL to use the global scope */
	global_trace(str1); /* trace str1 using global scope */
	scoped_trace(&scope, str2); /* trace str2 using scope object */

	printf("Before free:\n");
	printf("str1(global): %s\n", str1); /* now lets print before garbage_free */
	printf("str2(scoped): %s\n", str2); /* now lets print before garbage_free */

	/* set the scope argument to NULL to use the global scope */
	global_free();  /* free all global pointers */

	printf("\nafter global free:\n");
	printf("str1(global): %s\n", str1); /* now lets print after global free */
	printf("str2(scoped): %s\n", str2); /* now lets print after global free */

	scoped_free(&scope); /* free using garbage scope object */

	printf("\nafter scoped free:\n");
	printf("str1(global): %s\n", str1); /* now lets print after scoped free */
	printf("str2(scoped): %s\n", str2); /* now lets print after scoped free */

	return 0;
}
