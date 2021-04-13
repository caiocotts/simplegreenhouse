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
  initscr();
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_RED);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);
  init_pair(3, COLOR_BLACK, COLOR_WHITE);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);
  curs_set(0);
  controls ctrl = {0};
  setpoints sets = {0};
  readings creadings = {0};
  sets = SetTargets();
  ControllerInit();
  int logged;
  int xoffset = 35;
  int yoffset = 2;
  // WriteBlankMatrix();
  while (1) {
    refresh();
    creadings = GetReadings();
    logged = LogData("log", creadings);
    DisplayOnMatrix(creadings, sets);
    DisplayReadings(creadings, xoffset, yoffset);
    DisplayTargets(sets, xoffset, yoffset);
    ctrl = SetControls(sets, creadings);
    DisplayControls(ctrl, xoffset, yoffset);
    refresh();
    sleep(DELAY_INTERVAL);
  }
}