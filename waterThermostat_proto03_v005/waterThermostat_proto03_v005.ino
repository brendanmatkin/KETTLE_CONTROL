#include <OneWire.h>  
#include <DallasTemperature.h>


#define data      11  // attiny change to 0
#define clk       12  // attiny change to 1
#define thermoPin  2
#define dig1       3
#define dig2       4
#define relayPin   5
#define tonePin    6
#define pwrPin     7
#define modePin    8
#define bUpPin    A0
#define bDwnPin   A1

//** temp value (for counting) - DELETE ME
  int val; 
  unsigned long timer;
  unsigned long del = 500;
//** end temp

boolean masterPower;
boolean offMode;



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
  timer = millis();          // TEMP - DELETE ME
  
  // inputs init
  pinMode(pwrPin, INPUT_PULLUP);
  pinMode(modePin, INPUT_PULLUP);
  masterPower = digitalRead(pwrPin);
  offMode = digitalRead(modePin);
  
  //outputs init
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
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



