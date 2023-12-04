#include "../include/maze.h"

int
main(int argc, char* args[])
{
  struct Cell** grid = generate_grid();
  display_maze(grid);
}
