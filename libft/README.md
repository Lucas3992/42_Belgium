# libft

The goal of this project is to build my own C library by re-implementing standard `libc` functions and adding useful extra utilities.

It is split in three parts: re-coding libc functions (`ft_strlen`, `ft_memmove`, `ft_atoi`...), additional string and output helpers (`ft_split`, `ft_itoa`, `ft_strjoin`...), and linked-list functions. The main difficulties are handling memory correctly (no leaks, no crashes, `NULL` checks after every `malloc`) and matching the exact behavior of the original functions, including edge cases.

This README was written after the project was pushed. The subject PDF may have changed since then, so what is described here may no longer match the current subject 100%.

## Build

```bash
make          # builds libft.a
make bonus    # adds the linked-list functions
make clean    # removes object files
make fclean   # removes object files and libft.a
make re       # rebuilds everything
```

Use it in another project by including `libft.h` and linking with `libft.a`:

```bash
cc main.c -L. -lft -o test
```

## Features

- Libc re-implementations: character checks, `str*` and `mem*` functions, `atoi`, `calloc`, `strdup`...
- Additional functions: `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`, `ft_itoa`, `ft_strmapi`, `ft_striteri`, `ft_put*_fd`.
- Linked lists: `ft_lstnew`, `ft_lstadd_front`, `ft_lstadd_back`, `ft_lstsize`, `ft_lstlast`, `ft_lstdelone`, `ft_lstclear`, `ft_lstiter`, `ft_lstmap`.

## Bonus

The bonus part is the linked-list section (files ending in `_bonus.c`). It uses a `t_list` structure (`content`, `next`) and is built with `make bonus`.

## Constraints

- No global variables, no external functions other than `malloc`, `free` and `write`.
- Library created with `ar`, compiled with `-Wall -Wextra -Werror`.

## Skills

- Memory management in C
- Pointers and string manipulation
- Writing a reusable static library
- Makefile writing
