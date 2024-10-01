//Surveillance
void runSurveillance() {
  
  displayDistance();
  displaySurveillanceScreen();
  checkDistanceBounds();

  if (boundsExceeded == true) {
    mode = 3;
    lcd.clear();
    delay(10);
  }

  if (digitalRead(button) == LOW){
    returnToConfig();
  }
}
