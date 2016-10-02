
/************* powerOn ****************/


unsigned long bTimer;
unsigned long bDelay = 100;
int bThresh = 150;  // 150

void powerOn() {
  // set relay
  digitalWrite(relayPin, HIGH);


  // read "buttons"
  
//  if (bUp < bThresh || bDwn < bThresh) { // if hand is near button
//    setTimer = millis();                 // reset timer
//    setMode = true;                      // switch to set mode
//  }
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
  
  if (setMode) {
    displayTemp = setTemp;
  } else {
    displayTemp = realTemp;
  }

  // get temperature
  if (millis() - tempTimer >= tempReadDelay) {
    getTemp(displayTemp);  // it takes between 209 - 211 ms to run this method.
    tempTimer = millis();
  }

  // output display
  printDisplay(displayTemp);
}
