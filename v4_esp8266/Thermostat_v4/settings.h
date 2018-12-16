#ifndef SETTINGS_H
#define SETTINGS_H

#define DEBUG_SERIAL true

enum OperatingMode {
  ON,
  OFF,
  STANDBY,
  INTERNET,
  ADJUST
};

struct DeviceState {
  OperatingMode mode = ON;    // disable this for switch-based operation
  //float readTemp;
  float setTemp = 75.0f;      // celcius
} state;



uint32_t alarmOnTime    = 100;
uint32_t alarmOffTime   = 1000;
uint32_t alarmTotalTime = 30000;
bool     alarmComplete  = false;

int freq = 200;

/*
int freq[]={1047,1175,1319,1397,1568,1760,1976,2093};//Note name: C6 D6 E6 F6 G6 A6 B6 C7   http://newt.phys.unsw.edu.au/jw/notes.html
String note[]={"C6", "D6", "E6", "F6", "G6", "A6", "B6", "C7"};
*/

#endif /* SETTINGS_H */
