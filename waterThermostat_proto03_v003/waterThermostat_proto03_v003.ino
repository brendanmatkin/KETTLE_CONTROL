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


int val;
unsigned long timer;
unsigned long del = 500;


void setup() {
  Serial.begin(9600);
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);
  
  pinMode(dig1, OUTPUT);
  pinMode(dig2, OUTPUT);
  digitalWrite(dig1, LOW);
  digitalWrite(dig2, HIGH);
  timer = millis();
}

void loop() {
  //int aa = analogRead(0)/4;

  printDisplay(val);
  if (val < 99) {
    if (millis() - timer > del) {
      val++;
      timer = millis();
    }
  } else {
    val = 0;
  }
}
