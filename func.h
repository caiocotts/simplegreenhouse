#ifndef GHCONTROL_H
#define GHCONTROL_H
#define SEARCHSTR "Serial\t\t"
#define BUFSIZE 512
#define GHUPDATE 2

#include <time.h>

int getRandom(int range);
unsigned long long int getSerial(void);
void displayHeader(const char *sname);

#endif
