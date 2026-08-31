#include "paper_grid.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int neightbors[][2] = {{0, -1},  {0, 1}, {-1, 0}, {-1, 1},
                                    {-1, -1}, {1, 0}, {1, 1},  {1, -1}};

bool in_bounds(int col, int row, size_t max_rows, size_t max_cols) {
  return row >= 0 && (size_t)row < max_rows && col >= 0 &&
         (size_t)col < max_cols;
}

char **create_grid_from_file(FILE *file, size_t *out_count) {
  char **grid = NULL;
  size_t count = 0;
  size_t capacity = 0;

  char *line = NULL;
  size_t line_cap = 0;

  while (getline(&line, &line_cap, file) != -1) {
    if (count == capacity) {
      capacity = (capacity == 0) ? 4 : capacity * 2;
      char **grown = realloc(grid, capacity * sizeof(*grid));
      if (grown == NULL) {
        free(line);
        *out_count = count;
        return grid;
      }
      grid = grown;
    }

    line[strcspn(line, "\n")] = '\0';
    char *owned = strdup(line);
    if (owned == NULL) {
      break;
    }
    grid[count++] = owned;
  }
  free(line);
  *out_count = count;

  return grid;
}

size_t count_neighboring_papers(char **grid, int row, int col, size_t max_rows,
                                size_t max_cols) {
  size_t count = 0;

  for (size_t i = 0; i < sizeof(neightbors) / sizeof(neightbors[0]); i++) {
    int nrow = row + neightbors[i][0];
    int ncol = col + neightbors[i][1];
    if (!in_bounds(ncol, nrow, max_rows, max_cols)) {
      continue;
    }
    if (grid[nrow][ncol] == '@') {
      ++count;
    }
  }

  return count;
}

int process_from_file(FILE *file) {

  size_t max_rows = 0;
  size_t max_cols = 0;
  size_t paper_count = 0;
  char **grid = create_grid_from_file(file, &max_rows);

  for (size_t row = 0; row < max_rows; ++row) {
    if (max_cols == 0) {
      max_cols = strlen(grid[row]);
    }
    for (size_t col = 0; col < max_cols; col++) {
      if (grid[row][col] != '@') {
        continue;
      }
      if (count_neighboring_papers(grid, row, col, max_rows, max_cols) < 4) {
        ++paper_count;
      }
    }
  }

  return paper_count;
}
