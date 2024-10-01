//Countdown
void runCountdown() {

  ledOn();
  displayDistance();
  displayCountdownScreen();
  checkDistanceBounds();

  if (boundsExceeded == true) {
    if (timeRemaining == 0) {
      mode = 4;
      lcd.clear();
      delay(10);
    }

    if (timeRemaining != 0) {
      timeRemaining = timeRemaining - 1;
      delay(1000);
    }
  }

  if (boundsExceeded == false) {
    returnToSurveillance();
  }

  if (digitalRead(button) == LOW){
    returnToConfig();
  }
}
