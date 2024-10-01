//Configuration mode
void runConfig(){
  displayDistance();
  displayButtonNotPushed();

  if (digitalRead(button) == LOW){
    closedDoorDistance = distance;
    upperBound = closedDoorDistance + tolerance;
    lowerBound = closedDoorDistance - tolerance;
    mode = 2;
    lcd.clear();
    delay(10);
  }
}
