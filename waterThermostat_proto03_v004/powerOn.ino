
/************* powerOn ****************/

void powerOn() {
  digitalWrite(relayPin, HIGH);
  printDisplay(val);
  //Serial.println(val);
  if (val < 99) {
    if (millis() - timer > del) {
      val++;
      timer = millis();
    }
  } else {
    val = 0;
  }
}
