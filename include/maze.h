#ifndef CELL_H
#define CELL_H

enum Bool
{
  FALSE,
  TRUE,
};

struct Cell
{
  int x;
  int y;
  enum Bool visited;
  enum Bool top;
  enum Bool right;
  enum Bool bottom;
  enum Bool left;
};

struct Cell**
generate_grid();

void
randomized_dfs(struct Cell** grid, struct Cell* cell);

struct Cell*
get_neighbour(struct Cell** grid, struct Cell cell);

void
connect_cells(struct Cell* curr_cell, struct Cell* next_cell);

int
display_maze(struct Cell** grid);

#endif // !CELL_H
