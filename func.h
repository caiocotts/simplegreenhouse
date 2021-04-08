#ifndef SIMPLEGREENHOUSE_H
#define SIMPLEGREENHOUSE_H
#include "pisensehat.h"
#include <stdint.h>
#include <time.h>

#define USHUMID 100
#define LSHUMID 0
#define SEARCHSTR "serial\t\t: "
#define BUFSIZE 512
#define DELAY_INTERVAL 2
#define USTEMP 50
#define LSTEMP -10
#define USPRESS 1016
#define LSPRESS 975
#define STEMP 25.0
#define SHUMID 55.0
#define ON 1
#define OFF 0
#define SIMTEMPERATURE 0
#define SIMHUMIDITY 0
#define SIMPRESSURE 0
#define CTIMESTRSZ 25
#define NUMBARS 8
#define NUMPTS 8.0
#define TBAR 7
#define HBAR 5
#define PBAR 3
#define SENSEHAT 1

typedef struct readings {
  time_t rtime;
  double temperature;
  double humidity;
  double pressure;
} readings;

typedef struct setpoints {
  double temperature;
  double humidity;
} setpoints;

typedef struct controls {
  int heater;
  int humidifier;
} controls;

int GetRandom(int range);
uint64_t GetSerial(void);
void DisplayHeader(const char *sname);
void Delay(int milliseconds);
void ControllerInit(void);
void DisplayControls(controls ctrl);
void DisplayReadings(readings rdata);
void DisplayTargets(setpoints spts);
controls SetControls(setpoints target, readings rdata);
setpoints SetTargets(void);
double GetHumidity(void);
double GetPressure(void);
double GetTemperature(void);
readings GetReadings(void);
int LogData(char *fname, readings ghdata);
int SaveSetPoints(char *fname, setpoints spts);
setpoints RetrieveSetPoints(char *fname);
void DisplaySplashScreen(void);
void DisplayOnMatrix(readings values, setpoints targets);
void RedTextColour();
void BlackTextColour();
void GreenTextColour();
void YellowTextColour();
void BlueTextColour();
void PurpleTextColour();
void CyanTextColour();
void WhiteTextColour();
void ResetTextColour();

#endif