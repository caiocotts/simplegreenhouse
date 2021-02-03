
#ifndef GHCONTROL_H
#define GHCONTROL_H
#define SEARCHSTR "Serial\t\t"
#define BUFSIZE 512
#define GHUPDATE 2
 
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

int getRandom(int range);
uint64_t getSerial(void);
void displayHeader(const char *sname);
// void GhDelay(int milliseconds);

#endif
