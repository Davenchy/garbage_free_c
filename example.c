#include "garbage.h"
#include <stdio.h>
#include <string.h>

char *create_fake_cstring(void) {
	char *str = strdup("Fake CString");

	garbage_trace(str);
	return str;
}

int main(void) {
	char *str = create_fake_cstring();

	if (!str)
		puts("Failed to create fake cstring!");
	else
		printf("msg: %s\n", str);

	garbage_free();

	return 0;
}
