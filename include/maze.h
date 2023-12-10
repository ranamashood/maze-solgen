#ifndef MAZE_H
#define MAZE_H

#include "a_star.h"
#include "cell.h"
#include <SDL2/SDL_render.h>

struct Cell**
generate_grid(SDL_Renderer* renderer);

void
randomized_dfs(SDL_Renderer* renderer, struct Cell** grid, struct Cell* cell);

struct Cell*
get_neighbour(struct Cell** grid, struct Cell cell);

void
draw_cell_top(SDL_Renderer* renderer, struct Cell cell);

void
draw_cell_right(SDL_Renderer* renderer, struct Cell cell);

void
draw_cell_bottom(SDL_Renderer* renderer, struct Cell cell);

void
draw_cell_left(SDL_Renderer* renderer, struct Cell cell);

void
draw_cell_helper(void (*draw_cell_border)(SDL_Renderer*, struct Cell),
                 SDL_Renderer* renderer,
                 struct Cell cell);

void
connect_cells(SDL_Renderer* renderer,
              struct Cell* curr_cell,
              struct Cell* next_cell);

void
display_maze(SDL_Renderer* renderer, struct Cell** grid);

void
draw_path_cell(SDL_Renderer* renderer,
               struct Path path,
               int j,
               int cell_index,
               int other_cell_index);

void
draw_path(SDL_Renderer* renderer, struct Path path);

void
free_grid(struct Cell** grid);

#endif // !MAZE_H
