#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../garbage.h"

int main(void) {
	garbage scope = NULL; /* create scope object and set it to NULL */
	char *str = strdup("hello");

	scoped_trace(&scope, str);

	printf("str: %s\n", str);

	scoped_free(&scope);

	printf("str: %s\n", str);

	return 0;
}
