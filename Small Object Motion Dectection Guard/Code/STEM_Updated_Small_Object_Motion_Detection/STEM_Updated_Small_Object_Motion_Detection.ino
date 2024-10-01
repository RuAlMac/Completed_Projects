int redLed1 = 6;
int redLed2 = 7;
int redLed3 = 8;
int greenLed1 = 5;
int button = 9;
int sensor = 2;

int mode = 1;
int count;
int blinkDelay;
bool sensorMode;

void setup() {
  Serial.begin(9600);

  pinMode(redLed1, OUTPUT);
  pinMode(redLed2, OUTPUT);
  pinMode(redLed3, OUTPUT);
  pinMode(greenLed3, OUTPUT);

  pinMode(button, INPUT_PULLUP);
  pinMode(sensor, INPUT);

  Serial.println("");
  Serial.println("---System Initiated---");
}

void loop() {
  if (mode == 1) { //Awaiting System Setting Mode*************************
    digitalWrite(greenLed1, HIGH);
    Serial.println("Press button to set system mode");

    while (digitalRead(button) == HIGH) {
      // Do nothing while awaiting a button press
    }

    if (digitalRead(sensor) == HIGH) { //Mode: The alarm will be set off if an object is inserted into the view of the sensor
      sensorMode = false;
      Serial.println("Alarm Mode: The alarm will be set off if an object is INSERTED into the view of the sensor");
    }

    if (digitalRead(sensor) == LOW) { //Mode: The alarm will be set off if an object is removed from the view of the sensor
      sensorMode = true;
      Serial.println("Mode: The alarm will be set off if an object is REMOVED from the view of the sensor");
    }

    while (digitalRead(button) == LOW) {
      //Do nothing until the buttun is released
    }

    Serial.println("Press button to initiate countdown");

    while (digitalRead(button) == HIGH) {
      //Do nothing while awaiting a button press
    }

    digitalWrite(greenLed1, LOW);

    mode = 2;
  }

  if (mode == 2) { //Countdown to Ready Mode*************************
    digitalWrite(greenLed2, HIGH);
    Serial.println("Countdown initiated");


    digitalWrite(redLed, HIGH);
    delay(5000);
    digitalWrite(redLed, LOW);

    digitalWrite(greenLed2, LOW);
    Serial.println("Countdown concluded");

    mode = 3;
  }

  if (mode == 3) { //Active Mode*************************
    digitalWrite(greenLed3, HIGH);
    blinkDelay = 1000;

    delay(100);

    Serial.println("Sentinel mode initiated");

    while ((sensorMode == false) && (mode == 3)) {
      if (digitalRead(sensor) == LOW) {
        digitalWrite(greenLed3, LOW);
        mode = 4;
      }
    }

    while ((sensorMode == true) && (mode == 3)) {
      if (digitalRead(sensor) == HIGH) {
        digitalWrite(greenLed3, LOW);
        mode = 4;
      }
    }

  }

  if (mode == 4) { //Alarm Activated Mode*************************
    Serial.println("Sentinal mode disengaged");
    Serial.println("Alarm triggered");

    while (mode == 4) {
      digitalWrite(redLed, HIGH);
      delay(1000);
      digitalWrite(redLed, LOW);
      delay(1000);
    }
  }
}

void countdown() {
  if (count != 0) {
    digitalWrite(redLed, HIGH);
    delay(blinkDelay);
    digitalWrite(redLed, LOW);
    delay(blinkDelay);
    count = count - 1;
  }
}
