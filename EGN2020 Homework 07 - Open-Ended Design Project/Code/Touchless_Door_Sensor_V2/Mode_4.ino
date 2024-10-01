//Alert
void runAlert() {
  buzzerOn();
  displayDistance();
  displayAlertScreen();
  checkDistanceBounds();

  if (boundsExceeded == false) {
    returnToSurveillance();
  }

  if (digitalRead(button) == LOW) {
    returnToConfig();
  }
}
