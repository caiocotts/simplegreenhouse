/*
************************
******* lab01.c ********
************************
*/

#include "ghcontrol.h"

int main() {
  time_t now;
  srand((unsigned)(time(NULL)));

  GhDisplayHeader("Caio Cotts");
  while (true) {
    // printf("------%Lx\n", GhGetSerial());
    fprintf(stdout, "\nUnit: %Lx %sReadings\tT: %dC\n", GhGetSerial(),
            ctime(&now), GhGetRandom(100) - 50);
    GhDelay(GHUPDATE);
  }

  fprintf(stdout, "Press ENTER to continue...");
  getchar();

  return EXIT_FAILURE;
}
