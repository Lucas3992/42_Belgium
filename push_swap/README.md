# push_swap

The goal of this project is to sort a stack of integers using a second stack and a very limited set of operations, with as few moves as possible.

The program receives a list of unique integers as stack `a` (stack `b` starts empty) and prints the shortest sequence of instructions it can find to sort `a` in ascending order. The instructions are `sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb` and `rrr`. The main difficulty is reducing the number of operations enough to pass the benchmark.

This README was written after the project was pushed. The subject PDF may have changed since then, so what is described here may no longer match the current subject 100%.

## Build and run

```bash
make          # builds push_swap
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # rebuilds everything
```

```bash
./push_swap 2 1 3 6 5 8
```

The first argument is the top of the stack. The program prints one instruction per line:

```bash
$ ./push_swap 2 1 3 6 5 8
sa
pb
pb
pb
sa
pa
pa
pa
```

Count the instructions and check the result with the checker provided by 42:

```bash
ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_OS $ARG
```

## Behavior

- No arguments: nothing is displayed.
- Invalid input (non-integers, values outside the `int` range, duplicates): `Error` is printed on the standard error.
- Instructions are separated by a newline and nothing else.

## Benchmark

To fully validate the project, the subject requires sorting 100 random numbers in fewer than 700 operations, and 500 random numbers in no more than 5500 operations.

## Constraints

- Allowed functions: `read`, `write`, `malloc`, `free`, `exit`, plus `ft_printf` or an equivalent coded by myself.
- No global variables. The Makefile must not relink.
- Only the operations listed in the subject can be used to sort.

## Skills

- Algorithm design and complexity optimization
- Data structures (stacks, linked lists)
- Input parsing and validation
- Writing and measuring an algorithm against a benchmark