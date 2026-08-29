#include <stdio.h>
#include <stdlib.h>

int main(void) {

  puts("Lets count some paper!");
  FILE *file = fopen("paper_grid.txt", "r");

  fclose(file);

  return EXIT_SUCCESS;
}
