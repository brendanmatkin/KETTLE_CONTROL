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
  watchdogCount++;
  noInterrupts ();
  MCUSR = 0;                          // reset various flags
  WDTCSR |= 0b00011000;               // see docs, set WDCE, WDE
  WDTCSR =  0b01000000 | interval;    // set WDIE, and appropriate delay
  wdt_reset();
  interrupts ();
}
