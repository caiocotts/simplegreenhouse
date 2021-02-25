#include "func.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long long int GetSerial(void)
{

  FILE *fp;
  static unsigned long long int serial = 0;
  char buf[BUFSIZE];

  // print text from cpuinfo, filter "Serial", filter any numbers,
  // pass numbers into serialnum
  system("cat /proc/cpuinfo | grep Serial | grep -Po '[\\d]+'> serialnum");
  fp = fopen("serialnum", "r");
  if (fp != NULL)
  {
    fscanf(fp, "%llu", &serial);
    fclose(fp);
  }
  else
  {
    return 0;
  }

  return serial;
}

int GetRandom(int range) { return rand() % range; }

void DisplayHeader(const char *sname)
{
  printf("%s's Greenhouse Controller\n\n\n", sname);
}
void ControllerInit(void)
{
  srand((unsigned)time(NULL));
  DisplayTargets();
  DisplayHeader("Anon");
}

double GetHumidity(void)
{
#if SIMULATE
  return GetRandom(USHUMID - LSHUMID) + LSHUMID;
#else
  return 55.0;
#endif
}
double GetPressure(void)
{
#if SIMULATE
  return GhGetRandom(USPRESS - LSPRESS) + LSPRESS;
#else
  return 1013.0;
#endif
}
double GetTemperature(void)
{
#if SIMULATE
  return GhGetRandom(USTEMP - LSTEMP) + LSTEMP;
#else
  return 20.0;
#endif
}
