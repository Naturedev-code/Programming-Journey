# Programming Journey

A collection of beginner-friendly C programs that demonstrate input handling,
control flow, functions, arrays, strings, structures, dynamic memory, and
pointer arithmetic.

## Programs

| File | Description |
| --- | --- |
| `hello.c` | Prints a first message |
| `calculator.c` | Performs basic arithmetic safely |
| `numberguess.c` | Random number guessing game |
| `rps.c` | Rock, Paper, Scissors game with score tracking |
| `factorial.c` | Calculates factorials from 0 to 20 |
| `prime_checker.c` | Checks whether a whole number from 0 to 2147483647 is prime |
| `palindrome.c` | Checks whether text reads the same backward |
| `sorting.c` | Sorts up to 100 integers |
| `test.c` | Sorts the characters in a word |
| `stm.c` | Student marks and grade summary |
| `pointer_array_stats.c` | Uses pointers and dynamic memory for minimum, maximum, average, median, and descending order |
| `file_handling.c` | Writes a message to a file and reads it back |
| `tic_tac_toe.c` | Plays console Tic-tac-toe against the computer |
| `maze_cartographer.c` | Generates reproducible mazes, hides treasure in the farthest room, and reveals the shortest route |

## Build

Compile any program with a C11 compiler:

```text
gcc -std=c11 -Wall -Wextra -Wpedantic filename.c -o program
```

Run the resulting executable from your terminal.

## Maze Cartographer

Explore a different maze for every seed. The generator uses iterative depth-first
search to carve a connected maze with exactly one route between any two rooms.
Breadth-first search places the treasure in a room farthest from the start.

```text
gcc -std=c11 -Wall -Wextra -Wpedantic maze_cartographer.c -o maze_cartographer
./maze_cartographer 12 8 42
./maze_cartographer 12 8 42 --solve
```

On Windows PowerShell, use `./maze_cartographer.exe`. `S` marks the start,
`T` marks the treasure, and `--solve` draws the route with dots. Reusing the
dimensions and seed reproduces the same maze. Dimensions range from 2 to 30
rooms and seeds from 0 to 4294967295. With no arguments, the program generates
a 12 by 8 maze using the current time as its seed. No external libraries are needed.

Run `python tests/check_maze.py` to compile in a temporary directory and check
connectivity, absence of cycles, treasure distance, reproducibility, solution
paths, and invalid arguments.

## Check the programs

With GCC and Python 3 on your PATH, run:

```text
python tests/check_programs.py
```

This compiles all examples with warnings treated as errors in a temporary
directory, then checks array statistics at integer limits, interrupted marks
entry, and calculator error handling. Existing executables are left untouched.
