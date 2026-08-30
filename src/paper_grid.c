#include "paper_grid.h"

int process_from_file(FILE *file) {

  char *line = NULL;

  if (fgets(line, 200, file) == NULL) {
    return 1;
  }

  return 0;
}
