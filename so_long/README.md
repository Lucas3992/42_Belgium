# so_long

The goal of this project is to build a small 2D game with the MiniLibX graphics library, where the player collects every collectible on a map and then reaches the exit.

The program takes a map file with the `.ber` extension, validates it, and displays it in a window. The player moves with the keyboard, cannot walk through walls, and the number of moves is printed in the shell after every move. The main difficulties are the map validation (rectangular, enclosed by walls, exactly one exit and one start, at least one collectible, and a valid path to every collectible and to the exit), the graphics and event handling with MiniLibX, and closing everything cleanly without memory leaks.

This README was written after the project was pushed. The subject PDF may have changed since then, so what is described here may no longer match the current subject 100%.

## Build and run

```bash
make          # builds so_long
./so_long maps/<map>.ber
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # rebuilds everything
```

## Requirements

- `cc` and `make`
- The X11 development libraries for MiniLibX. On Debian/Ubuntu: `sudo apt install xorg libxext-dev libbsd-dev`

## Map format

A map is a `.ber` file made of 5 characters:

| Character | Meaning |
|---|---|
| `0` | Empty space |
| `1` | Wall |
| `C` | Collectible |
| `E` | Exit |
| `P` | Player start |

Example of a valid map:

```text
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

A map is valid only if it is rectangular, surrounded by walls, has exactly one exit and one start position, at least one collectible, and a valid path to reach everything. Any problem makes the program print `Error` followed by an explicit message, then exit cleanly.

## Gameplay

- Collect all collectibles, then reach the exit.
- Move with the `W` `A` `S` `D` keys.
- The player cannot move into walls.
- The number of moves is displayed in the shell at every move.
- `ESC` or the window cross closes the game cleanly.

## Project structure

The sources are split by role: `parsing/` (map reading and validation), `graphic/` (rendering), `controls/` (key events), `maps/` (example maps), with my own `gnl/` and `printf/` helpers.

## Skills

- Graphics programming and event handling with MiniLibX
- File parsing and input validation
- Path-finding on a grid (flood fill)
- Clean resource management in C