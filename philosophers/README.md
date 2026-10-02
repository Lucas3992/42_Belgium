# philosophers

The goal of this project is to solve the classic dining philosophers problem, to learn how to use threads and mutexes and how to avoid data races and deadlocks.

Philosophers sit around a table. Each one alternates between eating, sleeping and thinking, and needs two forks to eat, with one fork between each pair of philosophers. Each philosopher is a separate thread, and each fork is protected by a mutex so that a fork can never be held by two philosophers at once. The simulation stops when a philosopher dies of starvation, or when every philosopher has eaten the required number of times (if given). The main difficulties are avoiding deadlocks and data races, handling the single-philosopher case (only one fork available), and checking for death accurately in time so that no state message is printed after a death.

This README was written after the project was pushed. The subject PDF may have changed since then, so what is described here may no longer match the current subject 100%.

## Build and run

```bash
cd philosophers/philo
make          # builds philo
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # rebuilds everything
```

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep 
(optional: number_of_times_each_philosopher_must_eat)
```

Times are in milliseconds. Example with 5 philosophers:

```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
```

## Arguments

| Argument | Meaning |
|---|---|
| `number_of_philosophers` | Number of philosophers (and of forks) |
| `time_to_die` | Time without eating after which a philosopher dies |
| `time_to_eat` | Time a philosopher spends eating (holding two forks) |
| `time_to_sleep` | Time a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | Optional. The simulation stops when everyone has eaten this many times |

## Constraints

- One thread per philosopher, one mutex-protected fork between each pair of philosophers.
- Allowed functions include `pthread_create`, `pthread_join`, `pthread_mutex_*`, `usleep`, `gettimeofday`, `malloc` and `free`.
- No global variables shared between threads without protection, and libft is not allowed.

## Skills

- Multithreading with POSIX threads
- Mutexes and protection of shared data
- Deadlock and data race prevention
- Time handling with `gettimeofday`
- Debugging concurrent programs