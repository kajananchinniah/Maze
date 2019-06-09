#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_timer.h"
#include "SDL2/SDL_image.h"

#include "maze.h"

int main(void)
{
   int isOpen = 0;
   SDL_Window *window;
   char* window_title = "Maze";
   int window_x = SDL_WINDOWPOS_CENTERED;
   int window_y = SDL_WINDOWPOS_CENTERED;
   int window_w = 650;
   int window_h = 650;
   Uint32 window_flags = 0;


   SDL_Renderer* rend;
   Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
   int render_index = -1;
   int background_r = 0;
   int background_g = 0;
   int background_b = 0;
   int background_a = 255;

   Maze maze;
   int maze_nrows = 25;
   int maze_ncols = 25;

   SDL_Rect cell;
   int cell_x = 0;
   int cell_y = 0;
   int cell_w = window_w / maze_nrows;
   int cell_h = window_h / maze_ncols;
   int cell_r = 255;
   int cell_g = 255;
   int cell_b = 255;
   int cell_a = 255;

   cell.x = cell_x;
   cell.y = cell_y;
   cell.w = cell_w;
   cell.h = cell_h;
    
   SDL_Init(SDL_INIT_VIDEO);

   window = SDL_CreateWindow(window_title, window_x, window_y, window_w, window_h, window_flags);
   if (window == NULL) 
   {
      printf("Error: cannot create window: %s\n", SDL_GetError());
      return -1;
   }

   rend = SDL_CreateRenderer(window, render_index, render_flags);
   if (rend == NULL)
   {
      printf("Error: cannot create renderer: %s\n", SDL_GetError());
      return -1;
   }

   SDL_SetRenderDrawColor(rend, background_r, background_g, background_b, background_a);
   SDL_RenderClear(rend);
   
   maze = createRandomMaze(maze_nrows, maze_ncols);

   for (int i = 0; i < maze_nrows; i++)
   {
      cell.y = i * cell_h;
      for (int k = 0; k < maze_ncols; k++)
      {
         cell.x = k * cell_w;
	 if (maze.arr[i][k] == getMazeEmptyValue())
	 {
	    SDL_SetRenderDrawColor(rend, cell_r, cell_g, cell_b, cell_a);
	    SDL_RenderFillRect(rend, &cell);
	    SDL_RenderPresent(rend);
	 }
      }
   }

   while (isOpen == 0)
   {
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
         if(event.type == SDL_QUIT)
	 {
            isOpen = 1;
	 }
      }
   }

   SDL_DestroyWindow(window);
   SDL_Quit();

   return 0;
   
}
