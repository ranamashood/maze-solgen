#include "../include/config.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int MAZE_WIDTH = 2;
int MAZE_HEIGHT = 2;
int CELL_SIZE = 3;

void
create_config(char* option, char* value)
{
  int value_int = atoi(value);

  if (value_int != 0) {
    if (strcmp(option, "cell-size") == 0) {
      CELL_SIZE = value_int;
    } else if (strcmp(option, "maze-width") == 0) {
      MAZE_WIDTH = value_int;
    } else if (strcmp(option, "maze-height") == 0) {
      MAZE_HEIGHT = value_int;
    }
  }
}

char*
trim_line(char* line, size_t len)
{
  char* trimmed_line = line;
  int j = 0;

  for (int i = 0; i < len; i++) {
    if (!isspace(line[i]))
      trimmed_line[j++] = line[i];
  }

  trimmed_line[j] = '\0';

  return trimmed_line;
}

bool
parse_option(char* line, char** option, char** value)
{
  char* delimeter_pos = strchr(line, ':');

  if (delimeter_pos != NULL) {
    *delimeter_pos = '\0';
    *option = line;
    *value = delimeter_pos + 1;
    return true;
  }

  return false;
}

void
parse_config_file(const char* path)
{
  FILE* file;
  file = fopen(path, "r");

  if (file == NULL) {
    printf("config file \"%s\" not found\n", path);
  }

  char* line = NULL;
  size_t len = 0;
  char *option, *value;

  while (getline(&line, &len, file) != -1) {
    char* trimmed_line = trim_line(line, len);
    if (*trimmed_line == '#' || *trimmed_line == '\0')
      continue;

    if (parse_option(trimmed_line, &option, &value)) {
      create_config(option, value);
    }
  }

  if (line != NULL)
    free(line);
}
