unsigned long timer;
int tonePin = 6;
int freq = 2637;

void setup() {
  pinMode(tonePin, OUTPUT);
  timer = millis();
  noTone(tonePin);

}


int sT = 3000; // start time
int tL = 100;   // tone length
int nL = 200;  // note length
void loop() {
  if (millis() - timer >= sT+2800+tL) {//2850
    noTone(tonePin);
    timer = millis();
  } else if (millis() - timer >= sT+2800) {//2800
    tone(tonePin, freq-1050);                // 7
  } else if (millis() - timer >= sT+1850+tL) {//1900
    noTone(tonePin);
  } else if (millis() - timer >= sT+1850) {//1850
    tone(tonePin, freq+499);                // 6
  } else if (millis() - timer >= sT+1400+tL) {//1450
    noTone(tonePin);
  } else if (millis() - timer >= sT+1400) {//1400
    tone(tonePin, freq);                     // 5
  } else if (millis() - timer >= sT+1150+tL) {//1200
    noTone(tonePin);
  } else if (millis() - timer >= sT+1150) {//1150
    tone(tonePin, freq-544);                 // 4
  } else if (millis() - timer >= sT+700+tL) {//750
    noTone(tonePin);
  } else if (millis() - timer >= sT+700) {//700
    tone(tonePin, freq);                     // 3
  } else if (millis() - timer >= sT+250+tL) {//300
    noTone(tonePin);
  } else if (millis() - timer >= sT+250) {//250
    tone(tonePin, freq);                     // 2
  } else if (millis() - timer >= sT+tL) {//50
    noTone(tonePin);
  } else if (millis() - timer >= sT) {
    tone(tonePin, freq);                      // 1
  } else {
    noTone(tonePin);
  }
}
