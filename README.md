# Garbage Free C V2

- Simple pointers tracer to free all traced pointers at once
- Now supports scoped and global tracing

## Build

- To build an example

```bash
cd examples
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -g ../garbage*.c <example file>
```

### Examples

- `global.c`: How to use global tracing
- `scoped.c`: How to use scoped tracing
- `mixed.c`: How to use both global and scoped tracing
- `untrace.c`: How to use both global and scoped untrace
## Usage

### Trace

- Trace a pointer to free later

> Returns: `0` on fail and `1` on success

```c
int scoped_trace(garbage *scope, void *ptr);
int global_trace(void *ptr);
```

### Untrace

- Untrace already traced pointer

```c
void scoped_untrace(garbage *scope, void *ptr);
void global_untrace(void *ptr);
```





### Free

- Free all traced pointers

```c
void scoped_free(garbage *scope);
void global_free(void);
```

### Has

- Check if scope is tracing a pointer

```c
int scoped_has(garbage *scope, void *ptr);
int global_has(void *ptr);
```

## Examples

### Global Scope Example

```c
#include <stdio.h>
#include <string.h>
#include "garbage.h"

int main(void) {
    char *str = strdup("hello");

    global_trace(str);

    printf("str: %s\n", str);

    global_free();

    printf("str: %s\n", str);

    return 0;
}
```

### Scoped Example

```c
#include <stdio.h>
#include <string.h>
#include "garbage.h"

int main(void) {
    garbage scope = NULL;
    char *str = strdup("hello");

    scoped_trace(&scope, str);

    printf("str: %s\n", str);

    scoped_free(&scope);

    printf("str: %s\n", str);

    return 0;
}
```
