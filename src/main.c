#include "../include/gui.h"
#include "../include/maze.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

int
main(int argc, char* args[])
{
  SDL_Renderer* renderer = gui_init("Maze Solgen");

  struct Cell** grid = generate_grid();
  display_maze(grid, renderer);

  gui_loop();

  free(grid);
  SDL_Quit();
}
