#define data 3
#define clk 4
#define dig1 5
#define dig2 6

int val;
unsigned long timer;
unsigned long del = 500;


void setup() {
  Serial.begin(9600);
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);
  
  pinMode(dig1, OUTPUT);
  pinMode(dig2, OUTPUT);
  digitalWrite(dig1, LOW);
  digitalWrite(dig2, HIGH);
  timer = millis();
}

void loop() {
  //int aa = analogRead(0)/4;
  //Serial.println(aa);
//  Serial.print(d1);
//  Serial.print(" ");
//  Serial.println(d2);
  
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
