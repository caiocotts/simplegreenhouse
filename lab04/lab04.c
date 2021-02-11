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
  int tempc, humidc;
  double creadings[SENSORS];
  GhControllerInit();

  while (1) {
    now = time(NULL);
    GhGetReadings(creadings);
    // task 4

    GhDisplayReadings(now, creadings);
    GhDisplayTargets();
    GhSetControls(&tempc, &humidc, creadings);
    GhDisplayControls(&tempc, &humidc);

    GhDelay(GHUPDATE);
  }

  // fprintf(stdout, "Press ENTER to continue...");
  // getchar();

  return EXIT_FAILURE;
}
