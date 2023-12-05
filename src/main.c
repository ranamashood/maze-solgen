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
  // struct CellPos path[6] = { { .x = 0, .y = 0 }, { .x = 1, .y = 0 },
  //                            { .x = 2, .y = 0 }, { .x = 2, .y = 1 },
  //                            { .x = 2, .y = 2 }, { .x = 2, .y = 2 } };
  // draw_path(path, 6, renderer);

  // SDL_RenderPresent(renderer);

  gui_loop();

  free(grid);
  SDL_Quit();
}
