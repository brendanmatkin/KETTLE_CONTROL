//uint32_t alarmOnTime    = 50;
//uint32_t alarmOffTime   = 700;
//uint32_t alarmTotalTime = 5000;
//bool     alarmComplete  = false;

uint32_t alarmTimer, alarmTimer2;
void soundTheAlarm() {
  if (!alarmComplete) {
//    if (millis() - alarmTimer > alarmOnTime) {
//      if ( millis() - alarmTimer > (alarmOffTime + alarmOnTime) ) {
//        noTone(BUZZER_PIN);
//        alarmTimer = millis();
//      }
//      else {
//        tone(BUZZER_PIN, freq);
//      }
//    }
    if (millis() - alarmTimer > alarmOffTime) {
      tone(BUZZER_PIN, freq, alarmOnTime);
      alarmTimer = millis();
      freq+=5;
    }
    if (millis() - alarmTimer2 > alarmTotalTime) {
      alarmComplete = true;
      noTone(BUZZER_PIN);
    }
  }
}

void resetAlarm() {
  alarmComplete = false;
  alarmTimer  = millis();
  alarmTimer2 = millis();
  noTone(BUZZER_PIN);
}



// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}


void setupThermometer() {
  Serial.print("Locating oneWire devices...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");
  if (!sensors.getAddress(thermoAddr, 0)) Serial.println("Unable to find address for Device 0"); 
  //verify:
  Serial.print("Device 0 Address: ");
  printAddress(thermoAddr);
  Serial.println();
  sensors.setResolution(thermoAddr, 9);
  //verify:
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(thermoAddr), DEC); 
}
