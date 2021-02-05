#include "func.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long long int getSerial(void) {

  FILE *fp;
  static unsigned long long int serial = 0;
  char buf[BUFSIZE];

  // print text from cpuinfo, filter "Serial", filter any numbers,
  // pass numbers into serialnum
  system("cat /proc/cpuinfo | grep Serial | grep -Po '[\\d]+'> serialnum");
  fp = fopen("serialnum", "r");
  if (fp != NULL) {
    fscanf(fp, "%llu", &serial);
    fclose(fp);
  } else {
    return 0;
  }

  return serial;
}

int getRandom(int range) { return rand() % range; }

void displayHeader(const char *sname) {
  printf("%s's Greenhouse Controller\n\n\n", sname);
}
