# minishell

The goal of this project is to write my own small shell in C, a simplified Bash that reads a command line, parses it and executes it.

The shell displays a prompt, keeps a history, launches programs found through `PATH` (or given by a relative or absolute path), and handles quotes, environment variables, redirections and pipes. The main difficulties are the parsing (tokens, quotes, `$` expansion), connecting several processes with `fork`, `pipe` and `dup2` while keeping file descriptors clean, handling signals like Bash does, and avoiding memory leaks. When in doubt, Bash was used as the reference.

This README was written after the project was pushed. The subject PDF may have changed since then, so what is described here may no longer match the current subject 100%.

## Build and run

```bash
make          # builds minishell
./minishell
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # rebuilds everything
```

## Requirements

- `cc` and `make`
- The GNU `readline` library. On Debian/Ubuntu: `sudo apt install libreadline-dev`

## Features

- Prompt and working command history.
- Execution of programs through `PATH`, or with a relative or absolute path.
- Single quotes (no interpretation) and double quotes (only `$` is interpreted). Unclosed quotes, `\` and `;` are not interpreted.
- Redirections: `<`, `>`, `>>` and heredoc `<<` with a delimiter.
- Pipes `|`, connecting the output of each command to the input of the next.
- Environment variable expansion (`$VAR`) and the exit status of the last pipeline (`$?`).
- Signals in interactive mode: `Ctrl-C` shows a new prompt, `Ctrl-D` exits, `Ctrl-\` does nothing.
- Built-in commands: `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

## Constraints

- At most one global variable, used only to store a received signal number.
- Only the allowed functions of the subject (`readline`, `fork`, `execve`, `pipe`, `dup2`, `waitpid`, `sigaction`...).
- Memory leaks from `readline()` itself are tolerated, but not from my own code.

## Project structure

The sources are in `src/`, split by role: `parsing`, `tokens`, `execution`, `childs`, `redirections`, `heredoc`, `built_inns` (built-ins), `signals`, `errors_and_free` and `utilities`. Headers are in `include/` and my libft is in `libft/`.

## Skills

- Processes: `fork`, `execve`, `wait`
- Pipes, file descriptors and redirections
- Signal handling
- Lexing and parsing of a command line
- Memory management in a large C codebase