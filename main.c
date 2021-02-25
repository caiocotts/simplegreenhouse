//      _                 _
//  ___(_)_ __ ___  _ __ | | ___
// / __| | '_ ` _ \| '_ \| |/ _ \
// \__ \ | | | | | | |_) | |  __/
// |___/_|_| |_| |_| .__/|_|\___|
//                 |_|

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "func.h"

int main() {
  time_t now;
  // srand((unsigned)(time(NULL)));

  while (true) {
    now = time(NULL);
    printf("\nUnit: %Lx %sReadings\tT: %dC\n", GetSerial(), ctime(&now),
           GetRandom(100) - 50);
    sleep(GHUPDATE);
  }

  // printf("Press ENTER to continue...");
  // getchar();

  return 0;
}
// getSerial get_serial GetSerial