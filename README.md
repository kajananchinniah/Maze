# Maze

Currently, maze.h and maze.c both just contains structs and functions that lead to the goal of generating mazes on console. main.c uses SDL to generate the maze and visualize it. The maze itself is represented with a 2 dimensional array, with 1 representing a wall and 0 representing an empty space. Note: an odd number of columns and rows should be used for proper generation & there should be more than 3 cols and rows.

For the makefile, I took the one used in the CS50 SDL seminar: https://github.com/tlively/sdl_seminar

Future plans are:
2) Implement a solver for the maze (probably will be using DF traversal since I use a stack anyways)

3) Create a simple maze game
