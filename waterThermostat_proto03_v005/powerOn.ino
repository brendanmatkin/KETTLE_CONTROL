
/************* powerOn ****************/

void powerOn() {
  digitalWrite(relayPin, HIGH);
  
  //** temp counting - DELETE ME
  printDisplay(val);
  if (val < 99) {
    if (millis() - timer > del) {
      val++;
      timer = millis();
    }
  } else {
    val = 0;
  }
  //** end temp
}
