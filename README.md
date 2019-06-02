# Maze

Currently, this just contains structs and functions that generate mazes on console. main.c contains sample usage for initializing the maze, generating and then printing it out. Note: an odd number of columns and rows should be used for proper generation & there should be more than 3 cols and rows.

Sample output (7x7 maze) starting at (1,1), where X represents a wall and O represents an empty space:

XXXXXXX <br />
XOOOXOX <br />
XOXOXOX <br />
XOXOOOX <br />
XXXXXOX <br />
XOOOOOX <br />
XXXXXXX <br />

I'm temporarily puttingthis project on hold.

Future plans are:
1) Implement a GUI for visualizing the maze. I might make it into a maze game. 
2) Implement a solver for the maze (probably will be using DF traversal since I use a stack anyways)
3) Implement a function for choosing a starting and end point
