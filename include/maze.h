#ifndef CELL_H
#define CELL_H

#include <SDL2/SDL_render.h>
#include <stdbool.h>

struct Cell
{
  int x;
  int y;
  bool visited;
  bool top;
  bool right;
  bool bottom;
  bool left;
};

struct CellPos
{
  int x;
  int y;
};

struct Cell**
generate_grid();

void
randomized_dfs(struct Cell** grid, struct Cell* cell);

struct Cell*
get_neighbour(struct Cell** grid, struct Cell cell);

void
connect_cells(struct Cell* curr_cell, struct Cell* next_cell);

void
display_maze(struct Cell** grid, SDL_Renderer* renderer);

void
draw_path(struct CellPos path[], int path_size, SDL_Renderer* renderer);

#endif // !CELL_H
