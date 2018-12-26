#ifndef SETTINGS_H
#define SETTINGS_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include <WebSocketsServer.h>
#include <Hash.h>

#include "wificonfig.h"   
// to track and stop tracking config.h: 
// git update-index --assume-unchanged FILE_NAME 
// git update-index --no-assume-unchanged FILE_NAME

const bool DEBUG_SERIAL = true;
#define AP_MODE true


/* -- network settings -- */
String deviceName = "Kettle_Thermostat";      // used for DHCP
const char* host  = "kettle";                 // used for mDNS
const char* ssid  = "your-ssid";              // unused for now
const char* password = "your-password";       // unused for now
const char* ssid_AP  = WIFI_SSID;             // see wificonfig.h
const char* password_AP = WIFI_PASSWORD;      // see wificonigh.h - **must be at least 8 characters!**

IPAddress local_IP(10, 0, 0, 1);              // static IP  - use staticIP[index] to get & set individual octets
IPAddress gateway(10, 0, 0, 1);               // gateway (for static)
IPAddress subnet(255, 255, 255, 0);           // subnet (for static)



enum OperatingMode {
  ON = 0,
  OFF = 1,
  STANDBY = 2,
  INTERNET = 3,
  ADJUST = 4
};

struct DeviceState {
  OperatingMode mode = ON;    // disable this for switch-based operation
  float currentTemp;
  float setTemp = 75.0f;      // celcius
  bool alarm = false;
  bool ready = false;
} state;

/*
let state = {
  currentTemp: 21.0,
  setTemp: 75.0,
  alarm: false,
  ready: false
}
*/


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
