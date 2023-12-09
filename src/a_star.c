#include "../include/a_star.h"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

struct Path
create_path()
{
  struct Path path;
  path.length = 0;
  path.positions = NULL;
  return path;
}

void
add_path_position(struct Path* path, struct CellPos cell_pos)
{
  path->positions =
    realloc(path->positions, ++path->length * sizeof(struct CellPos));
  path->positions[path->length - 1] = cell_pos;
}

void
free_path(struct Path* path)
{
  free(path->positions);
}

bool
isValid(int y, int x)
{
  return (y >= 0) && (y < MAZE_HEIGHT) && (x >= 0) && (x < MAZE_WIDTH);
}

bool
isUnBlocked(struct Cell** grid, int y, int x, int move)
{
  switch (move) {
    case 0:
      return !grid[y][x].top;
    case 1:
      return !grid[y][x].right;
    case 2:
      return !grid[y][x].bottom;
    case 3:
      return !grid[y][x].left;
    default:
      return false;
  }
}

bool
isDestination(int y, int x, struct Pair dest)
{
  return (y == dest.second[0] && x == dest.second[1]);
}

int
calculateHValue(int y, int x, struct Pair dest)
{
  return (abs(y - dest.second[0]) + abs(x - dest.second[1]));
}

void
tracePath(struct CellInfo cellDetails[][MAZE_WIDTH],
          struct Pair dest,
          struct Path* path)
{
  int y = dest.second[0];
  int x = dest.second[1];

  while (
    !(cellDetails[y][x].parent_y == y && cellDetails[y][x].parent_x == x)) {
    struct CellPos cell_pos = { x, y };
    add_path_position(path, cell_pos);
    int temp_y = cellDetails[y][x].parent_y;
    int temp_x = cellDetails[y][x].parent_x;
    y = temp_y;
    x = temp_x;
  }

  struct CellPos cell_pos = { x, y };
  add_path_position(path, cell_pos);
}

struct Path
aStarSearch(struct Cell** grid, struct Pair src, struct Pair dest)
{
  struct Path path = create_path();

  // if (!isValid(src.second[0], src.second[1]) ||
  //     !isValid(dest.second[0], dest.second[1]) ||
  //     !isUnBlocked(grid, src.second[0], src.second[1], 0) ||
  //     !isUnBlocked(grid, dest.second[0], dest.second[1], 0)) {
  //   printf("Source or destination is invalid\n");
  //   return path;
  // }

  if (isDestination(src.second[0], src.second[1], dest)) {
    printf("We are already at the destination\n");
    return path;
  }

  bool closedList[MAZE_HEIGHT][MAZE_WIDTH];
  for (int i = 0; i < MAZE_HEIGHT; i++) {
    for (int j = 0; j < MAZE_WIDTH; j++) {
      closedList[i][j] = false;
    }
  }

  struct CellInfo cellDetails[MAZE_HEIGHT][MAZE_WIDTH];

  for (int i = 0; i < MAZE_HEIGHT; i++) {
    for (int j = 0; j < MAZE_WIDTH; j++) {
      cellDetails[i][j].f = DBL_MAX;
      cellDetails[i][j].g = DBL_MAX;
      cellDetails[i][j].h = DBL_MAX;
      cellDetails[i][j].parent_y = -1;
      cellDetails[i][j].parent_x = -1;
    }
  }

  int y = src.second[0], x = src.second[1];
  cellDetails[y][x].f = 0.0;
  cellDetails[y][x].g = 0.0;
  cellDetails[y][x].h = 0.0;
  cellDetails[y][x].parent_y = y;
  cellDetails[y][x].parent_x = x;

  struct Pair openList[MAZE_HEIGHT * MAZE_WIDTH];
  int openListSize = 1;
  openList[0] = src;

  bool foundDest = false;

  while (openListSize > 0) {
    int minIndex = 0;
    for (int k = 0; k < openListSize; k++) {
      if (openList[k].first < openList[minIndex].first) {
        minIndex = k;
      }
    }

    y = openList[minIndex].second[0];
    x = openList[minIndex].second[1];
    // i = 0;
    // j = 0;
    openList[minIndex] = openList[openListSize - 1];
    openListSize--;

    closedList[y][x] = true;

    double gNew, hNew, fNew;

    int y_move[] = { -1, 0, 1, 0 };
    int x_move[] = { 0, 1, 0, -1 };

    for (int move = 0; move < 4; move++) {
      int new_y = y + y_move[move];
      int new_x = x + x_move[move];

      if (isValid(new_y, new_x) && isUnBlocked(grid, y, x, move)) {
        if (isDestination(new_y, new_x, dest)) {
          cellDetails[new_y][new_x].parent_y = y;
          cellDetails[new_y][new_x].parent_x = x;
          printf("The destination cell is found\n");
          tracePath(cellDetails, dest, &path);
          foundDest = true;
          return path;
        } else if (!closedList[new_y][new_x]) {
          gNew = cellDetails[y][x].g + 1.0;
          hNew = calculateHValue(new_y, new_x, dest);
          fNew = gNew + hNew;

          if (cellDetails[new_y][new_x].f == DBL_MAX ||
              cellDetails[new_y][new_x].f > fNew) {
            openList[openListSize].first = fNew;
            openList[openListSize].second[0] = new_y;
            openList[openListSize].second[1] = new_x;
            openListSize++;

            cellDetails[new_y][new_x].f = fNew;
            cellDetails[new_y][new_x].g = gNew;
            cellDetails[new_y][new_x].h = hNew;
            cellDetails[new_y][new_x].parent_y = y;
            cellDetails[new_y][new_x].parent_x = x;
          }
        }
      }
    }
  }

  if (!foundDest)
    printf("Failed to find the Destination Cell\n");

  return path;
}
