#ifndef CELL_H
#define CELL_H

#include <stdbool.h>

struct Cell
{
  int x, y;
  bool visited;
  bool top;
  bool right;
  bool bottom;
  bool left;
};

#endif // !CELL_H
