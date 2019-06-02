#include "maze.h"
#include <stdio.h>
#include <stdlib.h>

//Position functions
int getPosX(position p)
{
   return p.x;
}

int  getPosY(position p)
{
   return p.y;
}

int setPosX(position *p, int x)
{
   if (p == NULL) { return -1; }
   p->x = x;
   return 0;
}

int setPosY(position *p, int y)
{
   if (p == NULL) { return -1; }
   p->y = y;
   return 0;
}

//The getDirectionVariableMovement functions move the variable to the cell in it's respective direction
int getPositiveXMovement(int x) 
{
   int forward_pos = x + 2;
   return forward_pos;
}

int getNegativeYMovement(int y) 
{
   int left_pos = y - 2;
   return left_pos;
}

int getPositiveYMovement(int y) 
{
   int right_pos = y + 2;
   return right_pos;
}

int getNegativeXMovement(int x)
{
   int backward_pos = x - 2;
   return backward_pos;
}

//Stack functions
int push(stack **x, position p)
{
   stack *tmp = NULL;
   if (x == NULL) 
   {
      printf("ERROR: Cannot allocate memory to stack");
      return -1;
   }

   if (*x == NULL)
   {
      *x = (stack *)malloc(sizeof(stack));
      (*x)->p = p;
      (*x)->next = NULL;
      return 0;
   }

   else
   {
      stack *tmp = *x;
      (*x) = (stack *)malloc(sizeof(stack));
      (*x)->p = p;
      (*x)->next = tmp;
      return 0;   
   }
}

position pop(stack **x)
{
   stack* tmp = NULL;
   position r_val;
   if (x == NULL)
   {
      exit(-1);
   }
   else
   {
      tmp = *x;
      r_val = tmp->p;
      (*x) = (*x)->next;
      free(tmp);
      return r_val;
   }
}

int printStack(stack *head)
{
   stack *tmp = NULL;
   for (tmp = head; tmp != NULL; tmp = tmp->next)
   {
      printf("(%d,%d)->", tmp->p.x, tmp->p.y);
   }
   return 0;
}

int isStackEmpty(stack *head)
{
   if (head == NULL)
   {
      return 1; //true
   }
   return 0; //false
}

//Maze functions
//Initializes a n_rows * n_cols maze. Each cell will be surrounded by walls around it
int init_maze(Maze* maze, int n_rows, int n_cols)
{
   if (maze == NULL)
   {
      maze = malloc(sizeof(Maze));
      if (maze == NULL)
      {
	 printf("Error: Unable to malloc memory");
         return -1; //error
      }
   }

   //initializing 2D array
   maze->arr = (int **) malloc(sizeof(int *)*n_rows);
   maze->unvisited = (int **) malloc(sizeof(int *) * n_rows);
   for (int i = 0; i < n_rows; i++)
   {
       maze->arr[i] = (int *) malloc(n_cols * sizeof(int));
       maze->unvisited[i] = (int *) malloc(sizeof(int) * n_cols);
   }
   //assigning default value of one
   for (int i = 0; i < n_rows; i++)
   {
      for (int k = 0; k < n_cols; k++)
      {
	 if (i % 2 != 0 && k % 2 != 0)
	 {
            maze->arr[i][k] = 0; // represents a cell
	    maze->unvisited[i][k] = 0; // represents unvisited cell
	 }
	 else
	 {
            maze->arr[i][k] = 1; // 1s represent walls 
            maze->unvisited[i][k] = -1; // walls (i.e. unvisitable)
	 }
      }
   }
   maze->n_rows = n_rows;
   maze->n_cols = n_cols; 
   return 0;
}

int generateMaze(Maze *maze, position start_pos)
{
   position curr_pos;
   if (maze->arr[start_pos.x][start_pos.y] != 0) 
   {
      printf("Not valid starting position");
      return -1;
   }
   //generating the maze. I used recursive backtracking. Implementation based on wikipedia's pseudocode description
   curr_pos = start_pos;
   stack *head = NULL;
   push(&head, curr_pos);
   while(isStackEmpty(head) == 0)
   {
      if (isUnvisitedNeighbours(*maze, curr_pos) == 1)
      {
         position selected_neighbour = getRandomUnvisitedNeighbour(*maze, curr_pos);
         formPath(maze, curr_pos, selected_neighbour);
	 push(&head, selected_neighbour);
	 maze->unvisited[selected_neighbour.x][selected_neighbour.y] = 1;
	 curr_pos = selected_neighbour;
      }

      else
      {
         curr_pos = pop(&head);
      }
   } 
   return 0;   
}

