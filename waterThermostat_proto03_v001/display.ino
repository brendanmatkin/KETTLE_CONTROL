void ledDisplay(int time) {
  digitalWrite(digit_1, HIGH); 
  shiftOut(dispData, dispClock, LSBFIRST, numbers[dig_1]);
  delay(time);
  digitalWrite(digit_1, LOW);

  digitalWrite(digit_2, HIGH);
  shiftOut(dispData, dispClock, LSBFIRST, numbers[dig_2]);
  delay(time);
  digitalWrite(digit_2, LOW);
}
