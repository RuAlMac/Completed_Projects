#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //0x27 is the i2c address, while 16 = columns, and 2 = rows.

int sensor = 7;

int systemSwitch = 2;
int transistor = 5;

int S; //count seconds
int M; // count minutes
int H; // count hours

bool active = false;

void setup()
{

  pinMode(systemSwitch, INPUT_PULLUP);
  pinMode(sensor, INPUT);
  pinMode(transistor, OUTPUT);
  pinMode(13, OUTPUT);

  Serial.begin(9600);

  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight

  lcd.setCursor(0, 0);
  lcd.print ("---- || Sys: ---");
  lcd.setCursor(0, 1);
  lcd.print ("Cntdwn:   :  :  ");
}
//********************************************************
void loop() {
  if (digitalRead(systemSwitch) == HIGH) {
    lcd.setCursor(13, 0);
    lcd.print ("OFF");
    resetTimer();
    lcd.noBacklight();
  }
  else {
    lcd.setCursor(13, 0);
    lcd.print ("ON ");
    lcd.backlight();
  }

  if (digitalRead(sensor) == HIGH) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }


  if (digitalRead(sensor) == LOW) { //If sensor detects that the door is open, these statements execute
    active = true;
    lcd.setCursor(0, 0);
    lcd.print ("OPEN");
  }

  if ((S == 0 && M == 0 && H == 0) && digitalRead(sensor) == LOW) { //If sensor does not detect door, it outputs HIGH
    resetTimer();
    if (digitalRead(systemSwitch) == LOW) {
      digitalWrite(transistor, HIGH);
      delay(250);
      digitalWrite(transistor, LOW);
    }
  }

  if (digitalRead(sensor) == HIGH) { //If sensor does not detect door, it outputs HIGH
    resetTimer();
    lcd.setCursor(0, 0);
    lcd.print ("CLSD");
  }

  if (active == true && digitalRead(systemSwitch) == LOW) {
    S--;
  }

  delay(1000);
  runTimer();
}

void resetTimer() {
  active = false;

  S = 00;
  M = 05;
  H = 00;
}

void runTimer() {

  if (active == true) { //Really, the statements of this if statement are unnecessary for this project
    if (S < 0)
    {
      M--;
      S = 59;
    }
    if (M < 0)
    {
      H--;
      M = 59;
    }
  }

  if (H < 0) {
    H = 23;
    M = 59;
    S = 59;
  }

  if (M > 9)
  {
    lcd.setCursor(11, 1);
    lcd.print(M);
  }
  else
  {
    lcd.setCursor(11, 1);
    lcd.print("0");
    lcd.setCursor(12, 1);
    lcd.print(M);
    lcd.setCursor(13, 1);
    lcd.print(":");
  }

  if (S > 9)
  {
    lcd.setCursor(14, 1);
    lcd.print(S);
  }
  else
  {
    lcd.setCursor(14, 1);
    lcd.print("0");
    lcd.setCursor(15, 1);
    lcd.print(S);
    lcd.setCursor(16, 1);
    lcd.print(" ");
  }

  if (H > 9)
  {
    lcd.setCursor(8, 1);
    lcd.print (H);
  }
  else
  {
    lcd.setCursor(8, 1);
    lcd.print("0");
    lcd.setCursor(9, 1);
    lcd.print(H);
    lcd.setCursor(10, 1);
    lcd.print(":");
  }
}