//formPath deletes a wall between two cells
int formPath(Maze *maze, position curr_pos, position selected_neighbour)
{
   int offset_x = curr_pos.x - selected_neighbour.x;
   int offset_y = curr_pos.y - selected_neighbour.y;

   if (offset_x == -2)
   {
      maze->arr[curr_pos.x + 1][curr_pos.y] = 0;
   }

   if (offset_x == 2)
   {
      maze->arr[curr_pos.x - 1][curr_pos.y] = 0;
   }

   if (offset_y == 2)
   {
      maze->arr[curr_pos.x][curr_pos.y - 1] = 0;
   }

   if (offset_y == -2)
   {
      maze->arr[curr_pos.x][curr_pos.y + 1] = 0;
   }

   return 0;
}

//randomly returns an avaliable, unvisited neighbouring cell
position getRandomUnvisitedNeighbour(Maze maze, position curr_pos)
{
   position r_val;
   int random_choice = 0;

   int curr_x = curr_pos.x;
   int curr_y = curr_pos.y;
   int negative_y_bound = 1;
   int positive_y_bound = maze.n_cols - 2;
   int positive_x_bound = maze.n_rows - 2;
   int negative_x_bound = 1;


   while(1 == 1)
   {
      random_choice = rand() % 4;
      if (random_choice == 0 && curr_y != negative_y_bound && maze.unvisited[curr_x][getNegativeYMovement(curr_y)] == 0)
      {
         r_val.x = curr_x;
	 r_val.y = getNegativeYMovement(curr_y);
	 return r_val;
      }

      if (random_choice == 1 && curr_y != positive_y_bound && maze.unvisited[curr_x][getPositiveYMovement(curr_y)] == 0)
      {
         r_val.x = curr_x;
	 r_val.y = getPositiveYMovement(curr_y);
	 return r_val;
      }

      if (random_choice == 2 && curr_x != negative_x_bound && maze.unvisited[getNegativeXMovement(curr_x)][curr_y] == 0)
      {
	 r_val.x = getNegativeXMovement(curr_x);
	 r_val.y = curr_y;
	 return r_val;
      } 

      if (random_choice == 3 && curr_x != positive_x_bound && maze.unvisited[getPositiveXMovement(curr_x)][curr_y] == 0)
      {
         r_val.x = getPositiveXMovement(curr_x);
	 r_val.y = curr_y;
	 return r_val;
      }
   }

   printf("Unable to locate neighbours. Error has occured");
   exit(-1);
}

//checks if a position has neighbours avaliable
int isUnvisitedNeighbours(Maze maze, position curr_pos)
{
   int curr_x = curr_pos.x;
   int curr_y = curr_pos.y;
   int negative_y_bound = 1;
   int positive_y_bound = maze.n_cols - 2;
   int positive_x_bound = maze.n_rows - 2;
   int negative_x_bound = 1;

   if (curr_y != negative_y_bound && maze.unvisited[curr_x][getNegativeYMovement(curr_y)] == 0)
   {
      return 1;
   }

   if (curr_y != positive_y_bound && maze.unvisited[curr_x][getPositiveYMovement(curr_y)] == 0)
   {
      return 1;
   }

   if (curr_x != negative_x_bound && maze.unvisited[getNegativeXMovement(curr_x)][curr_y] == 0)
   {
      return 1;
   }

   if (curr_x != positive_x_bound && maze.unvisited[getPositiveXMovement(curr_x)][curr_y] == 0)
   {
      return 1;
   }

   return 0;
}

//prints the maze, * represents empty space, X represents a wall
int printMaze(Maze maze)
{
   for (int i = 0; i < maze.n_rows; i++)
   {
      for (int k = 0; k < maze.n_cols; k++)
      {
         if (maze.arr[i][k] == 0)
	 {
            printf("*");
	 }
	 else 
         {
            printf("X");
	 }
      }
   printf("\n");
   }
   return 0;
}
