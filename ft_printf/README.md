# ft_printf

The goal of this project is to re-code the C `printf()` function, mainly to learn how variadic functions (functions with a variable number of arguments) work.

The function reads a format string, detects each conversion and prints the matching argument directly with `write`. The main difficulties are using `va_list` correctly, printing numbers in different bases (hexadecimal, pointers) and matching the output of the real `printf` exactly, including the edge cases (`NULL` string, `NULL` pointer, `INT_MIN`).

This README was written after the project was pushed. The subject PDF may have changed since then, so what is described here may no longer match the current subject 100%.

## Build

```bash
make          # builds libftprintf.a
make clean    # removes object files
make fclean   # removes object files and the library
make re       # rebuilds everything
```

Use it in another project:

```bash
cc main.c libftprintf.a -o test
```

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello %s, you are number %d (0x%x)\n", "42", 42, 42);
    return (0);
}
```

## Features

Supported conversions: `%c` `%s` `%p` `%d` `%i` `%u` `%x` `%X` `%%`.

## Constraints

- Allowed functions: `malloc`, `free`, `write`, `va_start`, `va_arg`, `va_copy`, `va_end`.
- The buffer management of the original `printf` is not implemented.
- Library created with `ar`.

## Skills

- Variadic functions (`stdarg.h`)
- Number base conversion
- Structuring code so it stays easy to extend
- Matching the behavior of a reference implementation
