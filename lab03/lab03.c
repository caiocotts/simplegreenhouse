/*
************************
******* lab03.c ********
************************
*/

#include "ghcontrol.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  time_t now;
  double creadings[SENSORS];
  GhControllerInit();

  while (1) {
    now = time(NULL);
    GhGetReadings(creadings);
    // task 4
    GhSetControls();

    GhDisplayReadings(now, creadings);
    // GhDisplayTargets();
    GhDisplayControls();

    GhDelay(GHUPDATE);
  }

  // fprintf(stdout, "Press ENTER to continue...");
  // getchar();

  return EXIT_FAILURE;
}
