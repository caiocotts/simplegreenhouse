#ifndef GHCONTROL_H
#define GHCONTROL_H
#include <stdint.h>
#include <time.h>

#define SEARCHSTR "serial\t\t"
#define SYSINFOBUFSZ 512
#define GHUPDATE 2000
#define SENSORS 3
#define TEMPERATURE 0
#define HUMIDITY 1
#define PRESSURE 2

int GhGetRandom(int range);
uint64_t GhGetSerial(void);
void GhDisplayHeader(const char *sname);
void GhDelay(int milliseconds);

// Task 2
void GhControllerInit(void);
void GhDisplayControls(void);
void GhDisplayReadings(time_t rtime, double dreads[SENSORS]);
void GhDisplayTargets(void);
void GhSetControls(void);
void GhSetTargets(void);

double GhGetHumidity(void);
double GhGetPressure(void);
double GhGetTemperature(void);
double GhGetReadings(double readings[SENSORS]);

#endif