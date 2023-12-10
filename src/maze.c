#include "../include/maze.h"
#include "../include/config.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <time.h>

// TODO: set maze width and height with roll number
// const int MAZE_WIDTH = 50;
// const int MAZE_HEIGHT = 50;
// const int CELL_SIZE = 10;

struct Cell**
generate_grid(SDL_Renderer* renderer)
{
  struct Cell** grid =
    (struct Cell**)malloc(MAZE_HEIGHT * sizeof(struct Cell*));
  for (int y = 0; y < MAZE_HEIGHT; y++) {
    grid[y] = (struct Cell*)malloc(MAZE_WIDTH * sizeof(struct Cell));
  }

  for (int y = 0; y < MAZE_HEIGHT; y++) {
    for (int x = 0; x < MAZE_WIDTH; x++) {
      grid[y][x] = (struct Cell){
        .x = x,
        .y = y,
        .visited = false,
        .top = true,
        .right = true,
        .bottom = true,
        .left = true,
      };
    }
  }

  // struct Cell* curr_cell = &grid[MAZE_HEIGHT / 3][MAZE_WIDTH / 2];
  // TODO: choose curr_cell with roll number
  struct Cell* start_cell = &grid[0][0];

  srand(time(NULL));
  randomized_dfs(renderer, grid, start_cell);

  return grid;
}

void
randomized_dfs(SDL_Renderer* renderer, struct Cell** grid, struct Cell* cell)
{
  if (GRID_CELL_ANIMATION)
    SDL_Delay(GRID_CELL_DELAY);

  bool iteration_finished = true;
  cell->visited = true;
  struct Cell* next_cell = get_neighbour(grid, *cell);

  while (next_cell != NULL) {
    if (GRID_CELL_ANIMATION) {
      display_maze(renderer, grid);
      SDL_Delay(GRID_CELL_DELAY);
    }

    connect_cells(renderer, cell, next_cell);
    randomized_dfs(renderer, grid, next_cell);
    next_cell = get_neighbour(grid, *cell);
    iteration_finished = false;
  }

  if (GRID_ITERATION_ANIMATION && iteration_finished) {
    SDL_Delay(GRID_ITERATION_DELAY);
  }
}

struct Cell*
get_neighbour(struct Cell** grid, struct Cell cell)
{
  // TODO: use size_t in project instead of int for sizes
  // TODO: use pre increment instead of post increment
  int size = 0;
  struct Cell* neighours[4];

  if (cell.y > 0 && !grid[cell.y - 1][cell.x].visited)
    neighours[size++] = &grid[cell.y - 1][cell.x];

  if (cell.x > 0 && !grid[cell.y][cell.x - 1].visited)
    neighours[size++] = &grid[cell.y][cell.x - 1];

  if (cell.y < MAZE_HEIGHT - 1 && !grid[cell.y + 1][cell.x].visited)
    neighours[size++] = &grid[cell.y + 1][cell.x];

  if (cell.x < MAZE_WIDTH - 1 && !grid[cell.y][cell.x + 1].visited)
    neighours[size++] = &grid[cell.y][cell.x + 1];

  if (!size)
    return NULL;
  else
    return neighours[rand() % size];
}

void
draw_cell_top(SDL_Renderer* renderer, struct Cell cell)
{
  SDL_RenderDrawLine(renderer,
                     cell.x * CELL_SIZE,
                     cell.y * CELL_SIZE,
                     (cell.x * CELL_SIZE) + CELL_SIZE,
                     cell.y * CELL_SIZE);
}

void
draw_cell_right(SDL_Renderer* renderer, struct Cell cell)
{
  SDL_RenderDrawLine(renderer,
                     (cell.x * CELL_SIZE) + CELL_SIZE,
                     cell.y * CELL_SIZE,
                     (cell.x * CELL_SIZE) + CELL_SIZE,
                     (cell.y * CELL_SIZE) + CELL_SIZE);
}

void
draw_cell_bottom(SDL_Renderer* renderer, struct Cell cell)
{
  SDL_RenderDrawLine(renderer,
                     (cell.x * CELL_SIZE) + CELL_SIZE,
                     (cell.y * CELL_SIZE) + CELL_SIZE,
                     cell.x * CELL_SIZE,
                     (cell.y * CELL_SIZE) + CELL_SIZE);
}

void
draw_cell_left(SDL_Renderer* renderer, struct Cell cell)
{
  SDL_RenderDrawLine(renderer,
                     cell.x * CELL_SIZE,
                     (cell.y * CELL_SIZE) + CELL_SIZE,
                     cell.x * CELL_SIZE,
                     cell.y * CELL_SIZE);
}

