boolean marioTone(int nL, int tL) {
  int freq = 2637; // an E
  int sT = nL*15;  // restart time
  //int tL = 75;   // tone length
  //int nL = 120;  // note length
  int bT = 400;    // buffer time
  
  if (millis() - toneTimer >= (nL * 12) + tL + sT) {
    toneTimer = millis();
    noTone(tonePin);
    return false;
  } else if (millis() - toneTimer >= (nL*12) + tL + bT + 100) {
    return false;
  } else if (millis() - toneTimer >= (nL * 12) + tL + bT) { //2850
    noTone(tonePin);
    //toneTimer = millis();
    //return true;
  } else if (millis() - toneTimer >= (nL * 12) + bT) { //2800
    tone(tonePin, freq - 1050);              // 7
  } else if (millis() - toneTimer >= (nL * 8) + tL + bT) { //1900
    noTone(tonePin);
  } else if (millis() - toneTimer >= (nL * 8) + bT) { //1850
    tone(tonePin, freq + 499);              // 6
  } else if (millis() - toneTimer >= (nL * 6) + tL + bT) { //1450
    noTone(tonePin);
  } else if (millis() - toneTimer >= (nL * 6) + bT) { //1400
    tone(tonePin, freq);                     // 5
  } else if (millis() - toneTimer >= (nL * 5) + tL + bT) { //1200
    noTone(tonePin);
  } else if (millis() - toneTimer >= (nL * 5) + bT) { //1150
    tone(tonePin, freq - 544);               // 4
  } else if (millis() - toneTimer >= (nL * 3) + tL + bT) { //750
    noTone(tonePin);
  } else if (millis() - toneTimer >= (nL * 3) + bT) { //700
    tone(tonePin, freq);                     // 3
  } else if (millis() - toneTimer >= nL + tL + bT) { //300
    noTone(tonePin);
  } else if (millis() - toneTimer >= nL + bT) { //250
    tone(tonePin, freq);                     // 2
  } else if (millis() - toneTimer >= tL + bT) { //50
    noTone(tonePin);
  } else if (millis() - toneTimer >= 0 + bT) {
    tone(tonePin, freq);                      // 1
    return true;
  } else {
  //  noTone(tonePin);
//    return false;
  }
}
