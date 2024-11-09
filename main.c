#include <stdio.h>
#include "defee39.h"

int main(int argc, char *argv[]) {
  printf("Skrambilka %s by dslf (%s %s)\n\n", P_VER, C_DATE, C_TIME);

  init_cube();
  /* rotate_cube("R U R' U'");
  draw_cube(); */
  parse_argc(argc, argv);
  

  return 0;
}