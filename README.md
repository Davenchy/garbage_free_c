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
- `binging.c`: How to use both global and scoped binging
- `untrace.c`: How to use both global and scoped untrace

#### Global Scope Example

```c
#include <stdio.h>
#include <string.h>
#include "garbage.h"

int main(void) {
    char *str = strdup("hello"); /* allocate some data */

    global_trace(str); /* use the global scope to trace the str pointer */

    printf("str: %s\n", str); /* it should print normally */

    global_free(); /* free the global scope */

    printf("str: %s\n", str); /* it should print garbage */

    return 0;
}
```

#### Scoped Example

```c
#include <stdio.h>
#include <string.h>
#include "garbage.h"

int main(void) {
    garbage scope = NULL; /* initialize the scope object to NULL */
    char *str = strdup("hello"); /* allocate some data */

    scoped_trace(&scope, str); /* trace the str pointer */

    printf("str: %s\n", str); /* it should print normally */

    scoped_free(&scope); /* free the scope */

    printf("str: %s\n", str); /* it should print garbage now */

    return 0;
}
```

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

### Binding

- Bind or add tracers from scope to another and destroy the source scope.
- Also bind or add tracers from scope to global scope and destroy the source.

> Returns: `0` on fail and `1` on success

```c
void scoped_bind(global_scope *dest, global_trace *src);
void global_bind(global_trace *scope);
```

### Free

- Free all traced pointers

```c
void scoped_free(garbage *scope);
void global_free(void);
```

### Has

- Check if scope is tracing a pointer

> Returns: `0` on fail and `1` on success

```c
int scoped_has(garbage *scope, void *ptr);
int global_has(void *ptr);
```