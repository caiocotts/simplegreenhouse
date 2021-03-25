#ifndef SIMPLEGREENHOUSE_H
#define SIMPLEGREENHOUSE_H
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
#define SIMTEMPERATURE 1
#define SIMHUMIDITY 1
#define SIMPRESSURE 1
#define CTIMESTRSZ 25

struct readings {
  time_t rtime;
  double temperature;
  double humidity;
  double pressure;
};
struct setpoints {
  double temperature;
  double humidity;
};
struct controls {
  int heater;
  int humidifier;
};

int GetRandom(int range);
uint64_t GetSerial(void);
void DisplayHeader(const char *sname);
void Delay(int milliseconds);
void ControllerInit(void);
void DisplayControls(struct controls ctrl);
void DisplayReadings(struct readings rdata);
void DisplayTargets(struct setpoints spts);
struct controls SetControls(struct setpoints target, struct readings rdata);
struct setpoints SetTargets(void);
double GetHumidity(void);
double GetPressure(void);
double GetTemperature(void);
struct readings GetReadings(void);
int LogData(char *fname, struct readings ghdata);
int SaveSetPoints(char *fname, struct setpoints spts);
struct setpoints RetrieveSetPoints(char *fname);
void DisplaySplashScreen(void);

#endif