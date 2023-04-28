# Garbage

- Simple pointers tracer to free all traced pointers at once

## Build

- to build the example

`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -g *.c`

## Usage

### garbage_trace

Trace a pointer to free later

> Returns: `0` on fail and `1` on success

```c
int garbage_trace(void *ptr);
```

### garbage_untrace

Untrace already traced pointer

```c
void garbage_untrace(void *ptr);
```

### garbage_free

Free all traced pointers

```c
void garbage_free(void);
```
