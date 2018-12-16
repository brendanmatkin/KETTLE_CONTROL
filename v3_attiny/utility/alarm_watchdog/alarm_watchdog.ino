#include <avr/wdt.h>
#define tonePin 1

unsigned long alarmTimer;
int alarmInterval, noteLength;
volatile boolean alarm = true;
int watchdogCount;

void setup() {
  alarmTimer = millis();
  alarmInterval = 2400;
  noteLength = 70;
}

void loop() {
  int aT = millis() - alarmTimer;
  int tB = 5;   // time buffer in ms
  int alarmFreq = 4000;

  //  if (aT >= alarmInterval + noteLength*2 && aT < alarmInterval + noteLength*2 + tB) {
  //    tone(tonePin, alarmFreq, noteLength);
  //    alarmTimer = millis();
  //  } else if (aT >= alarmInterval && aT < alarmInterval + tB) {
  //    tone(tonePin, alarmFreq, noteLength);
  //  }
  if (alarm) {
    if (watchdogCount % 2) {
      tone(tonePin, alarmFreq, noteLength);
      alarm = false;
      setWatchdog(0b000111);
    } else {
      tone(tonePin, alarmFreq, noteLength);
      alarm = false;
      setWatchdog(0b000011);  // 2 seconds
    }
  }
}


