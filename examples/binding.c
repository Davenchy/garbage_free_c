#include "../garbage.h"
#include <stdio.h>
#include <string.h>

int main(void) {
	char *str1 = strdup("hello"), *str2 = strdup("world");
	garbage scope = NULL;

	scoped_trace(&scope, str1);
	global_trace(str2);

	printf("str1(scoped): %s\n", str1);
	printf("str2(global): %s\n\n", str2);

	printf("is str1 scope traced: %s\n",
				scoped_has(&scope, str1) ? "yes" : "no");
	printf("is str1 global traced: %s\n",
				global_has(str1) ? "yes" : "no");

	printf("[bind scope(str1) to global]\n");
	global_bind(&scope);

	printf("is str1 scope traced: %s\n",
				scoped_has(&scope, str1) ? "yes" : "no");
	printf("is str1 global traced: %s\n",
				global_has(str1) ? "yes" : "no");

	scoped_free(&scope);

	puts("\nAfter Scoped Free:");
	printf("str1(global): %s\n", str1);
	printf("str2(global): %s\n", str2);

	global_free();

	puts("\nAfter Global Free:");
	printf("str1(global): %s\n", str1);
	printf("str2(global): %s\n", str2);

	return 0;
}
