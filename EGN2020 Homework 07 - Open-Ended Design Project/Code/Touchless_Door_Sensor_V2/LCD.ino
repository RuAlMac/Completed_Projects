void displayDistance(){
  lcd.home();
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print("   ");
  delay(500);
}

void displayButtonNotPushed(){
  lcd.setCursor(0,1);
  lcd.print("distance not set");
}

void displaySurveillanceScreen(){
  lcd.setCursor(0,1);
  lcd.print("Set, monitoring ");
}

void displayCountdownScreen(){
  lcd.setCursor(11,1);
  lcd.print("    ");
  delay(50);
  lcd.setCursor(0,1);
  lcd.print("Countdown: ");
  lcd.print(timeRemaining);
  Serial.print("Countdown: ");
  Serial.print(timeRemaining);
  Serial.print("\n");
}

void displayAlertScreen(){
  lcd.setCursor(0,1);
  lcd.print("Close door");
}
