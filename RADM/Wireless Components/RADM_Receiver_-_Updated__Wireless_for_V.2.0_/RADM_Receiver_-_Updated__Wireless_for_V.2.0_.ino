//Wire Connections: Red(3.3 V), Black(Gnd), Yellow(Digital 8), Orange(Digital 9), Green(Digital 52), Blue(Digital50), Purple(Digital51)

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <SPI.h> //2.0 Additions (Libraries)
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8);

int yellowLamp1 = 30;
int yellowLamp2 = 31;

//V 2.0 Updates :: Wireless Capability Variables ********
int dStatus[2];

bool d1Bool; //FALSE = OPEN, TRUE = CLOSED
bool d2Bool;
bool d1StatusSent = true;
bool d2StatusSent = false;

const byte address[6] = "RADM1";
//********

void(* resetFunc) (void) = 0;

void setup() {

  //Pin Mode Settings

  pinMode(yellowLamp1, OUTPUT);
  pinMode(yellowLamp2, OUTPUT);

  //LCD Initialization
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight
  lcd.noCursor();
  lcd.noBlink();

  lcd.setCursor ( 0, 0 );            // go to the top left corner
  lcd.print("RADM | V1.4 | ONLINE"); //"ONLINE" changed from "ACTIVE"
  lcd.setCursor ( 0, 1 );            // go to the 2nd row
  lcd.print("D1: ERRR || D2: ERRR");
  lcd.setCursor ( 0, 2 );            // go to the third row
  lcd.print("   SEC KEY: ERROR   ");
  lcd.setCursor ( 0, 3 );            // go to the fourth row
  lcd.print(" STATUS: NOT READY  ");

  //V.2.0 Updates ********
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN); //MIN, LOW, or HIGH
  radio.startListening(); //RECEIVER
  //********
}

void loop() {

  if (radio.available() && d1StatusSent == false && d2StatusSent == true) {

    radio.read(&dStatus[0], sizeof(dStatus[0]));
    delay(20);

    if (dStatus[0] == 1) { //CLOSED = TRUE
      d1Bool = true;
      Serial.println("Door 1 Closed");
      digitalWrite(yellowLamp1, HIGH);
      delay(20);
    }

    if (dStatus[0] == 2) { //OPEN = FALSE
      d1Bool = false;
      Serial.println("Door 1 Open");
      digitalWrite(yellowLamp1, LOW);
      delay(20);
    }
    delay(20);

    d1StatusSent = true;
    d2StatusSent = false;
  }
  delay(250);

  if (radio.available() && d1StatusSent == true && d2StatusSent == false) {
    //if (d1StatusSent == true){
    radio.read(&dStatus[1], sizeof(dStatus[1]));
    delay(20);

    if (dStatus[1] == 1) { //CLOSED = TRUE
      d2Bool = true;
      Serial.println("Door 2 Closed");
      digitalWrite(yellowLamp2, HIGH);
      delay(20);
    }

    if (dStatus[1] == 2) { //OPEN = FALSE
      d1Bool = false;
      Serial.println("Door 2 Open");
      digitalWrite(yellowLamp2, LOW);
      delay(20);
    }
    delay(20);
    d1StatusSent = false;
    d2StatusSent = true;
    delay(250);
  }

/*
  if (d1Bool == true) {
    digitalWrite(yellowLamp1, HIGH);
  }
  else if (d1Bool == false) {
    digitalWrite(yellowLamp1, LOW);
  }

  if (d2Bool == true) {
    digitalWrite(yellowLamp2, HIGH);
  }
  else if (d2Bool == false) {
    digitalWrite(yellowLamp2, LOW);
  }
  */
}
