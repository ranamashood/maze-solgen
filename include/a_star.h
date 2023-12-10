#ifndef A_STAR_H
#define A_STAR_H

#include "cell.h"
#include "config.h"

struct CellInfo
{
  int parent_y, parent_x;
  double f, g, h;
};

struct Pair
{
  double first;
  int second[2];
};

struct CellPos
{
  int x, y;
};

struct Path
{
  struct CellPos* positions;
  int length;
};

struct Path
create_path();

void
add_path_position(struct Path* path, struct CellPos curr_pos);

void
free_path(struct Path* path);

bool
isValid(int row, int col);

bool
isUnBlocked(struct Cell** grid, int row, int col, int move);

bool
isDestination(int row, int col, struct Pair dest);

int
calculateHValue(int row, int col, struct Pair dest);

void
tracePath(struct CellInfo cellDetails[][MAZE_WIDTH],
          struct Pair dest,
          struct Path* path);

struct Path
aStarSearch(struct Cell** grid, struct Pair src, struct Pair dest);

#endif // !A_STAR_H
