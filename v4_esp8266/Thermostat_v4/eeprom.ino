uint32_t eepromTimer;
boolean eepromReady = false;

void writeToEEPROM() {
  eepromTimer = millis();
  eepromReady = true;
}



void eepromLoop() {
  if ((millis() - eepromTimer > 500) && eepromReady) {
    eepromReady = false;
    //storage = state;                      // copy struct
    //EEPROM.put(0, storage);
    EEPROM.put(0, state);
    boolean ok = EEPROM.commit();         // write the data to EEPROM
    Serial.print("[EEP] ");
    Serial.println((ok) ? "Commit OK" : "Commit failed (or data unchanged)");
  }
}



void readFromEEPROM() {
  Serial.print("[EEP] ");
  if(EEPROM.percentUsed()>=0) {

    EEPROM.get(0, state);
//    EEPROM.get(0, storage);
//    state = storage;
    Serial.println("EEPROM has data from a previous run.");
    Serial.print(EEPROM.percentUsed());
    Serial.println("% of ESP flash space currently used");
  } else {
    Serial.println("EEPROM size changed - EEPROM data zeroed - commit() to make permanent");    
  }
}
