
#ifndef GHCONTROL_H
#define GHCONTROL_H
#define SEARCHSTR "serial\t\t"
#define SYSINFOBUFSZ 512
#define GHUPDATE 2000

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

int GhGetRandom(int range);
uint64_t GhGetSerial(void);
void GhDisplayHeader(const char *sname);
void GhDelay(int milliseconds);

#endif
