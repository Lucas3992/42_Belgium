# cub3d

The goal of this project is to build a small 3D game from a first-person point of view, inspired by Wolfenstein 3D, using ray-casting and the MiniLibX graphics library.

The program reads a `.cub` scene file (wall textures, floor and ceiling colors, and a map), then draws the inside of the maze in real time. The main difficulties are parsing and validating the map (it must be closed by walls, with a single player start), the ray-casting math (finding which wall each ray hits and projecting it on screen), and keeping the window and events smooth and leak-free.

This README was written after the project was pushed. The subject PDF may have changed since then, so what is described here may no longer match the current subject 100%.

## Build and run

```bash
make            # builds cub3D
./cub3D path/to/map.cub
make bonus      # builds the bonus version
make clean      # removes object files
make fclean     # removes object files and binaries
make re         # rebuilds everything
```

## Requirements

- `cc` and `make`
- The X11 development libraries for MiniLibX. On Debian/Ubuntu: `sudo apt install xorg libxext-dev libbsd-dev`

## Features (mandatory)

- Wall textures that depend on the wall orientation (North, South, East, West).
- Different floor and ceiling colors.
- Move with `W` `A` `S` `D`, look left and right with the arrow keys.
- `ESC` or the window cross closes the program cleanly.
- Scene file parsing with explicit error messages (`Error` followed by a description).

Example of a minimal `.cub` file:

```text
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

## Bonus

The bonus version (`make bonus`, sources in `bonus/`) adds on top of the mandatory part:

- A minimap.
- Enemies.
- A weapon with shooting.
- Music.
- Additional maps in `bonus/maps/`.

## Skills

- Ray-casting and applied math
- Graphics and event handling with MiniLibX
- File parsing and input validation
- Project structure with a large codebase and a Makefile
