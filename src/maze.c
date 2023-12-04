#include "../include/maze.h"
#include <SDL2/SDL.h>
#include <time.h>

// TODO: set maze width and height with roll number
const int MAZE_WIDTH = 50;
const int MAZE_HEIGHT = 50;
const int CELL_SIZE = 10;

struct Cell**
generate_grid()
{
  struct Cell** grid =
    (struct Cell**)malloc(MAZE_HEIGHT * sizeof(struct Cell*));
  for (int y = 0; y < MAZE_HEIGHT; y++) {
    grid[y] = (struct Cell*)malloc(MAZE_WIDTH * sizeof(struct Cell));
  }

  for (int y = 0; y < MAZE_HEIGHT; y++) {
    for (int x = 0; x < MAZE_WIDTH; x++) {
      grid[y][x] = (struct Cell){ x, y, FALSE, TRUE, TRUE, TRUE, TRUE };
    }
  }

  // struct Cell* curr_cell = &grid[MAZE_HEIGHT / 3][MAZE_WIDTH / 2];
  // TODO: choose curr_cell with roll number
  struct Cell* curr_cell = &grid[0][0];

  srand(time(NULL));
  randomized_dfs(grid, curr_cell);

  return grid;
}

void
randomized_dfs(struct Cell** grid, struct Cell* cell)
{
  cell->visited = TRUE;
  struct Cell* next_cell = get_neighbour(grid, *cell);
  while (next_cell != NULL) {
    connect_cells(cell, next_cell);
    randomized_dfs(grid, next_cell);
    next_cell = get_neighbour(grid, *cell);
  }
}

struct Cell*
get_neighbour(struct Cell** grid, struct Cell cell)
{
  int size = 0;
  struct Cell* neighours[4];

  if (cell.y > 0 && !grid[cell.y - 1][cell.x].visited) {
    neighours[size++] = &grid[cell.y - 1][cell.x];
  }

  if (cell.x > 0 && !grid[cell.y][cell.x - 1].visited) {
    neighours[size++] = &grid[cell.y][cell.x - 1];
  }

  if (cell.y < MAZE_HEIGHT - 1 && !grid[cell.y + 1][cell.x].visited) {
    neighours[size++] = &grid[cell.y + 1][cell.x];
  }

  if (cell.x < MAZE_WIDTH - 1 && !grid[cell.y][cell.x + 1].visited) {
    neighours[size++] = &grid[cell.y][cell.x + 1];
  }

  // TODO: remove rand_num function and use one line exclusive method
  if (!size) {
    return NULL;
  } else {
    int rand_index = rand() % size;
    return neighours[rand_index];
  }
}

void
connect_cells(struct Cell* curr_cell, struct Cell* next_cell)
{
  if ((curr_cell->x == next_cell->x) &&
      (curr_cell->y == next_cell->y + 1)) { /// top
    curr_cell->top = next_cell->bottom = FALSE;
  }
  if (curr_cell->x == next_cell->x &&
      curr_cell->y == next_cell->y - 1) { /// bottom
    curr_cell->bottom = next_cell->top = FALSE;
  }
  if (curr_cell->x == next_cell->x - 1 &&
      curr_cell->y == next_cell->y) { /// right
    curr_cell->right = next_cell->left = FALSE;
  }
  if (curr_cell->x == next_cell->x + 1 &&
      curr_cell->y == next_cell->y) { /// left
    curr_cell->left = next_cell->right = FALSE;
  }
}

int
display_maze(struct Cell** grid)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  window = SDL_CreateWindow("Maze Solgen",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            1000,
                            700,
                            SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    fprintf(
      stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  for (int y = 0; y < MAZE_HEIGHT; y++) {
    for (int x = 0; x < MAZE_WIDTH; x++) {
      struct Cell cell = grid[y][x];

      if (cell.top) {
        SDL_RenderDrawLine(renderer,
                           x * CELL_SIZE,
                           y * CELL_SIZE,
                           (x * CELL_SIZE) + CELL_SIZE,
                           y * CELL_SIZE);
      }

      if (cell.right) {
        SDL_RenderDrawLine(renderer,
                           (x * CELL_SIZE) + CELL_SIZE,
                           y * CELL_SIZE,
                           (x * CELL_SIZE) + CELL_SIZE,
                           (y * CELL_SIZE) + CELL_SIZE);
      }

      if (cell.bottom) {
        SDL_RenderDrawLine(renderer,
                           (x * CELL_SIZE) + CELL_SIZE,
                           (y * CELL_SIZE) + CELL_SIZE,
                           x * CELL_SIZE,
                           (y * CELL_SIZE) + CELL_SIZE);
      }

      if (cell.left) {
        SDL_RenderDrawLine(renderer,
                           x * CELL_SIZE,
                           (y * CELL_SIZE) + CELL_SIZE,
                           x * CELL_SIZE,
                           y * CELL_SIZE);
      }
    }
  }

  SDL_RenderPresent(renderer);

  SDL_Event e;
  int quit = 0;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = 1;
    }
    SDL_Delay(10);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
