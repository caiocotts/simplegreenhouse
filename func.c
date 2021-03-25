#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

unsigned long long int GetSerial(void)
{

  FILE *fp;
  static unsigned long long int serial = 0;
  char buf[BUFSIZE];

  // print text from cpuinfo, filter "Serial", filter any numbers,
  // pass numbers into serialnum
  system("grep Serial /proc/cpuinfo | grep -Po '[\\d]+'> serialnum");
  fp = fopen("serialnum", "r");
  if (fp != NULL)
  {
    fscanf(fp, "%Lx", &serial);
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
  fprintf(stdout, "%s' Greenhouse Controller\n\n\n", sname);
}

void ControllerInit(void)
{
  srand((unsigned)time(NULL));
  DisplayHeader("Caio Cotts");
}

void DisplayReadings(struct readings rdata)
{

  fprintf(stdout,
          "\nUnit:%Lx %s Readings\tT: %5.1lfC\tH: %5.1lf%%\tP: %6.1lfmb\n ",
          GetSerial(), ctime(&rdata.rtime), rdata.temperature, rdata.humidity,
          rdata.pressure);
}

double GetHumidity(void)
{
#if SIMHUMIDITY
  return GetRandom(USHUMID - LSHUMID) + LSHUMID;
#else
  return 55.0;
#endif
}

double GetPressure(void)
{
#if SIMPRESSURE
  return GetRandom(USPRESS - LSPRESS) + LSPRESS;
#else
  return 1013.0;
#endif
}

double GetTemperature(void)
{

#if SIMTEMPERATURE
  return GetRandom(USTEMP - LSTEMP) + LSTEMP;
#else
  return 20.0;
#endif
}

struct readings GetReadings(void)
{
  struct readings now = {0};

  now.rtime = time(NULL);
  now.temperature = GetTemperature();
  now.humidity = GetHumidity();
  now.pressure = GetPressure();
  return now;
}

struct controls SetControls(struct setpoints target, struct readings rdata)
{
  struct controls cset = {0};

  if (rdata.temperature < target.temperature)
  {
    cset.heater = ON;
  }
  else
  {
    cset.heater = OFF;
  }
  if (rdata.humidity < target.humidity)
  {
    cset.humidifier = ON;
  }
  else
  {
    cset.humidifier = OFF;
  }
  return cset;
}

struct setpoints SetTargets(void)
{
  struct setpoints cpoints = RetrieveSetPoints("setpoints.dat");
  if (cpoints.temperature == 0)
  {
    cpoints.temperature = STEMP;
    cpoints.humidity = SHUMID;
    SaveSetPoints("setpoints.dat", cpoints);
  }

  return cpoints;
}

void DisplayTargets(struct setpoints spts)
{
  fprintf(stdout, "Targets\tT: %5.1lfC\tH: %5.1lf%%\n", spts.temperature, spts.humidity);
}

void DisplayControls(struct controls ctrl)
{
  fprintf(stdout, " Controls\tHeater: %i\tHumidifier: %i\n", ctrl.heater,
          ctrl.humidifier);
}

int LogData(char *fname, struct readings ghdata)
{
  FILE *fp;
  char ltime[CTIMESTRSZ];
  fp = fopen(fname, "a");
  if (fp == NULL)
  {
    return 0;
  }
  strcpy(ltime, ctime(&ghdata.rtime));
  ltime[3] = ',';
  ltime[7] = ',';
  ltime[10] = ',';
  ltime[19] = ',';

  fprintf(fp, "\n%.24s,%5.1lf,%5.1lf,%6.1lf",
          ltime, ghdata.temperature, ghdata.humidity,
          ghdata.pressure);
  fclose(fp);
  return 1;
}

int SaveSetPoints(char *fname, struct setpoints spts)
{
  FILE *fp;
  fp = fopen(fname, "w");
  if (fp == NULL)
  {
    return 0;
  }
  fwrite(&spts, sizeof(struct setpoints), 1, fp);
  fclose(fp);
  return 1;
}

struct setpoints RetrieveSetPoints(char *fname)
{
  struct setpoints spts = {0};
  FILE *fp;
  fp = fopen(fname, "r");
  if (fp == NULL)
  {
    return spts;
  }
  fread(&spts, sizeof(struct setpoints), 1, fp);
  fclose(fp);
  return spts;
}