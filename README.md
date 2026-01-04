8-Puzzle — C

Minimal, clean implementation of the 8-Puzzle (playable + foundation for BFS / IDDFS / A*).

Features

3×3 board, guaranteed-solvable shuffle

Manual play (W/A/S/D)

Modular C code (clear include/ + src/)

Quick start
gcc src/*.c -I include -o 8puzzle    # build
./8puzzle                            # run

Controls
W  up   | A left | S down | D right | Q quit

Project (core)
include/    # headers
src/
  main.c
  puzzle.c
  busca.c
  estruturas.c

Goal state
1 2 3
4 5 6
7 8 _

Note

Initial board produced by applying random valid moves to the goal (always solvable).
