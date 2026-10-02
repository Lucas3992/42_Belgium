# 42 Belgium – Common Core Projects

A collection of the projects I completed during the Common Core of [42], a project-based, peer-learning programming school. Each folder is an independent project with its own source code. There is a specific README file for each project with more details.

## Projects

| Project | Language | Description |
|---|---|---|
| **libft** | C | My own C library, rewriting standard functions (string, memory, list utilities) |
| **ft_printf** | C | Re-implementation of `printf` with variadic arguments |
| **get_next_line** | C | A function that reads a file descriptor one line at a time |
| **push_swap** | C | Sorts a stack of integers using a limited set of operations, with as few moves as possible |
| **minitalk** | C | Client/server exchange of messages using only UNIX signals |
| **so_long** | C | A small 2D game built with the MiniLibX graphics library |
| **philosophers** | C | Dining philosophers problem: threads, mutexes and synchronization |
| **minishell** | C | A simplified Bash-like shell with pipes, redirections and built-ins |
| **cub3d** | C | The final C projet: a 3D maze renderer using raycasting, inspired by Wolfenstein 3D |
| **CPP_Modules** | C++ | Series of exercises introducing C++ (classes, inheritance, templates, STL) |
| **webserv** | C++ | An HTTP server written from scratch (sockets, requests, CGI) |
| **inception** | Docker | A small web infrastructure (NGINX, WordPress, MariaDB) running in Docker containers |

## Tech

- **C** and **C++** for most projects
- **Make** for building
- **Docker / Docker Compose** for inception

## Build

Most projects are built with a Makefile. From inside a project folder:

```bash
make          # build the project
make clean    # remove object files
make fclean   # remove object files and the binary
make re       # rebuild from scratch
```

- **inception** runs with Docker Compose (`make` calls it for you)
- **CPP_Modules** contains many small exercises, each with its own Makefile

## Structure

```text
.
├── libft/
├── ft_printf/
├── get_next_line/
├── push_swap/
├── minitalk/
├── so_long/
├── cub3d/
├── philosophers/
├── minishell/
├── CPP_Modules/
├── webserv/
└── inception/
```

## A note on the Norm

Projects written in C follow the **Norm**, the strict coding standard of 42 (limited function length, limited number of functions per file, fixed naming and formatting rules, no `for` loops, and so on). It is checked automatically, and a single Norm error means a grade of 0 for the project, bonus files included.

The goal is not style for its own sake. The Norm teaches rigor and discipline: it pushes you to write short, readable, single-purpose functions and to split your code cleanly. It also means any other 42 student can read your code without effort. This is why the C code in this repository can look a bit unusual compared to what you see in other projects.

The C++ modules are different: the Norm does not apply there, and the formatting style is free.