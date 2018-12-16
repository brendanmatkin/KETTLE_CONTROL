void initThermo(int _displayTemp) {
  if ( !ds.search(thermoAddr)) {
    //no more sensors on chain, reset search
    ds.reset_search();
    return;
  }
  if ( OneWire::crc8( thermoAddr, 7) != thermoAddr[7]) {
    Serial.println("CRC is not valid!");
    return;
  }
  if ( thermoAddr[0] != 0x10 && thermoAddr[0] != 0x28) {
    Serial.print("Device is not recognized");
    return;
  }
  // change resolution
  ds.reset();
  printDisplay(_displayTemp);
  ds.skip();
  //  ds.select(thermoAddr);
  ds.write(0x4E);  // write to scratchpad
  printDisplay(_displayTemp);
  ds.write(0x4B);      // high alarm
  printDisplay(_displayTemp);
  ds.write(0x46);      // low alarm
  printDisplay(_displayTemp);
  ds.write(0x1F);  // config (resolution)  1F - 9, 3F - 10, 5F - 11, 7F - 12.
  printDisplay(_displayTemp);
  ds.reset();
  printDisplay(_displayTemp);
  ds.write(0x48);  // write eeprom
  printDisplay(_displayTemp);
  ds.reset();
  printDisplay(_displayTemp);

  // request temperatures
  ds.reset();
  printDisplay(_displayTemp);
  //ds.select(thermoAddr);
  ds.skip();        // single device
  ds.write(0x44); // start conversion
  printDisplay(_displayTemp);
}



/********** get temp **************/
/** put this together without DallasTemperture 
thanks to BLDR and looking through DallasTemp lib files **/
void getTemp(int _displayTemp) {
  ds.reset();
  printDisplay(_displayTemp);
  //ds.select(thermoAddr);
  ds.skip();                      // only works with one device. slightly faster
  printDisplay(_displayTemp);     // oneWire uses MANY delayMicroseconds. They add up
  ds.write(0xBE);                 // read scratchpad
  printDisplay(_displayTemp);
  byte inData[12];
  for (int i = 0; i < 9; i++) {   // may need to read all 9 bytes
    inData[i] = ds.read();
    printDisplay(_displayTemp);
  }
  ds.reset_search(); // ???
  
  byte T_MSB = inData[1];
  byte T_LSB = inData[0];
  int rawTemp = ((T_MSB << 8) | T_LSB);
  realTemp = (int)((float)(rawTemp >> 3) * 0.5);  // 9 bit conversion maths
  //rawTemp = rawTemp & ~7;
  //rawTemp = (float)rawTemp/16.0;

  ds.reset();
  printDisplay(_displayTemp);
  //ds.select(thermoAddr);
  ds.skip();
  printDisplay(_displayTemp);
  ds.write(0x44, 1); // start conversion
}
