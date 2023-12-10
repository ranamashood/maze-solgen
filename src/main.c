#include "../include/config.h"
#include "../include/gui.h"
#include "../include/maze.h"
#include <SDL2/SDL.h>

int
main(int argc, char* args[])
{
  parse_config_file("examples/sample-config");

  SDL_Renderer* renderer = gui_init("Maze Solgen");

  struct Cell** grid = generate_grid(renderer);
  display_maze(renderer, grid);

  struct Pair src = { 0, { 0, 0 } };
  struct Pair dest = { 0, { 5, 0 } };
  struct Path path = aStarSearch(grid, src, dest);
  draw_path(renderer, path);

  gui_loop();

  free_path(&path);
  free_grid(grid);
  SDL_Quit();
}
