#ifndef SIMPLEGH_H
#define SIMPLEGH_H
#define BUFSIZE 512
#define GHUPDATE 2

#include <time.h>

int getRandom(int range);
unsigned long long int getSerial(void);
void displayHeader(const char *sname);

#endif

void ControllerInit(void);
// void GhDisplayReadings(time_t rtime, double dreads[SENSORS]);
// void GhDisplayTargets(void);
//
// double GhGetHumidity(void);
// double GhGetPressure(void);
// double GhGetTemperature(void);
// double GhGetReadings(double readings[SENSORS]);
//