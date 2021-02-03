/*
************************
******* lab01.c ********
************************
*/

#include "func.h"

int main() {
  time_t now;
  srand((unsigned)(time(NULL)));

  displayHeader("Caio Cotts");
  while (true) {
    now = time(NULL);
    // printf("------%Lx\n", GhGetSerial());
    printf("\nUnit: %Lx %sReadings\tT: %dC\n", getSerial(), ctime(&now),
           getRandom(100) - 50);
    sleep(GHUPDATE);
  }

  printf("Press ENTER to continue...");
  getchar();

  return EXIT_FAILURE;
}
