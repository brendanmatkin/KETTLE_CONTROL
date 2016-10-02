unsigned long toneTimer;
int tonePin = 6;
int freq = 2637;

void setup() {
  pinMode(tonePin, OUTPUT);
  toneTimer = millis();
  noTone(tonePin);

}



void loop() {
  marioTone(150, 100);
}

void marioTone(int nL, int tL) {
  int sT = 3000; // start time
  //int tL = 75;   // tone length
  //int nL = 120;  // note length
  if (millis() - toneTimer >= sT + (nL * 12) + tL) { //2850
    noTone(tonePin);
    toneTimer = millis();
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
  }
}
