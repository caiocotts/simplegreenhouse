#include "func.h"
#include "pisensehat.h"
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

unsigned long long int GetSerial(void) {

  FILE *fp;
  static unsigned long long int serial = 0;
  char buf[BUFSIZE];

  // print text from cpuinfo, filter "Serial", filter any numbers,
  // pass numbers into serialnum
  system("grep Serial /proc/cpuinfo | grep -Po '[\\d]+'> serialnum");
  fp = fopen("serialnum", "r");
  if (fp != NULL) {
    fscanf(fp, "%Lx", &serial);
    fclose(fp);
  } else {
    return 0;
  }

  return serial;
}

int GetRandom(int range) { return rand() % range; }

void DisplayHeader(const char *sname) {
  fprintf(stdout, "%s' Greenhouse Controller\n\n\n", sname);
}

void ControllerInit(void) {
  DisplaySplashScreen();

  system("clear");
  srand((unsigned)time(NULL));
  DisplayHeader("Caio Cotts");
#if SENSEHAT
  ShInit();
#endif
}

void DisplayReadings(readings rdata, int x, int y) {

  mvprintw(y, x, "Unit:%Lx %s ", GetSerial(), ctime(&rdata.rtime),
           rdata.pressure);
  mvprintw(y + 1, x, "Readings\tT: %5.1lfC\tH: %5.1lf%%\tP: %6.1lfmb\n",
           rdata.temperature, rdata.humidity, rdata.pressure);
}

double GetHumidity(void) {
#if SIMHUMIDITY
  return GetRandom(USHUMID - LSHUMID) + LSHUMID;
#else
  ht221sData_s ch = {0};
  ch = ShGetHT221SData();
  return ch.humidity;
#endif
}

double GetPressure(void) {
#if SIMPRESSURE
  return GetRandom(USPRESS - LSPRESS) + LSPRESS;
#else
  lps25hData_s cp = {0};
  cp = ShGetLPS25HData();
  return cp.pressure;
#endif
}

double GetTemperature(void) {

#if SIMTEMPERATURE
  return GetRandom(USTEMP - LSTEMP) + LSTEMP;
#else
  ht221sData_s ct = {0};
  ct = ShGetHT221SData();
  return ct.temperature;
#endif
}

readings GetReadings(void) {
  readings now = {0};

  now.rtime = time(NULL);
  now.temperature = GetTemperature();
  now.humidity = GetHumidity();
  now.pressure = GetPressure();
  return now;
}

controls SetControls(setpoints target, readings rdata) {
  controls state = {0};

  if (rdata.temperature < target.temperature) {
    state.heater = ON;
  } else {
    state.heater = OFF;
  }
  if (rdata.humidity < target.humidity) {
    state.humidifier = ON;
  } else {
    state.humidifier = OFF;
  }
  return state;
}

setpoints SetTargets(void) { // Create a dot directory in ~ if non existent
  setpoints cpoints = RetrieveSetPoints("setpoints");
  if (cpoints.temperature == 0) {
    cpoints.temperature = STEMP;
    cpoints.humidity = SHUMID;
    SaveSetPoints("setpoints", cpoints);
  }

  return cpoints;
}

void DisplayTargets(setpoints spts, int x, int y) {
  mvprintw(y + 2, x, "Targets\tT: %5.1lfC\tH: %5.1lf%%\n", spts.temperature,
           spts.humidity);
}

void DisplayControls(controls ctrl, int x, int y) {
  mvprintw(y + 3, x, "Controls\tHeater: %i\tHumidifier: %i\n", ctrl.heater,
           ctrl.humidifier);
}

int LogData(char *fname, readings ghdata) {
  FILE *fp;
  char ltime[CTIMESTRSZ];
  fp = fopen(fname, "a");
  if (fp == NULL) {
    return 0;
  }
  strcpy(ltime, ctime(&ghdata.rtime));
  ltime[3] = ',';
  ltime[7] = ',';
  ltime[10] = ',';
  ltime[19] = ',';

  fprintf(fp, "\n%.24s,%5.1lf,%5.1lf,%6.1lf", ltime, ghdata.temperature,
          ghdata.humidity, ghdata.pressure);
  fclose(fp);
  return 1;
}

