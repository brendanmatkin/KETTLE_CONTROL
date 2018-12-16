#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP_EEPROM.h>
#include "settings.h"

#define RELAY_PIN     2        // relay
#define BUZZER_PIN    14       // aka D5

//thermometer
#define ONE_WIRE_BUS  13       // thermometer
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress thermoAddr;



void setup() {
  delay(500);
  Serial.begin(115200);
  Serial.println("Thermostat v.4.x");

  // update memory
  EEPROM.begin(sizeof(state));
  readFromEEPROM();

  // thermometer:
  setupThermometer();

  // pins:
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(BUZZER_PIN, LOW);
  
  //yield();
  delay(100);
}



void loop() {
  // ****   TODO - use OneWire library (see example code) to implement non-blocking behaviour.   *** 
  //Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");
  
  float tempC = sensors.getTempC(thermoAddr);
  if (DEBUG_SERIAL) Serial.printf("Temerature: %.2fC\n", tempC);
  // put your main code here, to run repeatedly:
  if (tempC > state.setTemp) {
    Serial.println("OFF");
    digitalWrite(RELAY_PIN, LOW);
    soundTheAlarm();
  }
  else {
    digitalWrite(RELAY_PIN, HIGH);       // maintain temp.. remove this line for single use
    resetAlarm();
  }
  
  eepromLoop();
}
