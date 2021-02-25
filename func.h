#ifndef SIMPLEGH_H
#define SIMPLEGH_H
#define BUFSIZE 512
#define GHUPDATE 2
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
// #define STEMP 25.0
// #define SHUMID 55.0
// #define ON 1
// #define OFF 0

#include <time.h>

int GetRandom(int range);
unsigned long long int GetSerial(void);
void DisplayHeader(const char *sname);

#endif

void ControllerInit(void);
void DisplayTargets(void);
double GetHumidity(void);
double GetPressure(void);
double GetTemperature(void);

// void DisplayReadings(time_t rtime, double dreads[SENSORS]);
//
// double GetReadings(double readings[SENSORS]);
//