int SaveSetPoints(char *fname, setpoints spts) {
  FILE *fp;
  fp = fopen(fname, "w");
  if (fp == NULL) {
    return 0;
  }
  fwrite(&spts, sizeof(setpoints), 1, fp);
  fclose(fp);
  return 1;
}

setpoints RetrieveSetPoints(char *fname) {
  setpoints spts = {0};
  FILE *fp;
  fp = fopen(fname, "r");
  if (fp == NULL) {
    return spts;
  }
  fread(&spts, sizeof(setpoints), 1, fp);
  fclose(fp);
  return spts;
}

void DisplaySplashScreen() {
  printw("      _                 _\n");
  printw("  ___(_)_ __ ___  _ __ | | ___\n");
  printw(" / __| | '_ ` _ \\| '_ \\| |/ _ \\\n");
  printw(" \\__ \\ | | | | | | |_) | |  __/\n");
  printw(" |___/_|_| |_| |_| .__/|_|\\___|\n");
  printw("                 |_|");
  attron(COLOR_PAIR(4));
  printw(" greenhouse\n");
  attroff(COLOR_PAIR(4));
  refresh();
  clear();
  sleep(3);
}

void DisplayOnMatrix(readings values, setpoints targets) {
  int scaledReadings, sv, svh, avl;
  fbpixel_s pixel_colour;
  ShClearMatrix();
  scaledReadings =
      (8.0 * (((values.temperature - LSTEMP) / (USTEMP - LSTEMP)) + 0.05)) -
      1.0;
  pixel_colour.red = 0x00;
  pixel_colour.green = 0xFF;
  pixel_colour.blue = 0x00;
  ShSetVerticalBar(TBAR, pixel_colour, scaledReadings);

  scaledReadings =
      (8.0 * (((values.humidity - LSHUMID) / (USHUMID - LSHUMID)) + 0.05)) -
      1.0;
  ShSetVerticalBar(HBAR, pixel_colour, scaledReadings);

  scaledReadings =
      (8.0 * (((values.pressure - LSPRESS) / (USPRESS - LSPRESS)) + 0.05)) -
      1.0;
  ShSetVerticalBar(PBAR, pixel_colour, scaledReadings);

  pixel_colour.red = 0xFF;
  pixel_colour.green = 0x00;
  pixel_colour.blue = 0x00;

  sv = (8.0 * (((targets.temperature - LSTEMP) / (USTEMP - LSTEMP)) + 0.05)) -
       1.0;
  WritePixel(TBAR, sv, pixel_colour);
  ShSetPixel(TBAR, sv, pixel_colour);
  sv = (8.0 * (((targets.humidity - LSHUMID) / (USHUMID - LSHUMID)) + 0.05)) -
       1.0;
  ceil(sv);
  WritePixel(HBAR, sv, pixel_colour);
  ShSetPixel(HBAR, sv, pixel_colour);
}

void WritePixel(int x, int y, fbpixel_s pixel_color) {
  int simulated_x_coordinate = (7 - x) * 4;
  int simulated_y_coordinate = (7 - y) * 2;

  if (pixel_color.red != 0) {
    attron(COLOR_PAIR(1));
    mvprintw(simulated_y_coordinate, simulated_x_coordinate, PIXEL_STRING);
    attroff(COLOR_PAIR(1));
  } else if (pixel_color.green != 0) {
    attron(COLOR_PAIR(2));
    mvprintw(simulated_y_coordinate, simulated_x_coordinate, PIXEL_STRING);
    attroff(COLOR_PAIR(2));
  } else {
    attron(COLOR_PAIR(4));
    mvprintw(simulated_y_coordinate, simulated_x_coordinate, PIXEL_STRING);
    attroff(COLOR_PAIR(4));
  }
}

void WriteBlankMatrix() {

  for (int y = 0; y <= 14; y = y + 2) {
    for (int x = 0; x <= 31; x = x + 4) {
      attron(COLOR_PAIR(3));
      mvprintw(y, x, "  ");
      attroff(COLOR_PAIR(3));
    }
  }

  // move(14, 29);
  refresh();
}