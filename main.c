//      _                 _
//  ___(_)_ __ ___  _ __ | | ___
// / __| | '_ ` _ \| '_ \| |/ _ \
// \__ \ | | | | | | |_) | |  __/
// |___/_|_| |_| |_| .__/|_|\___|
//                 |_| greenhouse

// getopt

#include "func.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
  controls ctrl = {0};
  setpoints sets = {0};
  readings creadings = {0};
  sets = SetTargets();
  ControllerInit();
  int logged;

  initscr();
  WriteBlankMatrix();
  while (1) {
    curs_set(0);
    refresh();
    creadings = GetReadings();
    logged = LogData("log", creadings);
    DisplayOnMatrix(creadings, sets);
    // DisplayReadings(creadings);
    // DisplayTargets(sets);
    ctrl = SetControls(sets, creadings);
    // DisplayControls(ctrl);
    // endwin();
    refresh();
    sleep(DELAY_INTERVAL);
  }

  return EXIT_FAILURE;
}