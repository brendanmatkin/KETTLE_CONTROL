
/************* powerOn ****************/


unsigned long bTimer;
unsigned long bDelay = 200;
int bThresh = 150;

void powerOn() {
  // set relay
  digitalWrite(relayPin, HIGH);
  

  // read "buttons"
  if (millis() - bTimer > bDelay) {
    int bUp = analogRead(bUpPin);
    int bDwn = analogRead(bDwnPin);
    //Serial.print(bUp); Serial.print(" , "); Serial.println(bDwn); 

    if (bUp < bThresh) {
      setTemp ++;
      bTimer = millis();
    }
    if (bDwn < bThresh) {
      setTemp --;
      bTimer = millis();
    }
    if (setTemp >= 99) {
      setTemp = 99;
    } else if (setTemp <= 0) {
      setTemp = 0;
    }
  }
  
  // get temperature
  if (millis() - tempTimer >= tempReadDelay) {
    realTemp = thermos.getTempC(thermometer);
    thermos.requestTemperatures();
    tempReadDelay = millis();
  }
  
  // output display
  printDisplay(realTemp);
}
