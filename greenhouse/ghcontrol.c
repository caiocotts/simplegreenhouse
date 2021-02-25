/**  @brief Functions
 *   @file ghcontrol.c
 */

#include "ghcontrol.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**  @brief Delay the program for a specified amount of time.
 *   @version 18FEB2021
 *   @author Caio Cotts
 *   @param milliseconds integer variable of time in milliseconds
 *   @return void
 */
void GhDelay(int milliseconds) {
  long wait;
  clock_t now, start;

  wait = milliseconds * (CLOCKS_PER_SEC / 1000);
  start = clock();
  now = start;
  while ((now - start) < wait) {
    now = clock();
  }
}

/**  @brief Get serial number, if it's not found, find
 * the timestamp of /usr/lib/codeblocks.
 *   @version 18FEB2021
 *   @author Caio Cotts
 *   @return Serial number
 */
uint64_t GhGetSerial(void) {
  static uint64_t serial = 0;
  FILE *fp;
  char buf[SYSINFOBUFSZ];
  char searchstring[] = SEARCHSTR;

  fp = fopen("/proc/cpuinfo", "r");

  if (fp != NULL) {
    while (fgets(buf, sizeof(buf), fp) != NULL) {
      if (!strncasecmp(searchstring, buf, strlen(searchstring))) {
        sscanf(buf + strlen(searchstring), "%Lx", &serial);
      }
    }
    fclose(fp);
  }
  return serial;
}

// static uint64_t serial = 0;
// FILE *fp;
// char buf[SYSINFOBUFSZ];
// char searchstring[] = SEARCHSTR;
// fp = fopen("/proc/cpuinfo", "r");
// if (fp != NULL) {
//   while (fgets(buf, sizeof(buf), fp) != NULL) {
//     if (!strncasecmp(searchstring, buf, strlen(searchstring))) {
//       sscanf(buf + strlen(searchstring), "%Lx", &serial);
//     }
//   }
//   fclose(fp);
// }
// if (serial == 0) {
//   system("uname -a");
//   system("ls --fu /usr/lib/codeblocks | grep -Po '\\.\\K[^ ]+'>stamp.txt");
//   fp = fopen("stamp.txt", "r");
//   if (fp != NULL) {
//     while (fgets(buf, sizeof(buf), fp) != NULL) {
//       sscanf(buf, "%lu", &serial);
//     }
//     fclose(fp);
//   }
// }
// return serial;
//}

/**  @brief Generate random.
 *   @version 18FEB2021
 *   @author Caio Cotts
 *   @param range integer value holding a range
 *   @return Random integer
 */
int GhGetRandom(int range) { return rand() % range; }

/**  @brief Print greenhouse controller header the user's name.
 *   @version 18FEB2021
 *   @author Caio Cotts
 *   @param sname string with user's name
 *   @return void
 */
void GhDisplayHeader(const char *sname) {
  fprintf(stdout, "%s' Greenhouse Controller\n\n\n", sname);
}

/**  @brief Generate a seed based on the current time whcih will
 *  be used by any rand functions and calls GhDisplayHeader.
 *   @version 18FEB2021
 *   @author Caio Cotts
 *   @return void
 */
void GhControllerInit(void) {
  srand((unsigned)time(NULL));
  GhDisplayHeader("Caio Cotts");
}

/**  @brief Display current time and sensor readings
 *   @version 18FEB2021
 *   @author Caio Cotts
 *   @param rtime value holding current time
 *   @param dreads array with values for
 * temperature, humidity, and pressure.
 *   @return void
 */
void GhDisplayReadings(time_t rtime, double dreads[SENSORS]) {

  fprintf(stdout,
          "\nUnit:%Lx %s Readings\tT: %5.1lfC\tH: %5.1lf%%\tP: %6.1lfmb\n ",
          GhGetSerial(), ctime(&rtime), dreads[TEMPERATURE], dreads[HUMIDITY],
          dreads[PRESSURE]);
}

/**  @brief Measure humidity.
 *   @version 18FEB2021
 *   @author Caio Cotts
 *   @return Humidity as a percentage.
 */
double GhGetHumidity(void) {
#if SIMULATE
  return GhGetRandom(USHUMID - LSHUMID) + LSHUMID;
#else
  return 55.0;
#endif
}

/**  @brief Measure pressure.q
 *   @version 18FEB2021
 *   @author Caio Cotts
 *   @return Humidity in millibars.
 */
double GhGetPressure(void) {
#if SIMULATE
  return GhGetRandom(USPRESS - LSPRESS) + LSPRESS;
#else
  return 1013.0;
#endif
}

/**  @brief Measure temperature.
 *   @version 18FEB2021
 *   @author Caio Cotts
 *   @return Temperature in degrees Celcius
 */
double GhGetTemperature(void) {

#if SIMULATE
  return GhGetRandom(USTEMP - LSTEMP) + LSTEMP;
#else
  return 20.0;
#endif
}

/**  @brief Take all returned values
 * from GhGetTemperature, GhGetHumidity, and GhGetPressure
 * and place them in an array.
 *   @version 18FEB2021
 *   @author Caio Cotts
 *   @param readings array with sensor readings
 *   @return void
 */
void GhGetReadings(double readings[SENSORS]) {

  readings[TEMPERATURE] = GhGetTemperature();
  readings[HUMIDITY] = GhGetHumidity();
  readings[PRESSURE] = GhGetPressure();
}

/**  @brief Change the states of the heater and humidifier on or off
 * given the current readings
 *   @version 18FEB2021
 *   @author Caio Cotts
 *   @param heater pointer to the state of the heater
 *   @param humidifier pointer to the state of the humidifier
 *   @param readings array with sensor readings
 *   @return void
 */
void GhSetControls(int *heater, int *humidifier, double readings[SENSORS]) {
  if (readings[TEMPERATURE] < STEMP) {
    *heater = ON;
  } else {
    *heater = OFF;
  }
  if (readings[HUMIDITY] < SHUMID) {
    *humidifier = ON;
  } else {
    *humidifier = OFF;
  }
}

void GhSetTargets(void) {}

/**  @brief Display environment values that the controller is
 * set to maintain, like temperature and humidity.
 *   @version 18FEB2021
 *   @author Caio Cotts
 *   @return void
 */
void GhDisplayTargets(void) {
  fprintf(stdout, "Targets\tT: %5.1lfC\tH: %5.1lf%%\n", STEMP, SHUMID);
}

/**  @brief Display the state of the heater and humidifier.
 *   @version 18FEB2021
 *   @author Caio Cotts
 *   @param heater pointer to the state of the heater
 *   @param humidifier pointer to the state of the humidifier
 *   @return void
 */
void GhDisplayControls(int *heater, int *humidifier) {
  fprintf(stdout, " Controls\tHeater: %i\tHumidifier: %i\n", *heater,
          *humidifier);
}