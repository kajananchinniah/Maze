#include "maze.h"

int main(int argc, char *argv[])
{
   Maze x;
   position start_pos;
   start_pos.x = 1;
   start_pos.y = 1;
   int n_rows = 25;
   int n_cols = 25;
   init_maze(&x, n_rows, n_cols);
   generateMaze(&x, start_pos);
   printMaze(x);
   return 0;
}
