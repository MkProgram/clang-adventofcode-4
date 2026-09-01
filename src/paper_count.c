#include "paper_grid.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  puts("Lets count some paper!");
  FILE *file = fopen("paper_grid.txt", "r");

  size_t paper_count = process_from_file(file);

  fclose(file);

  printf("Paper count is: %d\n", (int)paper_count);
  return EXIT_SUCCESS;
}
