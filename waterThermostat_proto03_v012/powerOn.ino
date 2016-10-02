
/************* powerOn ****************/


unsigned long bTimer;
unsigned long bDelay = 100;
int bThresh = 150;  // 150

unsigned long dispTimer;

void powerOn() {
  
  // read "buttons"
  if (millis() - bTimer > bDelay) {
    int bUp = analogRead(bUpPin);
    int bDwn = analogRead(bDwnPin);
    //Serial.print(bUp); Serial.print(" , "); Serial.println(bDwn);
    //Serial.println(bDelay);
    if (bUp < bThresh) {
      setTemp ++;
      setMode = true;                      // switch to set mode
      setTimer = millis();                 // reset timer
      bTimer = millis();
    }
    if (bDwn < bThresh) {
      setTemp --;
      setMode = true;                      // switch to set mode
      setTimer = millis();                 // reset timer
      bTimer = millis();
    }
    if (setTemp >= 99) {
      setTemp = 99;
    } else if (setTemp <= 0) {
      setTemp = 0;
    }
  }
  
  // choose display value
  if (millis() - setTimer >= setDelay) {
    setMode = false;
  }
  
  //bool readTemp = false;
  if (setMode) {                           // set temperature mode
    displayTemp = setTemp;
//    if (millis()-dispTimer >= 700) {       // flash display (on for 700 ms)
//      dispTimer = millis();
//    } else if (millis()-dispTimer >= 80) { // (off for 80 ms)
//      printDisplay(displayTemp);
//    }
  } else {                                 // read temperature mode
    //readTemp = true;
    displayTemp = realTemp;
  }
  printDisplay(displayTemp);
  
  // thermotize!
  bool beeping = false;
  if (realTemp >= setTemp) {
    beeping = marioTone(150, 100);
    digitalWrite(relayPin, HIGH);
    setMode = false;   // display read temp
  } else {
    digitalWrite(relayPin, LOW);
    noTone(tonePin);
    toneTimer = millis();
  }
  
  // get temperature
  if (!beeping) {
    if (millis() - tempTimer >= tempReadDelay+100) {
      getTemp(displayTemp);  // it takes between 209 - 211 ms to run this method.
      tempTimer = millis();
    }
  }
}