void
draw_cell_helper(void (*draw_cell_border)(SDL_Renderer*, struct Cell),
                 SDL_Renderer* renderer,
                 struct Cell cell)
{
  if (GRID_CELL_ANIMATION || GRID_ITERATION_ANIMATION) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    draw_cell_border(renderer, cell);
    SDL_RenderPresent(renderer);
  }
}

void
connect_cells(SDL_Renderer* renderer,
              struct Cell* curr_cell,
              struct Cell* next_cell)
{
  if ((curr_cell->x == next_cell->x) && (curr_cell->y == next_cell->y + 1)) {
    curr_cell->top = next_cell->bottom = false;
    draw_cell_helper(draw_cell_top, renderer, *curr_cell);
  }

  if (curr_cell->x == next_cell->x && curr_cell->y == next_cell->y - 1) {
    curr_cell->bottom = next_cell->top = false;
    draw_cell_helper(draw_cell_bottom, renderer, *curr_cell);
  }

  if (curr_cell->x == next_cell->x - 1 && curr_cell->y == next_cell->y) {
    curr_cell->right = next_cell->left = false;
    draw_cell_helper(draw_cell_right, renderer, *curr_cell);
  }

  if (curr_cell->x == next_cell->x + 1 && curr_cell->y == next_cell->y) {
    curr_cell->left = next_cell->right = false;
    draw_cell_helper(draw_cell_left, renderer, *curr_cell);
  }
}

void
display_maze(SDL_Renderer* renderer, struct Cell** grid)
{
  // bg color
  SDL_SetRenderDrawColor(renderer, 36, 36, 36, 255);
  SDL_RenderClear(renderer);
  // SDL_RenderPresent(renderer);

  SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);

  for (int y = 0; y < MAZE_HEIGHT; y++) {
    for (int x = 0; x < MAZE_WIDTH; x++) {
      struct Cell cell = grid[y][x];

      if (cell.top)
        draw_cell_top(renderer, cell);

      if (cell.right)
        draw_cell_right(renderer, cell);

      if (cell.bottom)
        draw_cell_bottom(renderer, cell);

      if (cell.left)
        draw_cell_left(renderer, cell);
    }
  }

  SDL_RenderPresent(renderer);
}

void
draw_path_cell(SDL_Renderer* renderer,
               struct Path path,
               int j,
               int cell_index,
               int other_cell_index)
{
  const struct CellPos cell_pos = path.positions[cell_index];
  const struct CellPos other_cell_pos = path.positions[other_cell_index];

  SDL_Rect rect;
  rect.x = cell_pos.x * CELL_SIZE + ceil((float)CELL_SIZE / 4);
  rect.y = cell_pos.y * CELL_SIZE + ceil((float)CELL_SIZE / 4);

  bool is_src = (cell_index == path.length - 1);
  int delta = is_src ? ((float)CELL_SIZE / 4) : -((float)CELL_SIZE / 4);
  bool compare_x =
    is_src ? (cell_pos.x < other_cell_pos.x) : (cell_pos.x > other_cell_pos.x);
  bool compare_y =
    is_src ? (cell_pos.y < other_cell_pos.y) : (cell_pos.y > other_cell_pos.y);

  if (cell_pos.x != other_cell_pos.x) {
    int k = compare_x ? j + delta : CELL_SIZE - j - delta;
    rect.w = 1;
    rect.h = ceil((float)CELL_SIZE / 2);
    rect.x = cell_pos.x * CELL_SIZE + k;
  } else if (cell_pos.y != other_cell_pos.y) {
    int k = compare_y ? j + delta : CELL_SIZE - j - delta;
    rect.w = ceil((float)CELL_SIZE / 2);
    rect.h = 1;
    rect.y = cell_pos.y * CELL_SIZE + k;
  }
  SDL_RenderFillRect(renderer, &rect);

  if (PATH_CELL_ANIMATION) {
    SDL_Delay(PATH_CELL_DELAY);
    SDL_RenderPresent(renderer);
  }
}

void
draw_path(SDL_Renderer* renderer, struct Path path)
{
  float color = 0;
  float segments = (float)255 / (path.length * CELL_SIZE);

  for (int i = path.length - 1; i >= 0; i--) {
    for (int j = 0; j < CELL_SIZE; j++) {
      SDL_SetRenderDrawColor(renderer, 255 - color, color, 0, 255);
      if (i == path.length - 1) {
        draw_path_cell(renderer, path, j, i, i - 1);
      } else {
        draw_path_cell(renderer, path, j, i, i + 1);
      }
      color += segments;
    }
  }

  if (!PATH_CELL_ANIMATION) {
    SDL_Delay(50);
    SDL_RenderPresent(renderer);
  }
}

void
free_grid(struct Cell** grid)
{
  free(grid);
}
