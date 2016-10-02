
/************* powerOn ****************/


unsigned long bTimer;        // button timer
unsigned long bDelay = 150;  // button delay
//int bThresh = 150;  // 150   // button threshold

unsigned long dispTimer;
unsigned long watchdogCount;
void powerOn() {
  //TODO:
  // - Change buttons to increment on tap (not hold)
  // - Update setMode so that buttons switch to true overrides 
  //   realTemp (passing set temp) switch to false
  
  // read "buttons"
  if (millis() - bTimer > bDelay) {
    int bUp = digitalRead(bUpPin);
    int bDwn = digitalRead(bDwnPin);
    if (bUp == LOW) {
      setTemp ++;
      setMode = true;                      // switch to set mode
      setTimer = millis();                 // reset timer
      bTimer = millis();
    }
    if (bDwn == LOW) {
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
  
  
  // thermotize!
  bool waterReady = false;
  if (realTemp >= setTemp) {
    waterReady = true;
    digitalWrite(relayPin, LOW);
    //setMode = false;   // display read temp
  } else {
    waterReady = false;
    digitalWrite(relayPin, HIGH);
  }

  if (alarm && waterReady) {
    if (watchdogCount % 2) {
      tone(tonePin, noteFreq, noteLength);
      alarm = false;
      //setWatchdog(0b000111);  // 2 seconds
      setWatchdog(0b100000);    // 4 seconds
    } else {
      tone(tonePin, noteFreq, noteLength);
      alarm = false;
      //setWatchdog(0b000011);  // 120 milliseconds
      setWatchdog(0b000100);    // 250 milliseconds
    }
  }
  
    // choose display value
  if (millis() - setTimer >= setDelay) {
    setMode = false;
  }
  
  if (setMode) {                             // set temperature mode
    displayTemp = setTemp;
//    if (millis()-dispTimer >= 700) {       // flash display (on for 700 ms)
//      printDisplay(-1);
//      dispTimer = millis();
//    } else if (millis()-dispTimer >= 80) { // (off for 80 ms)
//      printDisplay(displayTemp);
//    }
  } else {                                   // read temperature mode
    displayTemp = realTemp;
  }
  
  printDisplay(displayTemp);
  
  // get temperature
  //if (alarm) {
    if (millis() - tempTimer >= tempReadDelay+100) {
      getTemp(displayTemp);  // it takes between 209 - 211 ms to run this method.
      tempTimer = millis();
    }
  //}
}
