*This project has been created as part of the 42 curriculum by tsaby.*

# so_long

## Description

**so_long** is a small tile-based 2D game written in C on top of the **MiniLibX** graphical library, built as part of the 42 curriculum.

The player is dropped into a map described in a plain text file. The goal is simple: collect every collectible on the map, then reach the exit. Movement is limited to the four cardinal directions, walls block the way, and every valid move is counted and displayed.

The point of the project is not the game itself but everything around it. A map file has to be read line by line and stored in memory, then validated before a single pixel is drawn: correct file extension, allowed characters only, rectangular shape, walls all around the border, exactly one player, exactly one exit, at least one collectible — and, above all, a path that actually connects the player to every collectible and to the exit. That last check is done with a flood fill on a copy of the map, so the original grid stays intact.

The rest is event-driven programming: hooks for key presses and for closing the window, a render pass that walks the grid and puts one image per tile, and a cleanup routine that destroys images, window and display, then frees everything before exiting.

## Instructions

### Requirements

- `gcc` and `make`
- X11 development headers and zlib

```bash
# Debian / Ubuntu
sudo apt install gcc make xorg libxext-dev zlib1g-dev
```

### MiniLibX

**MiniLibX is not included in this repository.** Download it, place it at the root of the project and rename the folder to `mlx_linux` — the Makefile expects that exact name and builds the library itself.

```
so_long/
├── mlx_linux/   <-- here
├── Makefile
└── ...
```

### Compilation

```bash
git clone https://github.com/sabytheo/so_long.git
cd so_long
# add mlx_linux/ as described above
make
```

| Rule | Effect |
| --- | --- |
| `make` | Builds MiniLibX, then the `so_long` binary |
| `make clean` | Removes object files |
| `make fclean` | Removes object files and the binary |
| `make re` | Full rebuild |

### Execution

The program takes exactly one argument: a map file with the `.ber` extension.

```bash
./so_long maps/map.ber
```

Images are loaded from the `img/` folder using relative paths, so the game must be launched from the root of the project.

## Gameplay

| Key | Action |
| --- | --- |
| `W` | Move up |
| `A` | Move left |
| `S` | Move down |
| `D` | Move right |
| `Esc` | Quit |

Closing the window with the title bar also exits cleanly.

The move counter is printed to the terminal on every valid move and drawn inside the window. The exit stays closed until the last collectible is picked up; once the map is clear it switches to its open sprite and stepping on it wins the game.

## Map format

Maps are plain text files with the `.ber` extension, made of five characters:

| Character | Meaning |
| --- | --- |
| `0` | Empty floor |
| `1` | Wall |
| `P` | Player starting position — exactly one |
| `C` | Collectible — at least one |
| `E` | Exit — exactly one |

```
1111111111111
100000000C001
10000P000001
1000C00000E01
1111111111111
```

A map is rejected, with an explicit message on the standard error output, when it contains a forbidden character, is not rectangular, is not fully surrounded by walls, has the wrong number of players, exits or collectibles, or offers no valid path to the collectibles and the exit.

## Technical choices

**Reading the map** — the file is read with `get_next_line` and the grid grows one line at a time: each new line triggers the allocation of a slightly larger array of pointers, into which the previous lines are copied. No size is known in advance, and the map is never read twice.

**Validating the path** — a recursive four-direction flood fill starts from the player's position and marks every reachable floor tile. It runs on a *copy* of the grid, since the fill destroys what it walks over. The map is valid if no collectible survived the fill and if the exit is adjacent to at least one flooded tile. The copy is freed immediately afterwards, whether the check passed or failed.

**Storing the state** — a single structure holds the whole game: dimensions, counters, player position, move count, the grid, the six image pointers and the MiniLibX handles. It is zeroed at startup, so the cleanup routine can be called at any point during initialisation and only free what has actually been allocated.

**The grid is the state** — the player is not tracked separately from the map: moving rewrites the target tile as `P` and the previous one as `0`. Collecting works the same way, by overwriting a `C` and decrementing the counter. There is therefore only one source of truth to keep consistent.

**Rendering** — sprites are 120 × 120 pixel XPM files, and the window is sized to the map. Each key press that results in a valid move triggers a full redraw of the grid.

**Exiting** — one function handles every exit path, whether it comes from an invalid map, a failed allocation, `Esc` or the window being closed. It destroys the images, the window and the display, frees the grid, closes the file descriptor and leaves.

## Project structure

```
so_long/
├── Makefile
├── include/
│   └── so_long.h
├── sources/
│   ├── so_long.c        # entry point, argument check, hooks, cleanup
│   ├── init_map.c       # reading the .ber file into memory
│   ├── check_error.c    # characters, counts, shape, borders
│   ├── check_path.c     # flood fill on a copy of the map
│   ├── print_map.c      # loading sprites and drawing the grid
│   └── keycontrol.c     # key handling and movement rules
├── img/                 # 120x120 XPM sprites
├── maps/                # example maps
└── Libft/               # libft, ft_printf, get_next_line
```

## Resources

### Documentation and references

- [42 Docs — MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx) — the reference documentation for the library: window creation, images, hooks and the event loop
- [MiniLibX repository](https://github.com/42Paris/minilibx-linux) — source and installation of the Linux version
- `man X11` and the X11 keysym table — for the key codes used by the key hooks
- [XPM file format specification](https://www.xfree86.org/current/xpm.pdf) — structure of the sprite files loaded by `mlx_xpm_file_to_image`
- [Flood fill — Wikipedia](https://en.wikipedia.org/wiki/Flood_fill) — the algorithm used to prove the map is solvable
- 42 projects reused here: **Libft**, **ft_printf** and **get_next_line**
