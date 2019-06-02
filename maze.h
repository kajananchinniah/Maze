#ifndef MAZE_H_
#define MAZE_H

typedef struct position
{
  int x;
  int y;
} position;

typedef struct stack
{
   struct position p;
   struct stack *next;
} stack;

typedef struct Maze
{
   int **arr;
   int **unvisited;
   int n_rows;
   int n_cols;
} Maze;

//Position functions
int getPosX(position p);
int getPosY(position p);
int setPosX(position *p, int x);
int setPosY(position *p, int y);
int getPositiveXMovement(int x);
int getNegativeYMovement(int y);
int getPositiveYMovement(int y);
int getNegativeXMovement(int x);

//Stack functions
int push(stack **head, position p);
position pop(stack **head);
int printStack(stack *head);
int isStackEmpty(stack *head); 

//Maze functions
int init_maze(Maze *maze, int n_rows, int n_cols);
int generateMaze(Maze *maze, position start_pos);
int formPath(Maze *maze, position curr_pos, position selected_neighbour);
position getRandomUnvisitedNeighbour(Maze maze, position curr_pos);
int isUnvisitedNeighbours(Maze maze, position curr_pos);
int printMaze(Maze maze);

#endif
