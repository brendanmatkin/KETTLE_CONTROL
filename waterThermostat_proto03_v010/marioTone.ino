boolean marioTone(int nL, int tL) {
  int freq = 2637; // an E
  int sT = nL*15;  // restart time
  //int tL = 75;   // tone length
  //int nL = 120;  // note length
  
  if (millis() - toneTimer >= sT + (nL * 12) + tL) { //2850
    noTone(tonePin);
    toneTimer = millis();
    return true;
  } else if (millis() - toneTimer >= sT + (nL * 12)) { //2800
    tone(tonePin, freq - 1050);              // 7
  } else if (millis() - toneTimer >= sT + (nL * 8) + tL) { //1900
    noTone(tonePin);
  } else if (millis() - toneTimer >= sT + (nL * 8)) { //1850
    tone(tonePin, freq + 499);              // 6
  } else if (millis() - toneTimer >= sT + (nL * 6) + tL) { //1450
    noTone(tonePin);
  } else if (millis() - toneTimer >= sT + (nL * 6)) { //1400
    tone(tonePin, freq);                     // 5
  } else if (millis() - toneTimer >= sT + (nL * 5) + tL) { //1200
    noTone(tonePin);
  } else if (millis() - toneTimer >= sT + (nL * 5)) { //1150
    tone(tonePin, freq - 544);               // 4
  } else if (millis() - toneTimer >= sT + (nL * 3) + tL) { //750
    noTone(tonePin);
  } else if (millis() - toneTimer >= sT + (nL * 3)) { //700
    tone(tonePin, freq);                     // 3
  } else if (millis() - toneTimer >= sT + nL + tL) { //300
    noTone(tonePin);
  } else if (millis() - toneTimer >= sT + nL) { //250
    tone(tonePin, freq);                     // 2
  } else if (millis() - toneTimer >= sT + tL) { //50
    noTone(tonePin);
  } else if (millis() - toneTimer >= sT) {
    tone(tonePin, freq);                      // 1
  } else {
    noTone(tonePin);
    return false;
  }
}
