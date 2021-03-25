//      _                 _
//  ___(_)_ __ ___  _ __ | | ___
// / __| | '_ ` _ \| '_ \| |/ _ \
// \__ \ | | | | | | |_) | |  __/
// |___/_|_| |_| |_| .__/|_|\___|
//                 |_|

#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main()
{
  struct controls ctrl = {0};
  struct setpoints sets = {0};
  struct readings creadings = {0};
  sets = SetTargets();
  ControllerInit();
  int logged;

  while (1)
  {
    creadings = GetReadings();
    logged = LogData("data.txt", creadings);

    DisplayReadings(creadings);
    DisplayTargets(sets);
    ctrl = SetControls(sets, creadings);
    DisplayControls(ctrl);

    sleep(DELAY_INTERVAL);
  }

  return EXIT_FAILURE;
}