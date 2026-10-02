# minitalk

The goal of this project is to build a small communication program made of a client and a server that exchange messages using only UNIX signals.

The server starts first and prints its PID. The client takes the server PID and a string, then sends the string bit by bit using only `SIGUSR1` and `SIGUSR2`. The server rebuilds each character from the received bits and prints the message. The main difficulties are encoding characters into a signal sequence, keeping the client and server synchronized (signals of the same type are not queued by Linux, so they can be lost), and displaying the message fast enough to handle several clients in a row without restarting the server.

This README was written after the project was pushed. The subject PDF may have changed since then, so what is described here may no longer match the current subject 100%.

## Build and run

```bash
make          # builds server and client (bonus included)
make clean    # removes object files
make fclean   # removes object files and binaries
make re       # rebuilds everything
```

In a first terminal, start the server. It prints its PID:

```bash
./server
```

In a second terminal, send a message with the client:

```bash
./client <server_pid> "Hello 42!"
```

## Features

- The server prints its PID at launch.
- The client sends any string to the server using the server PID.
- Communication uses only `SIGUSR1` and `SIGUSR2`.
- The server displays the message right away and can receive messages from several clients in a row without restarting.

## Bonus

The bonus features are implemented directly in the main source files (`client.c` and `server.c`), so there are no separate `_bonus` files:

- Acknowledgment: the server sends a signal back to the client to confirm that each message was received.
- Unicode support: multi-byte characters (accents, emojis...) are sent and displayed correctly.

## Constraints

- Only UNIX signals can be used for communication between the client and the server.
- Only the two signals `SIGUSR1` and `SIGUSR2` are allowed.
- The server must be fast: displaying 100 characters must take far less than one second.

## Skills

- UNIX signals and signal handlers (`signal` / `sigaction`, `kill`)
- Bitwise operations to encode and decode data
- Synchronization between two processes
- Handling multi-byte (UTF-8) characters