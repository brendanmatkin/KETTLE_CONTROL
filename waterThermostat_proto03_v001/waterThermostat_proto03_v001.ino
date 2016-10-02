#include <OneWire.h>  
#include <DallasTemperature.h>
#include <Bounce2.h>

#define tonePin 0
#define buttonPin 1     // button to switch display
#define ONE_WIRE_BUS 2  // temp pin
#define buttonUp 3
#define buttonDown 4
#define relayPin 5

#define dispLatch 6
#define dispData 7
#define dispClock 8
#define digit_1 9
#define digit_2 10

OneWire oneWire(ONE_WIRE_BUS);       // temp pin
DallasTemperature sensors(&oneWire);
DeviceAddress thermometer;

Bounce butt = Bounce();  // button

// numbers 0-9 for the way I wired my 7 segment display using 74HC164N
byte numbers[] = {
  B10010000, B11111100, B00110010, B00110100, B01011100, 
  B00010101, B00010001, B10111100, B00010000, B00011100
};

int temp;                     // temperature from thermometer
int setTemp;                  // alarm temperature
int inc = 5;                  // temperature increment
int dig_1;                    // 1st digit on 7 seg LED
int dig_2;                    // 2nd digit on 7 seg LED
boolean tempDisplay = false; 
unsigned long timer;

int resolution = 12;
unsigned long lastTempRequest = 0;
int delayInMillis;


void setup(){
  pinMode(dispClock, OUTPUT); 
  pinMode(dispData, OUTPUT);
  pinMode(digit_1, OUTPUT);
  pinMode(digit_2, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);

  sensors.begin();
  sensors.getAddress(thermometer, 0);
  sensors.setResolution(thermometer, resolution);
  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();
  delayInMillis = 750 / (1 << (12 - resolution));
  lastTempRequest = millis();
  
  digitalWrite(relayPin, LOW);
  setTemp = 75;
}


void loop(){   
  if (digitalRead(buttonUp) == 0) { 
    setTemp += inc; 
    delay(200); 
  }
  if (digitalRead(buttonDown) == 0) {
    setTemp -= inc;
    delay(200);
  }
  if (setTemp >= 100) setTemp = 100;
  if (setTemp <= 5) setTemp = 5;
  if (digitalRead(buttonPin) == 0) {
    tempDisplay = !tempDisplay;
    delay(200);
  }
  if (millis() - lastTempRequest >= delayInMillis) {
    temp = int(sensors.getTempC(thermometer));
    sensors.requestTemperatures();
    lastTempRequest = millis();
  }
  int n;
  if (tempDisplay) n = temp;
  else n = setTemp;
  dig_1 = ((n/10)%10);
  dig_2 = (n%10);

  ledDisplay(5);

  if (temp >= setTemp) {
    digitalWrite(relayPin, HIGH);
    if (millis()-timer > 1700) {
      tone(tonePin,300,75);
      delay(60);
      tone(tonePin,315,75);
      timer = millis();
    }
  }
  else {
    digitalWrite(relayPin, LOW);
    noTone(tonePin);
  }
}

