void initThermo() {
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
  //  ds.reset();
  //  ds.select(thermoAddr);
  //  ds.write(0x4E);  // write to scratchpad
  //  ds.write(0x1F);

  // request temperatures
  ds.reset();
  //ds.select(thermoAddr);
  ds.skip();        // single device
  ds.write(0x44); // start conversion
}



/********** get temp **************/

void getTemp() {
  ds.reset();
  printDisplay(realTemp);
  //ds.select(thermoAddr);
  ds.skip();                      // only works with one device. slightly faster
  printDisplay(realTemp);         // oneWire uses MANY delayMicroseconds. They add up
  ds.write(0xBE);                 // read scratchpad
  printDisplay(realTemp);
  byte inData[12];
  for (int i = 0; i < 9; i++) {   // may need to read all 9 bytes
    inData[i] = ds.read();
    printDisplay(realTemp);
  }
  //ds.reset_search(); // ???
  
  byte T_MSB = inData[1];
  byte T_LSB = inData[0];
  int rawTemp = ((T_MSB << 8) | T_LSB);
  realTemp = (int)((float)(rawTemp >> 3) * 0.5);  // 9 bit conversion maths

  ds.reset();
  printDisplay(realTemp);
  //ds.select(thermoAddr);
  ds.skip();
  printDisplay(realTemp);
  ds.write(0x44); // start conversion
}
