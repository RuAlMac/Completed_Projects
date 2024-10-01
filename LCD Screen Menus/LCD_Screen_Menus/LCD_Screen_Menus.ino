#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);


//Components:
int button1 = 10;
int button2 = 8;
int button3 = 7;
int button4 = 6;

int redLed = 4;
int greenLed = 3;
int blueLed = 2;
//*****************


//Variables:
int activePage = 1;
bool redLedStatus = false;
bool greenLedStatus = false;
bool blueLedStatus = false;
//*****************

void setup() {
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  updateScreen();
}

void loop() {
  if (digitalRead(button1) == LOW) {
    activePage = activePage - 1;
    while (digitalRead(button1) == LOW) {
      //do nothing
    }
    updateScreen();
  }

  if (digitalRead(button2) == LOW) {
    activePage = activePage + 1;
    while (digitalRead(button2) == LOW) {
      //do nothing
    }
    updateScreen();
  }

  if (digitalRead(button3) == LOW) {
    if (activePage == 1) {
      redLedStatus = !redLedStatus;
    }
    if (activePage == 2) {
      greenLedStatus = !greenLedStatus;
    }
    if (activePage == 3) {
      blueLedStatus = !blueLedStatus;
    }
    while(digitalRead(button3) == LOW){
      //do nothing
    }

    updateScreen();
  }
}

void updateScreen() {
  lcd.clear();
  
  if (activePage == 0) {
    activePage = 4;
  }

  if (activePage == 5) {
    activePage = 1;
  }

  if (activePage == 1) {
    screen1();
  }

  if (activePage == 2) {
    screen2();
  }

  if (activePage == 3) {
    screen3();
  }

  if (activePage == 4) {
    screen4();
  }
}

void screen1() {
  lcd.setCursor(0, 0);
  lcd.print("Red LED Settings");

  lcd.setCursor(0, 1);
  if (redLedStatus == false) {
    lcd.print("Off");
    digitalWrite(redLed, LOW);
  }
  else {
    lcd.print("On ");
    digitalWrite(redLed, HIGH);
  }

  lcd.setCursor(0, 2);
  lcd.print("Button 3 to Change");
}

void screen2() {
  lcd.setCursor(0, 0);
  lcd.print("Green LED Settings");

  lcd.setCursor(0, 1);
  if (greenLedStatus == false) {
    lcd.print("Off");
    digitalWrite(greenLed, LOW);
  }
  else {
    lcd.print("On ");
    digitalWrite(greenLed, HIGH);
  }

  lcd.setCursor(0, 2);
  lcd.print("Button 3 to Change");
}

void screen3() {
  lcd.setCursor(0, 0);
  lcd.print("Blue LED Settings");

  lcd.setCursor(0, 1);
  if (blueLedStatus == false) {
    lcd.print("Off");
    digitalWrite(blueLed, LOW);
  }
  else {
    lcd.print("On ");
    digitalWrite(blueLed, HIGH);
  }

  lcd.setCursor(0, 2);
  lcd.print("Button 3 to Change");
}

void screen4() {
  lcd.setCursor(0, 0);
  lcd.print("Screen 4");
}
