# Coding Convention

## Pointer Declarations

Always attach `*` to the **type**, not the variable name.

```c
// correct
int* p;
const char* s;
void* buf;

// wrong
int *p;
const char *s;
void *buf;
```

This applies to all data types — including `const`-qualified types, `void*`, and function parameters.

```c
// correct
void swap(int* a, int* b);

// wrong
void swap(int *a, int *b);
```

### Exception

Intentional **bad-style examples** used for pedagogical contrast (e.g., marked with 😖) must be left unchanged.
