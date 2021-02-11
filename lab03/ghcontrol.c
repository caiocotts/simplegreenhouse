#include "ghcontrol.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void GhDelay(int milliseconds) {
  long wait;
  clock_t now, start;

  wait = milliseconds * (CLOCKS_PER_SEC / 1000);
  start = clock();
  now = start;
  while ((now - start) < wait) {
    now = clock();
  }
}

uint64_t GhGetSerial(void) {
  static uint64_t serial = 0;
  FILE *fp;
  char buf[SYSINFOBUFSZ];
  char searchstring[] = SEARCHSTR;
  fp = fopen("/proc/cpuinfo", "r");
  if (fp != NULL) {
    while (fgets(buf, sizeof(buf), fp) != NULL) {
      if (!strncasecmp(searchstring, buf, strlen(searchstring))) {
        sscanf(buf + strlen(searchstring), "%lu", &serial);
      }
    }
    fclose(fp);
  }
  if (serial == 0) {
    system("uname -a");
    system("ls --fu /usr/lib/codeblocks | grep -Po '\\.\\K[^ ]+'>stamp.txt");
    fp = fopen("stamp.txt", "r");
    if (fp != NULL) {
      while (fgets(buf, sizeof(buf), fp) != NULL) {
        sscanf(buf, "%lu", &serial);
      }
      fclose(fp);
    }
  }
  return serial;
}

int GhGetRandom(int range) { return rand() % range; }

void GhDisplayHeader(const char *sname) {
  fprintf(stdout, "%s' Greenhouse Controller\n\n\n", sname);
}

void GhControllerInit(void) {
  srand((unsigned)time(NULL));
  GhDisplayTargets();
  GhDisplayHeader("Caio Cotts");
}

void GhDisplayReadings(time_t rtime, double dreads[SENSORS]) {

  fprintf(stdout,
          "\nUnit:%LX %s Readings\tT: %5.1lfC\tH: %5.1lf%%\tP: %6.1lfmb\n ",
          GhGetSerial(), ctime(&rtime), dreads[TEMPERATURE], dreads[HUMIDITY],
          dreads[PRESSURE]);
}
double GhGetHumidity(void) {
#if SIMULATE
  return GhGetRandom(USHUMID - LSHUMID) + LSHUMID;
#else
  return 55.0;
#endif
}
double GhGetPressure(void) {
#if SIMULATE
  return GhGetRandom(USPRESS - LSPRESS) + LSPRESS;
#else
  return 1013.0;
#endif
}
double GhGetTemperature(void) {

#if SIMULATE
  return GhGetRandom(USTEMP - LSTEMP) + LSTEMP;
#else
  return 20.0;
#endif
}

void GhGetReadings(double readings[SENSORS]) {

  readings[TEMPERATURE] = GhGetTemperature();
  readings[HUMIDITY] = GhGetHumidity();
  readings[PRESSURE] = GhGetPressure();
}

void GhSetControls(int *heater, int *humidifier, double readings[SENSORS]) {
  if (readings[TEMPERATURE] < STEMP) {
    *heater = 1;
  } else {
    *heater = 0;
  }
  if (readings[HUMIDITY] < SHUMID) {
    *humidifier = 1;
  } else {
    *humidifier = 0;
  }
}
void GhSetTargets(void) {}
void GhDisplayTargets(void) {
  fprintf(stdout, "Targets\tT: %5.1lfC\tH: %5.1lf%%\n", STEMP, SHUMID);
}
void GhDisplayControls(int *heater, int *humidifier) {
  fprintf(stdout, " Controls\tHeater: %i\tHumidifier: %i\n", *heater,
          *humidifier);
}