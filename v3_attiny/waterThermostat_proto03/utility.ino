#include <avr/wdt.h>

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
  ds.write(0x4E);             // write to scratchpad
  printDisplay(_displayTemp);
  ds.write(0x4B);             // high alarm
  printDisplay(_displayTemp);
  ds.write(0x46);             // low alarm
  printDisplay(_displayTemp);
  ds.write(0x1F);             // config (resolution)  1F - 9, 3F - 10, 5F - 11, 7F - 12.
  printDisplay(_displayTemp);
  ds.reset();
  printDisplay(_displayTemp);
  ds.write(0x48);             // transfer from scratchpad to eeprom
  printDisplay(_displayTemp);
  ds.reset();
  printDisplay(_displayTemp);

  // request temperatures
  ds.reset();
  printDisplay(_displayTemp);
  //ds.select(thermoAddr);
  ds.skip();                  // single device (instead of ds.select(xxxx))
  ds.write(0x44);             // start conversion
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
  //byte inData[tempRes];
  for (int i = 0; i < 9; i++) {   // may need to read all 9 bytes
    inData[i] = ds.read();
    printDisplay(_displayTemp);
  }
  ds.reset_search(); // ???

  // does the following math only work with 9 bit resolution? 
  byte Temp_MSB = inData[1];
  byte Temp_LSB = inData[0];
  int16_t rawTemp = ((Temp_MSB << 8) | Temp_LSB);
  //realTemp = (int)((float)(rawTemp >> 3) * 0.5);  // 9 bit conversion maths
  rawTemp = rawTemp & ~7;
  float _temp = (float)rawTemp/16.0;
  realTemp = (int)_temp;

  ds.reset();
  printDisplay(_displayTemp);
  //ds.select(thermoAddr);
  ds.skip();
  printDisplay(_displayTemp);
  ds.write(0x44, 1); // start conversion
}


// watchdog stuff (for alarm): 
ISR (WDT_vect) 
{
  //fireAlarm();
  alarm = true;
}


// wdt bit patterns (interval):
    //  15ms:      0b000000
    //  30ms:      0b000001
    //  60ms:      0b000010
    //  120ms:     0b000011
    //  250ms:     0b000100
    //  500ms:     0b000101
    //  1 second:  0b000110
    //  2 seconds: 0b000111
    //  4 seconds: 0b100000
    //  8 seconds: 0b100001
void setWatchdog (const byte interval) { 
  noInterrupts ();
  MCUSR = 0;                          // reset various flags
  WDTCSR |= 0b00011000;               // see docs, set WDCE, WDE
  WDTCSR =  0b01000000 | interval;    // set WDIE, and appropriate delay
  wdt_reset();
  interrupts ();
}
