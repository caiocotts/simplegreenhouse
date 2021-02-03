

#include "func.h"

// void GhDelay(int milliseconds) {
//   long wait;
//   clock_t now, start;

//   wait = milliseconds * (CLOCKS_PER_SEC / 1000);
//   start = clock();
//   now = start;
//   while ((now - start) < wait) {
//     now = clock();
//   }
// }

uint64_t getSerial(void) {

  FILE *fp;
  static uint64_t serial = 0;
  char buf[BUFSIZE];
  system("cat /proc/cpuinfo | grep Serial | grep -Po '[\\d]+'> serialnum");
  fp = fopen("serialnum", "r");
  if (fp != NULL) {
    fscanf(fp, "%lu", &serial);
    fclose(fp);
    printf("%lu", serial);
  }

  return serial;
}

int getRandom(int range) { return rand() % range; }

void displayHeader(const char *sname) {
  printf("%s's Greenhouse Controller\n\n\n", sname);
}
