# get_next_line

The goal of this project is to write a function that returns one line at a time from a file descriptor, and to learn how static variables work in C.

Each call to `get_next_line(fd)` returns the next line (including the `\n` when there is one), or `NULL` when there is nothing left to read or on error. The main difficulties are reading as little as possible with `read()`, keeping the leftover data between two calls, and making it work with any `BUFFER_SIZE` (1, 42, 9999, 10000000...) without leaks.

This README was written after the project was pushed. The subject PDF may have changed since then, so what is described here may no longer match the current subject 100%.

## Build

There is no Makefile for this project. The files are compiled together with your own `main.c`, and the buffer size can be chosen at compile time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
./gnl
```

The project also compiles without `-D BUFFER_SIZE` (a default value is defined in the header).

## Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd = open("file.txt", O_RDONLY);
    char    *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

It also works on standard input (`fd = 0`).

## Constraints

- Allowed functions: `read`, `malloc`, `free`.
- `lseek()` and global variables are forbidden, and libft is not allowed.

## Skills

- Static variables and state kept between calls
- File descriptors and `read()`
- Dynamic memory management and leak prevention
- Testing with extreme buffer sizes
