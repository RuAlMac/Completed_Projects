void ledOn() {
  digitalWrite(led, HIGH);
}

void ledOff() {
  digitalWrite(led, LOW);
}

void buzzerOn() {
  tone(buzzer, 1000);
  delay(50);
  
  noTone(buzzer);
  delay(50);
  
}

void buzzerOff() {
  noTone(buzzer);
}
