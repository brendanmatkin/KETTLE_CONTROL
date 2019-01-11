extern "C" {
#include "user_interface.h"   // allows wifi_set_sleep_type
}

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

ESP8266WebServer server(80);                        // http server
WebSocketsServer webSocket = WebSocketsServer(81);  // websocket server

uint8_t res = 9;                                    // thermometer resolution (9, 10, 11, or 12)
int conversionTime = 750 / (1 << (12 - res));       // time for conversion


void setup() {
  wifi_set_sleep_type(NONE_SLEEP_T);    // disable sleep (might be related to analogRead)
  
  delay(500);
  Serial.begin(115200);
  Serial.println("Thermostat v.4.1.x (WiFi)");

  // update memory
  EEPROM.begin(sizeof(state));
  readFromEEPROM();

  // thermometer:
  setupThermometer(res, false);      //  (resolution, wait for conversion)

  networkInit();
  websocketInit();
  mdnsInit();
  serverInit();

  // pins:
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(BUZZER_PIN, LOW);

  //yield();
  delay(100);
}



void loop() {
  webSocket.loop();
  server.handleClient();
  
  // get temp async:
  static uint32_t _thermoTimer;
  if (millis() - _thermoTimer > conversionTime) {
    state.currentTemp = sensors.getTempC(thermoAddr);
    sendState();
    //if (DEBUG_SERIAL) Serial.printf("New Temperature: %.2fC\n", state.currentTemp);
    // put your main code here, to run repeatedly:
    sensors.requestTemperatures(); // Send the command to get temperatures
    _thermoTimer = millis();
  }
  
  if (state.currentTemp > state.setTemp) {
    //if (DEBUG_SERIAL) Serial.println("OFF");
    digitalWrite(RELAY_PIN, LOW);
    soundTheAlarm();
  }
  else {
    digitalWrite(RELAY_PIN, HIGH);       // maintain temp.. remove this line for single use
    resetAlarm();
  }

  eepromLoop();
}
