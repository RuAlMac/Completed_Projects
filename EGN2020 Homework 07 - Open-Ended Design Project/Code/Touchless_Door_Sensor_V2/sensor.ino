void getDistance() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;
}

void checkDistanceBounds(){
  if ( (distance < lowerBound) || (distance > upperBound) ){
    boundsExceeded = true;
  }
  else{
    boundsExceeded = false;
  }
}
