#include "paper_grid.h"
#include <stdio.h>
#include <stdlib.h>

struct GRID_CASES {
  const char *name;
  const char *floc;
  const int expected;
};

int test_process_grid_file(void) {
  int failures = 0;

  struct GRID_CASES cases[] = {{"Example file", "tests/example.txt", 43}};
  for (size_t i = 0; i < sizeof cases / sizeof cases[0]; ++i) {
    FILE *file = fopen(cases[i].floc, "r");

    int actual = process_from_file(file);

    if (actual != cases[i].expected) {
      fprintf(stderr, "FAILURE: %s: Expected %d, found %d\n", cases[i].name,
              cases[i].expected, actual);
      ++failures;
    }
  }

  return failures;
}

int main(void) {
  int failures = 0;

  failures += test_process_grid_file();
  if (failures == 0) {
    printf("All tests pass!\n");

    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}
