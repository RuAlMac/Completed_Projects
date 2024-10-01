#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//****Pin initializations****
int buzzer = 4;
int led = 9;
int button = 7;

int trigPin = 6;
int echoPin = 5;

//****Variables****
//Ultrasonic Sensor
long duration;
int distance;

//Program
int mode = 0;
bool distanceSet = false;
bool boundsExceeded = false;
int closedDoorDistance;
int upperBound;
int lowerBound;
int timeRemaining;
int index = 0;

//****Settings****
int tolerance = 20;
int countdownTime = 10; //time in seconds it takes for the alert to get set off after distance exceeds acceptable bounds

void setup() {
  //LCD Initialization
  lcd.init();
  lcd.backlight();

  //Serial monitor initialization
  Serial.begin(9600);

  //pinMode Initialziation
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  //Code to run once:
  mode = 1;
  timeRemaining = countdownTime;
}

void loop() {
  getDistance();

  if (mode == 1) {
    runConfig();
  }

  if (mode == 2) {
    runSurveillance();
  }

  if (mode == 3) {
    runCountdown();
  }

  if (mode == 4) {
    runAlert();
  }
}

void returnToConfig(){
  mode = 1;
  ledOff();
  buzzerOff();
  lcd.clear();
  timeRemaining = countdownTime;
  distanceSet = false;
  boundsExceeded = false;
  delay(100);
}

void returnToSurveillance() {
  mode = 2;
  ledOff();
  buzzerOff();
  lcd.clear();
  timeRemaining = countdownTime;
  delay(10);
}
