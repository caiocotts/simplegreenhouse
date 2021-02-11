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
#define SIMULATE 1
#define USTEMP 50
#define LSTEMP -10
#define USHUMID 100
#define LSHUMID 0
#define USPRESS 1016
#define LSPRESS 975
#define STEMP 25.0
#define SHUMID 55.0
#define ON 1
#define OFF 0

int GhGetRandom(int range);
uint64_t GhGetSerial(void);
void GhDisplayHeader(const char *sname);
void GhDelay(int milliseconds);

// Task 2
void GhControllerInit(void);
void GhDisplayControls(int *heater, int *humidifier);
void GhDisplayReadings(time_t rtime, double dreads[SENSORS]);
void GhDisplayTargets(void);
void GhSetControls(int *heater, int *humidifier, double readings[SENSORS]);
void GhSetTargets(void);

double GhGetHumidity(void);
double GhGetPressure(void);
double GhGetTemperature(void);
void GhGetReadings(double readings[SENSORS]);

#endif