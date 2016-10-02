#include <OneWire.h>
#include <NewTone.h>

//#define data      11  // attiny change to 0
//#define clk       12  // attiny change to 1
#define data       0
#define clk        1
#define thermoPin  2
#define dig1       3
#define dig2       4
#define relayPin   5
#define tonePin    6
#define pwrPin     7
#define modePin    8
#define bUpPin     9
#define bDwnPin   10

OneWire ds(thermoPin);   // thermometer pin
byte thermoAddr[8];      // thermometer address

boolean masterPower;     // running or not
boolean offMode;         // relay on or off in standby
boolean setMode = true;  // set temperature with buttons

int setTemp = 75;        // default temperature threshold
int realTemp;            // actual temperature from thermo
int displayTemp;         // placeholder to switch back and forth
int tempRes = 9;         // resolution (9-12 bit)
int tempReadDelay;       // calculated wait time to check temp
unsigned long tempTimer; // wait time timer

int setDelay = 2500;     // after no input button, wait this long to switch back to realTemp
unsigned long setTimer;  // timer for setting

//int toneFreq = 2000;
//int toneDelay = 500;
unsigned long toneTimer;


/************* SETUP ****************/

void setup() {
  Serial.begin(9600);

  // display init
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(dig1, OUTPUT);
  pinMode(dig2, OUTPUT);
  digitalWrite(dig1, LOW);
  digitalWrite(dig2, HIGH);

  // inputs init
  pinMode(pwrPin, INPUT_PULLUP);
  pinMode(modePin, INPUT_PULLUP);
  pinMode(bUpPin, INPUT_PULLUP);
  pinMode(bDwnPin, INPUT_PULLUP);
  masterPower = digitalRead(pwrPin);
  offMode = digitalRead(modePin);

  // outputs init
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  pinMode(tonePin, OUTPUT);

  // thermometer init
  printDisplay(setTemp);
  initThermo(setTemp);
  tempReadDelay = 750 / (1 << (12 - tempRes));
  tempTimer = millis();
  
  setTimer = millis();
  
  // read temp to start
//  printDisplay(setTemp);
//  delay(tempReadDelay);
//  getTemp(-1);
//  delay(100);
}


/************* LOOP ****************/

void loop() {
  masterPower = digitalRead(pwrPin);
  offMode = digitalRead(modePin);

  if (masterPower) {
    powerOn();
  } else {
    standby();
  }
}


/************* STANDBY ****************/

void standby() {
  if (offMode) {
    digitalWrite(relayPin, LOW);
  } else {
    digitalWrite(relayPin, HIGH);
  }
  printDisplay(-1);
}



