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
  GhSetTargets();
  GhDisplayHeader("Caio Cotts");
}

void GhDisplayReadings(time_t rtime, double dreads[SENSORS]) {

  fprintf(stdout,
          "\nUnit:%LX %s Readings\tT: %5.1lfC\tH: %5.1lf%%\tP: %6.1lfmb\n ",
          GhGetSerial(), ctime(&rtime), dreads[TEMPERATURE], dreads[HUMIDITY],
          dreads[PRESSURE]);
}
double GhGetHumidity(void) { return 55.0; }
double GhGetPressure(void) { return 1013.0; }
double GhGetTemperature(void) { return 20.0; }

// double readings[SENSORS]

double GhGetReadings(double readings[SENSORS]) {

  readings[TEMPERATURE] = GhGetTemperature();
  readings[HUMIDITY] = GhGetHumidity();
  readings[PRESSURE] = GhGetPressure();
}

void GhSetControls(void) {}
void GhSetTargets(void) {}
void GhDisplayControls(void) {}