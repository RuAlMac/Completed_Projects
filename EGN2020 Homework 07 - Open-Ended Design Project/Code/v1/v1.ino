#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Pin initializations
int trigPin = 6;
int echoPin = 5;
int piezo = 4;
int led = 9;
int button = 7;

//Variables
long duration;
int distance;
bool distanceSet = false;
bool doorOpen = false;
int closedDoorDistance;
int upperBound;
int lowerBound;

//Settings
int tolerance = 30;

void setup() {
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(piezo, ); //???????????????
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  Serial.begin(9600);

  //Code to run once:
  updateLcd();
}


void loop() {
  getdistance();

  setClosedDoorDistance();
  compareSetDistance();
  updateLcd();

}


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

void setClosedDoorDistance() {
  if (digitalRead(button) == LOW) {
    distanceSet = true;
    closedDoorDistance = distance;

    upperBound = closedDoorDistance + tolerance;
    lowerBound = closedDoorDistance - tolerance;
  }
}

void compareSetDistance() {
  if ( (distance < lowerBound) || (distance > upperBound) ) {
    //trigger alarm
  }
  else {
    //do nothing
  }
}

void doorOpenProcedure() {
  //countdown
  //alarm
  //press button to reset alarm, or press and hold button to reset entire system (set distance and alarm)
}

void updateLcd() {
  if (doorOpen == false) {
    printDistance();
  }

  if (doorOpen == true) {
    printDistance();
  }

  if (distanceSet == false) {
    lcd.setCursor(0, 1);
    lcd.print("prss to cnfrm clsd  ")
  }

  if (distanceSet == true) {
    lcd.setCursor(0, 1);
    lcd.print("set, monitoring...  ")
  }
}


void printDistance() {
  lcd.home();
  lcd.print("Distance:           ");

  lcd.setCursor(11);
  lcd.print(distance);
}
