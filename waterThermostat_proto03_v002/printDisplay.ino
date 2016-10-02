// Brendan Matkin June 2015
// 2 digit 7 segment display on a 74hc164
// 7 second delay per segment provides best contrast without flicker. 
// LTD-2601G (very small common anode, green)


byte num[] = {
  B00010001, B11011011, B00100011, B10000011, B11001001, 
  B10000101, B00001101, B11010011, B00000001, B11000001  
};

void printDisplay(int _in) {
  int d1 = (_in/10)%10;
  int d2 = _in%10;
  digitalWrite(dig1, LOW);
  digitalWrite(clk, LOW);
  shiftOut(data, clk, LSBFIRST, num[d1]);
  delay(7);
  digitalWrite(dig1, HIGH);
  
  digitalWrite(dig2, LOW);
  digitalWrite(clk, LOW);
  shiftOut(data, clk, LSBFIRST, num[d2]);
  delay(7);
  digitalWrite(dig2, HIGH);
}
