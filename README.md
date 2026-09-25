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
| `palindrome.c` | Checks whether text reads the same backward |
| `sorting.c` | Sorts up to 100 integers |
| `test.c` | Sorts the characters in a word |
| `stm.c` | Student marks and grade summary |
| `pointer_array_stats.c` | Uses pointers and dynamic memory for minimum, maximum, average, median, and descending order |
| `file_handling.c` | Writes a message to a file and reads it back |
| `tic_tac_toe.c` | Plays console Tic-tac-toe against the computer |

## Build

Compile any program with a C11 compiler:

```text
gcc -std=c11 -Wall -Wextra -Wpedantic filename.c -o program
```

Run the resulting executable from your terminal.

## Check the programs

With GCC and Python 3 on your PATH, run:

```text
python tests/check_programs.py
```

This compiles all examples with warnings treated as errors in a temporary
directory, then checks array statistics at integer limits, interrupted marks
entry, and calculator error handling. Existing executables are left untouched.
