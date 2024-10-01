int redButton = 8;
int yellowButton = 9;
int greenButton = 10;
int whiteButton = 11;
int blackButton = 12;

int relay1 = 4;
int relay2 = 5;
int relay3 = 6;

int delayl = 450;
int delays = 100;
int delayw = 700;

bool toggleValues[3] = {false, false, false}; //array length of three; RED, YELLOW, GREEN
int mode = 1;

void setup() {
  Serial.begin(9600);

  pinMode(redButton, INPUT_PULLUP);
  pinMode(yellowButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(whiteButton, INPUT_PULLUP);
  pinMode(blackButton, INPUT_PULLUP);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);

  turnOffLights();
  mode = 1;
}

void loop() {

  if (mode == 1) { //Standard Mode: Turn on specific lights by pressing the corresponding color-coded button
    if (digitalRead(redButton) == LOW) {
      toggleValues[0] = false;
      toggleValues[1] = false;
      toggleValues[2] = true;
    }

    if (digitalRead(yellowButton) == LOW) {
      toggleValues[0] = false;
      toggleValues[1] = true;
      toggleValues[2] = false;
    }

    if (digitalRead(greenButton) == LOW) {
      toggleValues[0] = true;
      toggleValues[1] = false;
      toggleValues[2] = false;
    }

    toggleLights();
  }

  if (mode == 2) { //Flash Mode: All lights flash simultaneously
    turnOffLights();

    delay(500);

    toggleValues[0] = true;
    toggleValues[1] = true;
    toggleValues[2] = true;
    toggleLights();

    delay(500);
  }

  if (mode == 3) { //Point Mode: Each light turns off and on in sequence to utilize phi phenomenon to present a "shooting upward" motion

    toggleValues[0] = true;
    toggleValues[1] = false;
    toggleValues[2] = false;
    toggleLights();

    delay(250);

    toggleValues[0] = false;
    toggleValues[1] = true;
    toggleValues[2] = false;
    toggleLights();

    delay(250);

    toggleValues[0] = false;
    toggleValues[1] = false;
    toggleValues[2] = true;
    toggleLights();

    delay(250);
  }

  if (mode == 4) { //"Dennis Hunt" in International Morse Code: -.. . -. -. .. ... / .... ..- -. -
    turnOffLights();

    toggleValues[0] = true; //long D
    toggleLights();
    delay(delayl);
    turnOffLights();

    toggleValues[1] = true; //short
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[1] = true; //short
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[1] = true; //short E
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[0] = true; //long N
    toggleLights();
    delay(delayl);
    turnOffLights();

    toggleValues[1] = true; //short
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[0] = true; //long N
    toggleLights();
    delay(delayl);
    turnOffLights();

    toggleValues[1] = true; //short N
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[1] = true; //short I
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[1] = true; //short
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[1] = true; //short S
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[1] = true; //short
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[1] = true; //short
    toggleLights();
    delay(delays);
    turnOffLights();

    delay(delayw); //Pause between "Dennis" and "Hunt" -.. . -. -. .. ... / .... ..- -. -

    if (digitalRead(blackButton) == LOW) {
      turnOffLights();
      mode = 1;
    }

    toggleValues[1] = true; //short D
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[1] = true; //short
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[1] = true; //short
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[1] = true; //short
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[1] = true; //short U
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[1] = true; //short
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[0] = true; //long
    toggleLights();
    delay(delayl);
    turnOffLights();

    toggleValues[0] = true; //long N
    toggleLights();
    delay(delayl);
    turnOffLights();

    toggleValues[1] = true; //short
    toggleLights();
    delay(delays);
    turnOffLights();

    toggleValues[0] = true; //long T
    toggleLights();
    delay(delayl);
    turnOffLights();

    delay(2000);

    if (digitalRead(blackButton) == LOW) {
      turnOffLights();
      mode = 1;
    }
  }

  if (digitalRead(whiteButton) == LOW) {
    turnOffLights();

    mode = mode + 1;


    if (mode > 4) {
      mode = 1;
    }
    delay(500);
  }

  if (digitalRead(blackButton) == LOW) {
    turnOffLights();
    mode = 1;
  }

  Serial.println(mode);
}

void turnOffLights() {
  toggleValues[0] = false;
  toggleValues[1] = false;
  toggleValues[2] = false;
  toggleLights();
}

void turnOnLights() {
  toggleValues[0] = true;
  toggleValues[1] = true;
  toggleValues[2] = true;
  toggleLights();
}

void toggleLights() {
  if (toggleValues[0] == true) {
    digitalWrite(relay1, LOW);
  }
  else {
    digitalWrite(relay1, HIGH);
  }

  if (toggleValues[1] == true) {
    digitalWrite(relay2, LOW);
  }
  else {
    digitalWrite(relay2, HIGH);
  }

  if (toggleValues[2] == true) {
    digitalWrite(relay3, LOW);
  }
  else {
    digitalWrite(relay3, HIGH);
  }
}
