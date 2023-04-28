#include "../garbage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	/* initialize allocated pointers */
	char *str1 = strdup("hello"), *str2 = strdup("world");
	garbage scope = NULL; /* the scope object */

	/* trace using scoped and global tracing */
	scoped_trace(&scope, str1);
	global_trace(str2);

	/* print samples */
	printf("str1(scoped): %s\n", str1);
	printf("str2(global): %s\n", str2);

	/* check if samples already traced */
	printf("\nBefore Untrace:\n");
	printf("str1 is scope traced: %s\n",
				scoped_has(&scope, str1) ? "yes" : "no");
	printf("str2 is global traced: %s\n", global_has(str2) ? "yes" : "no");

	/* untrace samples */
	scoped_untrace(&scope, str1);
	global_untrace(str2);

	/* check if samples still traced */
	printf("\nAfter Untrace:\n");
	printf("str1 is scope traced: %s\n",
				scoped_has(&scope, str1) ? "yes" : "no");
	printf("str2 is global traced: %s\n", global_has(str2) ? "yes" : "no");

	/* try garbage free */
	scoped_free(&scope);
	global_free();

	/* check if samples are free */
	printf("\nAfter Garbage Free:\n");
	printf("str1(scoped): %s\n", str1);
	printf("str2(global): %s\n", str2);

	/* free samples manualy before exit */
	free(str1);
	free(str2);

	return 0;
}
