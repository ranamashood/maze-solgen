#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <stdio.h>

extern int MAZE_WIDTH;
extern int MAZE_HEIGHT;
extern int CELL_SIZE;
extern int GRID_CELL_DELAY;
extern int GRID_ITERATION_DELAY;
extern int PATH_CELL_DELAY;
extern bool GRID_CELL_ANIMATION;
extern bool GRID_ITERATION_ANIMATION;
extern bool PATH_CELL_ANIMATION;

void
create_config(char* option, char* value);

char*
trim_line(char* line, size_t len);

bool
parse_option(char* line, char** option, char** value);

void
parse_config_file(const char* path);

#endif // !CONFIG_H
