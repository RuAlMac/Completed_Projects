//Room Automated Defense Manager (RADM) | Source Code | Version 1.4 Revised | Russell A.D. MacGregor | 12/22/2020-12/24/2020
/*********************************************************************************************************************************************************************/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

int door1 = 32; //32
int door2 = 33; //33
int redLamp = 28; //28
int whiteLamp = 29; //MEGA: 29, UNO: 6
int yellowLamp1 = 30;
int yellowLamp2 = 31;
int redButtonLed = 38; //38
int greenButtonLed = 40;
int blueButtonLed = 42;
int redButton = 44; //44
int greenButton = 46; //46
int blueButton = 48;
int securityKey = 37; //37
int redLed = 34; //34
int greenLed = 35; //35
int blueLed = 36; //36
int siren = 39;

//const int buzzer = 3; >> ALL REFERENCES REMOVED FROM CODE

void(* resetFunc) (void) = 0;

void setup() {

  //Pin Mode Settings
  pinMode(door1, INPUT_PULLUP);
  pinMode(door2, INPUT_PULLUP);
  pinMode(redLamp, OUTPUT);
  pinMode(whiteLamp, OUTPUT);
  pinMode(yellowLamp1, OUTPUT);
  pinMode(yellowLamp2, OUTPUT);
  pinMode(redButtonLed, OUTPUT);
  pinMode(greenButtonLed, OUTPUT);
  pinMode(blueButtonLed, OUTPUT);
  pinMode(redButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);
  pinMode(securityKey, INPUT_PULLUP);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(siren, OUTPUT);

  //pinMode(buzzer, OUTPUT);

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

  digitalWrite(redLamp, LOW);
}

void loop() {
  //Security Key LCD Status Setting

  if (digitalRead(securityKey) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 2 );            // go to the third row
    lcd.print("  SEC KEY: ACTIVE   ");
  }
  else if (digitalRead(securityKey) == HIGH && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 2 );            // go to the third row
    lcd.print(" SEC KEY: INACTIVE  ");
  }

  //Door LCD Status Settings

  if (digitalRead(door1) == LOW) {
    lcd.setCursor ( 4, 1 );
    lcd.print("CLSD");
  }
  else if (digitalRead(door1) == HIGH) {
    lcd.setCursor ( 4, 1 );
    lcd.print("OPEN");
  }
  if (digitalRead(door2) == LOW) {
    lcd.setCursor ( 16, 1 );
    lcd.print("CLSD");
  }
  else if (digitalRead(door2) == HIGH) {
    lcd.setCursor ( 16, 1 );
    lcd.print("OPEN");
  }

  //Lamp Function Assignments

  if (digitalRead(greenButton) == LOW) { //if green button is ACTIVATED > more effective/optimal method for implemting this possible?

    lcd.backlight(); //<<< REACTIVATE BEFORE FINAL IMPLEMENTATION

    if (digitalRead(door1) == LOW) { //If door is CLOSED, lamp is ON
      digitalWrite(yellowLamp1, HIGH);
    }
    else if (digitalRead(door1) == HIGH) {
      digitalWrite(yellowLamp1, LOW);
    }

    if (digitalRead(door2) == LOW) {
      digitalWrite(yellowLamp2, HIGH);
    }
    else if (digitalRead(door2) == HIGH) {
      digitalWrite(yellowLamp2, LOW);
    }

    if (digitalRead(securityKey) == LOW) {
      digitalWrite(whiteLamp, HIGH);
    }
    else if (digitalRead(securityKey) == HIGH) {
      digitalWrite(whiteLamp, LOW);
    }

    //Preliminary Button LED Activation Settings (Excepting Red)

    if (digitalRead(greenButton) == LOW) {
      digitalWrite(greenButtonLed, HIGH);
    }
    else if (digitalRead(greenButton) == HIGH) {
      digitalWrite(greenButtonLed, LOW);
    }

    if (digitalRead(blueButton) == LOW) { //BLUE BUTTON NOT IN USE
      digitalWrite(blueButtonLed, HIGH);
    }
    else if (digitalRead(blueButton) == HIGH) {
      digitalWrite(blueButtonLed, LOW);
    }
  }

  if (digitalRead(greenButton) == HIGH) { //if green button is DEACTIVATED

    digitalWrite(yellowLamp1, LOW);
    digitalWrite(yellowLamp2, LOW);
    digitalWrite(whiteLamp, LOW);
    digitalWrite(redLamp, LOW);
    digitalWrite(redButtonLed, LOW);
    digitalWrite(greenButtonLed, LOW);
    digitalWrite(blueButtonLed, LOW);
    lcd.noBacklight(); // <<< REACTIVATE BEFORE FINAL IMPLEMENTATION
  }

  //Alarm Stage 1: "Not Ready"
  //Default Stage established during program initialization

  //Alarm Stage 2: "Ready"

  //If user attempts to activate alarm without inserting security key first
  if (digitalRead(door1) == LOW && digitalRead(door2) == LOW && digitalRead(securityKey) == HIGH && digitalRead(redButton) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: ACTIVATE KEY");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: ACTIVATE KEY");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: ACTIVATE KEY");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: NOT READY  ");
  }

  //If user attempts to activate alarm without closing Door 1 first
  if (digitalRead(door1) == LOW && digitalRead(door2) == HIGH && digitalRead(securityKey) == LOW && digitalRead(redButton) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: CLOSE DOOR 1");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: CLOSE DOOR 1");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: CLOSE DOOR 1");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: CLOSE DOOR 1");
  }

  //If user attempts to activate alarm without closing Door 2 first
  if (digitalRead(door1) == HIGH && digitalRead(door2) == LOW && digitalRead(securityKey) == LOW && digitalRead(redButton) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: CLOSE DOOR 2");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: CLOSE DOOR 2");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: CLOSE DOOR 2");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: CLOSE DOOR 2");
  }

  //If user attempts to activate alarm without closing both doors or activating security key first
  if (digitalRead(door1) == HIGH && digitalRead(door2) == HIGH && digitalRead(securityKey) == HIGH && digitalRead(redButton) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOORS AND KEY  ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOORS AND KEY  ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOORS AND KEY  ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: NOT READY  ");
  }

  //If user attempts to activate alarm without closing Door 1 or activating security key first
  if (digitalRead(door1) == HIGH && digitalRead(door2) == LOW && digitalRead(securityKey) == HIGH && digitalRead(redButton) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOOR 1 AND KEY ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOOR 1 AND KEY ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOOR 1 AND KEY ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: NOT READY  ");
  }

  //If user attempts to activate alarm without closing Door 1 or activating security key first
  if (digitalRead(door1) == LOW && digitalRead(door2) == HIGH && digitalRead(securityKey) == HIGH && digitalRead(redButton) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOOR 2 AND KEY ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOOR 2 AND KEY ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOOR 2 AND KEY ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: NOT READY  ");
  }

  //If user attempts to activate alarm without closing Door 1 or Door 2, Security Key active
  if (digitalRead(door1) == HIGH && digitalRead(door2) == HIGH && digitalRead(securityKey) == LOW && digitalRead(redButton) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print("!!> CLOSE DOORS 1+2 ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("!!> CLOSE DOORS 1+2 ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("!!> CLOSE DOORS 1+2 ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: NOT READY  ");
  }

  if (digitalRead(door1) == LOW && digitalRead(door2) == LOW && digitalRead(securityKey) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print("   STATUS: READY    ");
  }
  else if (digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: NOT READY  ");
  }

  if (digitalRead(door1) == LOW && digitalRead(door2) == LOW && digitalRead(securityKey) == LOW && digitalRead(redButton) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: ACTIVE IN 10");
    digitalWrite(redButtonLed, HIGH);

    //******** | IF Statements to update indicators during countdown
    if (digitalRead(securityKey) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(whiteLamp, HIGH);
    }
    else if (digitalRead(securityKey) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(whiteLamp, LOW);
    }

    if (digitalRead(door1) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp1, HIGH);
    }
    else if (digitalRead(door1) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp1, LOW);
    }

    if (digitalRead(door2) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp2, HIGH);
    }
    else if (digitalRead(door2) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp2, LOW);
    }

    if (digitalRead(greenButton) == LOW) {
      digitalWrite(greenButtonLed, HIGH);
    }
    else if (digitalRead(greenButton) == HIGH) {
      digitalWrite(greenButtonLed, LOW);
    }
    //********

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("09");
    digitalWrite(redButtonLed, LOW);

    //******** | IF Statements to update indicators during countdown
    if (digitalRead(securityKey) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(whiteLamp, HIGH);
    }
    else if (digitalRead(securityKey) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(whiteLamp, LOW);
    }

    if (digitalRead(door1) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp1, HIGH);
    }
    else if (digitalRead(door1) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp1, LOW);
    }

    if (digitalRead(door2) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp2, HIGH);
    }
    else if (digitalRead(door2) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp2, LOW);
    }

    if (digitalRead(greenButton) == LOW) {
      digitalWrite(greenButtonLed, HIGH);
    }
    else if (digitalRead(greenButton) == HIGH) {
      digitalWrite(greenButtonLed, LOW);
    }
    //********

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("08");
    digitalWrite(redButtonLed, HIGH);

    //******** | IF Statements to update indicators during countdown
    if (digitalRead(securityKey) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(whiteLamp, HIGH);
    }
    else if (digitalRead(securityKey) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(whiteLamp, LOW);
    }

    if (digitalRead(door1) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp1, HIGH);
    }
    else if (digitalRead(door1) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp1, LOW);
    }

    if (digitalRead(door2) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp2, HIGH);
    }
    else if (digitalRead(door2) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp2, LOW);
    }

    if (digitalRead(greenButton) == LOW) {
      digitalWrite(greenButtonLed, HIGH);
    }
    else if (digitalRead(greenButton) == HIGH) {
      digitalWrite(greenButtonLed, LOW);
    }
    //********

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("07");
    digitalWrite(redButtonLed, LOW);

    //******** | IF Statements to update indicators during countdown
    if (digitalRead(securityKey) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(whiteLamp, HIGH);
    }
    else if (digitalRead(securityKey) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(whiteLamp, LOW);
    }

    if (digitalRead(door1) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp1, HIGH);
    }
    else if (digitalRead(door1) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp1, LOW);
    }

    if (digitalRead(door2) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp2, HIGH);
    }
    else if (digitalRead(door2) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp2, LOW);
    }

    if (digitalRead(greenButton) == LOW) {
      digitalWrite(greenButtonLed, HIGH);
    }
    else if (digitalRead(greenButton) == HIGH) {
      digitalWrite(greenButtonLed, LOW);
    }
    //********

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("06");
    digitalWrite(redButtonLed, HIGH);

    //******** | IF Statements to update indicators during countdown
    if (digitalRead(securityKey) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(whiteLamp, HIGH);
    }
    else if (digitalRead(securityKey) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(whiteLamp, LOW);
    }

    if (digitalRead(door1) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp1, HIGH);
    }
    else if (digitalRead(door1) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp1, LOW);
    }

    if (digitalRead(door2) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp2, HIGH);
    }
    else if (digitalRead(door2) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp2, LOW);
    }

    if (digitalRead(greenButton) == LOW) {
      digitalWrite(greenButtonLed, HIGH);
    }
    else if (digitalRead(greenButton) == HIGH) {
      digitalWrite(greenButtonLed, LOW);
    }
    //********

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("05");
    digitalWrite(redButtonLed, LOW);

    //******** | IF Statements to update indicators during countdown
    if (digitalRead(securityKey) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(whiteLamp, HIGH);
    }
    else if (digitalRead(securityKey) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(whiteLamp, LOW);
    }

    if (digitalRead(door1) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp1, HIGH);
    }
    else if (digitalRead(door1) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp1, LOW);
    }

    if (digitalRead(door2) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp2, HIGH);
    }
    else if (digitalRead(door2) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp2, LOW);
    }

    if (digitalRead(greenButton) == LOW) {
      digitalWrite(greenButtonLed, HIGH);
    }
    else if (digitalRead(greenButton) == HIGH) {
      digitalWrite(greenButtonLed, LOW);
    }
    //********

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("04");
    digitalWrite(redButtonLed, HIGH);

    //******** | IF Statements to update indicators during countdown
    if (digitalRead(securityKey) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(whiteLamp, HIGH);
    }
    else if (digitalRead(securityKey) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(whiteLamp, LOW);
    }

    if (digitalRead(door1) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp1, HIGH);
    }
    else if (digitalRead(door1) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp1, LOW);
    }

    if (digitalRead(door2) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp2, HIGH);
    }
    else if (digitalRead(door2) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp2, LOW);
    }

    if (digitalRead(greenButton) == LOW) {
      digitalWrite(greenButtonLed, HIGH);
    }
    else if (digitalRead(greenButton) == HIGH) {
      digitalWrite(greenButtonLed, LOW);
    }
    //********

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("03");
    digitalWrite(redButtonLed, LOW);

    //******** | IF Statements to update indicators during countdown
    if (digitalRead(securityKey) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(whiteLamp, HIGH);
    }
    else if (digitalRead(securityKey) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(whiteLamp, LOW);
    }

    if (digitalRead(door1) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp1, HIGH);
    }
    else if (digitalRead(door1) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp1, LOW);
    }

    if (digitalRead(door2) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp2, HIGH);
    }
    else if (digitalRead(door2) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp2, LOW);
    }

    if (digitalRead(greenButton) == LOW) {
      digitalWrite(greenButtonLed, HIGH);
    }
    else if (digitalRead(greenButton) == HIGH) {
      digitalWrite(greenButtonLed, LOW);
    }
    //********

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("02");
    digitalWrite(redButtonLed, HIGH);

    //******** | IF Statements to update indicators during countdown
    if (digitalRead(securityKey) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(whiteLamp, HIGH);
    }
    else if (digitalRead(securityKey) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(whiteLamp, LOW);
    }

    if (digitalRead(door1) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp1, HIGH);
    }
    else if (digitalRead(door1) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp1, LOW);
    }

    if (digitalRead(door2) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp2, HIGH);
    }
    else if (digitalRead(door2) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp2, LOW);
    }

    if (digitalRead(greenButton) == LOW) {
      digitalWrite(greenButtonLed, HIGH);
    }
    else if (digitalRead(greenButton) == HIGH) {
      digitalWrite(greenButtonLed, LOW);
    }
    //********

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("01");
    digitalWrite(redButtonLed, LOW);

    //******** | IF Statements to update indicators during countdown
    if (digitalRead(securityKey) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(whiteLamp, HIGH);
    }
    else if (digitalRead(securityKey) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(whiteLamp, LOW);
    }

    if (digitalRead(door1) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp1, HIGH);
    }
    else if (digitalRead(door1) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp1, LOW);
    }

    if (digitalRead(door2) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp2, HIGH);
    }
    else if (digitalRead(door2) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp2, LOW);
    }

    if (digitalRead(greenButton) == LOW) {
      digitalWrite(greenButtonLed, HIGH);
    }
    else if (digitalRead(greenButton) == HIGH) {
      digitalWrite(greenButtonLed, LOW);
    }
    //********

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("00");
    digitalWrite(redButtonLed, HIGH);

    //******** | IF Statements to update indicators during countdown
    if (digitalRead(securityKey) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(whiteLamp, HIGH);
    }
    else if (digitalRead(securityKey) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(whiteLamp, LOW);
    }

    if (digitalRead(door1) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp1, HIGH);
    }
    else if (digitalRead(door1) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp1, LOW);
    }

    if (digitalRead(door2) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp2, HIGH);
    }
    else if (digitalRead(door2) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp2, LOW);
    }

    if (digitalRead(greenButton) == LOW) {
      digitalWrite(greenButtonLed, HIGH);
    }
    else if (digitalRead(greenButton) == HIGH) {
      digitalWrite(greenButtonLed, LOW);
    }
    //********

    delay(1000);

    digitalWrite(redButtonLed, LOW);
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, HIGH);
    digitalWrite(blueLed, HIGH);
  }

  //Check to see if either door is open before "Active" stage is completely activated
  if ((digitalRead(door1) == HIGH || digitalRead(door2) == HIGH) && digitalRead(redLed) == HIGH && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == HIGH) {
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    //Blue LED remains HIGH
  }

  while (digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == HIGH && digitalRead(door1) == HIGH && digitalRead(door2) == LOW) {
    lcd.setCursor ( 0, 4 );
    lcd.print("  CLOSE DOOR 1 NOW  ");
    digitalWrite(yellowLamp1, HIGH);
    delay(500);
    lcd.setCursor ( 0, 4 );
    lcd.print("                    ");
    digitalWrite(yellowLamp1, LOW);
    delay(500);
  }

  while (digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == HIGH && digitalRead(door1) == LOW && digitalRead(door2) == HIGH) {
    lcd.setCursor ( 0, 4 );
    lcd.print("  CLOSE DOOR 2 NOW  ");
    digitalWrite(yellowLamp2, HIGH);
    delay(500);
    lcd.setCursor ( 0, 4 );
    lcd.print("                    ");
    digitalWrite(yellowLamp2, LOW);
    delay(500);
  }

  while (digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == HIGH && digitalRead(door1) == HIGH && digitalRead(door2) == HIGH) {
    lcd.setCursor ( 0, 4 );
    lcd.print("  CLOSE DOORS NOW   ");
    digitalWrite(yellowLamp1, HIGH);
    digitalWrite(yellowLamp2, HIGH);
    delay(500);
    lcd.setCursor ( 0, 4 );
    lcd.print("                    ");
    digitalWrite(yellowLamp1, LOW);
    digitalWrite(yellowLamp2, LOW);
    delay(500);
  }

  if ((digitalRead(redLed) == HIGH && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == HIGH && digitalRead(door1) == LOW && digitalRead(door2) == LOW) || (digitalRead(blueLed) == HIGH && digitalRead(greenLed) == LOW && digitalRead(redLed) == LOW && digitalRead(door1) == LOW && digitalRead(door2) == LOW)) {
    digitalWrite(greenLed, HIGH);
    digitalWrite(blueLed, LOW);
    digitalWrite(redLed, LOW);

    lcd.setCursor ( 0, 4 );
    lcd.print("   STATUS: ACTIVE   ");
    delay(500);
    lcd.setCursor ( 0, 4 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 4 );
    lcd.print("   STATUS: ACTIVE   ");
    delay(500);
    lcd.setCursor ( 0, 4 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 4 );
    lcd.print("   STATUS: ACTIVE   ");
    delay(500);
    lcd.setCursor ( 0, 4 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 4 );
    lcd.print("   STATUS: ACTIVE   ");
    //  digitalWrite(redLamp, HIGH); <<< REMOVED: redLamp is set to HIGH when securityKey is inactive (HIGH) after the WHILE statement below
  }

  //Deactivation without opening doors (e.g. if someone activates the alarm and does not leave the room)

  if (digitalRead(redLed) == LOW && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == LOW && digitalRead(securityKey) == HIGH && digitalRead(door1) == LOW && digitalRead(door2) == LOW) {
    digitalWrite(redButtonLed, LOW);
    lcd.setCursor ( 0, 2 );
    lcd.print("INSRT KEY TO DCATVTE");
  }

  while (digitalRead(redLed) == LOW && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == LOW && digitalRead(securityKey) == LOW && digitalRead(redButton) == HIGH) { //digitalRead(door1) == LOW && digitalRead(door2) == LOW REMOVED FROM CONDITIONS ?!
    if (digitalRead(securityKey) == LOW && digitalRead(redButton) == HIGH) {
      lcd.setCursor ( 0, 2 );
      lcd.print("REMOVE KEY TO SECURE");
      delay(2000);
      lcd.setCursor ( 0, 2 );
      lcd.print("                    ");
    }

    digitalWrite(redLamp, LOW);

    if (digitalRead(greenButton) == LOW) { //IF statement serves to update Green Button LED in this WHILE statement
      digitalWrite(greenButtonLed, HIGH);
    }
    else if (digitalRead(greenButton) == HIGH) {
      digitalWrite(greenButtonLed, LOW);
    }

    if (digitalRead(greenButton) == LOW) {
      digitalWrite(whiteLamp, HIGH);
    }
    else if (digitalRead(greenButton) == HIGH) {
      digitalWrite(whiteLamp, LOW);
    }

    //Door Indicator Functions > Included in WHILE statement
    if (digitalRead(door1) == LOW) {
      lcd.setCursor ( 4, 1 );
      lcd.print("CLSD");
    }
    else if (digitalRead(door1) == HIGH) {
      lcd.setCursor ( 4, 1 );
      lcd.print("OPEN");
    }
    if (digitalRead(door2) == LOW) {
      lcd.setCursor ( 16, 1 );
      lcd.print("CLSD");
    }
    else if (digitalRead(door2) == HIGH) {
      lcd.setCursor ( 16, 1 );
      lcd.print("OPEN");
    }

    if (digitalRead(door1) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp1, HIGH);
    }
    else if (digitalRead(door1) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp1, LOW);
    }

    if (digitalRead(door2) == LOW && digitalRead(greenButton) == LOW) {
      digitalWrite(yellowLamp2, HIGH);
    }
    else if (digitalRead(door2) == HIGH || digitalRead(greenButton) == HIGH) {
      digitalWrite(yellowLamp2, LOW);
    }

    if (digitalRead(securityKey) == LOW && digitalRead(redButton) == HIGH) {
      delay(500);
      lcd.setCursor ( 0, 2 );
      lcd.print("HOLD OFF: RED BUTTON");
      if (digitalRead(greenButton) == LOW) {
        digitalWrite(redButtonLed, HIGH);
      }
      if (digitalRead(redButton) == HIGH) {
        delay(2000);
        lcd.setCursor ( 0, 2 );
        lcd.print("                    ");
        digitalWrite(redButtonLed, LOW);
        delay(500);
      }
    }
  }

  //redLamp activation setting (RESET FOR redLamp LOCATED IN VOID SETUP)
  if (digitalRead(greenLed) == HIGH && digitalRead(redLed) == LOW && digitalRead(blueLed) == LOW && digitalRead(securityKey) == HIGH) {
    if (digitalRead(greenButton) == HIGH) {
      digitalWrite(redLamp, LOW);
    }
    else if (digitalRead(greenButton) == LOW) {
      digitalWrite(redLamp, HIGH);
    }
  }

  if (digitalRead(redLed) == LOW && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == LOW && digitalRead(securityKey) == LOW && digitalRead(redButton) == LOW) {
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(redButtonLed, LOW);
    lcd.setCursor ( 0, 2 );
    lcd.print("  SEC KEY: ACTIVE   ");
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    delay(500);
    resetFunc();
  }

  //Deactivation after door(s) opened + Alarm System

  if (digitalRead(redLed) == LOW && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == LOW && digitalRead(securityKey) == HIGH && (digitalRead(door1) == HIGH || digitalRead(door2) == HIGH)) {
    digitalWrite(greenLed, LOW);
    digitalWrite(whiteLamp, LOW);
    delay(250);
    if (digitalRead(securityKey) == HIGH) {
      lcd.setCursor ( 0, 2 );
      lcd.print(" SEC KEY: INACTIVE  ");
    }

    lcd.setCursor ( 0, 3 );
    lcd.print("COUNTDOWN INITIATED ");
    delay(1000);
    if (digitalRead(securityKey) == HIGH && digitalRead(greenLed) == LOW) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 09  ");
      delay(1000);
    }
    else if (digitalRead(securityKey) == LOW) {
      lcd.setCursor ( 0, 2 );
      lcd.print("  SEC KEY: ACTIVE   ");
    }
    if (digitalRead(securityKey) == HIGH && digitalRead(greenLed) == LOW) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 08  ");
      delay(1000);
    }
    else if (digitalRead(securityKey) == LOW) {
      lcd.setCursor ( 0, 2 );
      lcd.print("  SEC KEY: ACTIVE   ");
    }
    if (digitalRead(securityKey) == HIGH && digitalRead(greenLed) == LOW) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 07  ");
      delay(1000);
    }
    else if (digitalRead(securityKey) == LOW) {
      lcd.setCursor ( 0, 2 );
      lcd.print("  SEC KEY: ACTIVE   ");
    }
    if (digitalRead(securityKey) == HIGH && digitalRead(greenLed) == LOW) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 06  ");
      delay(1000);
    }
    else if (digitalRead(securityKey) == LOW) {
      lcd.setCursor ( 0, 2 );
      lcd.print("  SEC KEY: ACTIVE   ");
    }
    if (digitalRead(securityKey) == HIGH && digitalRead(greenLed) == LOW) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 05  ");
      delay(1000);
    }
    else if (digitalRead(securityKey) == LOW) {
      lcd.setCursor ( 0, 2 );
      lcd.print("  SEC KEY: ACTIVE   ");
    }
    if (digitalRead(securityKey) == HIGH && digitalRead(greenLed) == LOW) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 04  ");
      delay(1000);
    }
    else if (digitalRead(securityKey) == LOW) {
      lcd.setCursor ( 0, 2 );
      lcd.print("  SEC KEY: ACTIVE   ");
    }
    if (digitalRead(securityKey) == HIGH && digitalRead(greenLed) == LOW) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 03  ");
      delay(1000);
    }
    else if (digitalRead(securityKey) == LOW) {
      lcd.setCursor ( 0, 2 );
      lcd.print("  SEC KEY: ACTIVE   ");
    }
    if (digitalRead(securityKey) == HIGH && digitalRead(greenLed) == LOW) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 02  ");
      delay(1000);
    }
    else if (digitalRead(securityKey) == LOW) {
      lcd.setCursor ( 0, 2 );
      lcd.print("  SEC KEY: ACTIVE   ");
    }
    if (digitalRead(securityKey) == HIGH && digitalRead(greenLed) == LOW) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 01  ");
      delay(1000);
    }
    else if (digitalRead(securityKey) == LOW) {
      lcd.setCursor ( 0, 2 );
      lcd.print("  SEC KEY: ACTIVE   ");
    }
    if (digitalRead(securityKey) == HIGH && digitalRead(greenLed) == LOW) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 00  ");
      delay(1000);
    }
    else if (digitalRead(securityKey) == LOW) {
      lcd.setCursor ( 0, 2 );
      lcd.print("  SEC KEY: ACTIVE   ");
    }
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    digitalWrite(blueLed, LOW);

    if (digitalRead(securityKey) == LOW) {
      lcd.setCursor ( 0, 2 );
      lcd.print("   SEC KEY ACTIVE   ");
      lcd.setCursor ( 0, 3 );
      lcd.print("TURN OFF: RED BUTTON");
      digitalWrite(redButtonLed, HIGH);
      digitalWrite(greenLed, HIGH); //Turns on Green LED with Red LED - new configuration of status/memory RGB LED
    }
  }

  //If alarm is activated but security key is inserted before end (this first part has been added to the code above - redundancy) AND after security key is activated in response to siren
  if (digitalRead(redLed) == HIGH && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW && digitalRead(securityKey) == LOW && digitalRead(redButtonLed) == HIGH) {
    lcd.setCursor ( 0, 2 );
    lcd.print("   SEC KEY ACTIVE   ");
    lcd.setCursor ( 0, 3 );
    lcd.print("TURN OFF: RED BUTTON");
    digitalWrite(redButtonLed, HIGH);
    digitalWrite(greenLed, HIGH); //Turns on Green LED with Red LED - new configuration of status/memory RGB LED
  }

  if (digitalRead(redLed) == HIGH && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == LOW && digitalRead(securityKey) == LOW && digitalRead(redButton) == LOW) {
    digitalWrite(redButtonLed, LOW);
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    delay(500);
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW); //?!
    resetFunc();
  }

  //If alarm is triggered but Security Key is not active
  if (digitalRead(redLed) == HIGH && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW  && digitalRead(securityKey) == HIGH) {
    digitalWrite(redLed, HIGH);
    digitalWrite(blueLed, HIGH);
  }

  while (digitalRead(redLed) == HIGH && digitalRead(greenLed) == LOW && digitalRead(blueLed) == HIGH && digitalRead(securityKey) == HIGH) {
    lcd.setCursor ( 0, 3 );
    lcd.print("ALARM/SIREN ENGAGED ");

    digitalWrite(greenButtonLed, LOW);
    digitalWrite(yellowLamp1, LOW);
    digitalWrite(yellowLamp2, LOW);

    digitalWrite(redLamp, LOW);
    digitalWrite(whiteLamp, LOW);
    digitalWrite(yellowLamp1, LOW);
    digitalWrite(yellowLamp2, LOW);

    if (digitalRead(door1) == LOW) { //Updates Door open/closed status on LCD screen
      lcd.setCursor ( 4, 1 );
      lcd.print("CLSD");
    }
    else if (digitalRead(door1) == HIGH) {
      lcd.setCursor ( 4, 1 );
      lcd.print("OPEN");
    }
    if (digitalRead(door2) == LOW) {
      lcd.setCursor ( 16, 1 );
      lcd.print("CLSD");
    }
    else if (digitalRead(door2) == HIGH) {
      lcd.setCursor ( 16, 1 );
      lcd.print("OPEN");
    }

    digitalWrite(siren, HIGH);
    delay(250);
    digitalWrite(siren, LOW);
    delay(250);

    digitalWrite(redLamp, HIGH);
    digitalWrite(whiteLamp, HIGH);
    if (digitalRead(door1) == HIGH) {
      digitalWrite(yellowLamp1, HIGH);
    }
    if (digitalRead(door2) == HIGH) {
      digitalWrite(yellowLamp2, HIGH);
    }

    digitalWrite(siren, HIGH);
    delay(250);
    digitalWrite(siren, LOW);
    delay(250);

    if (digitalRead(door1) == LOW) { //Updates Door open/closed status on LCD screen
      lcd.setCursor ( 4, 1 );
      lcd.print("CLSD");
    }
    else if (digitalRead(door1) == HIGH) {
      lcd.setCursor ( 4, 1 );
      lcd.print("OPEN");
    }
    if (digitalRead(door2) == LOW) {
      lcd.setCursor ( 16, 1 );
      lcd.print("CLSD");
    }
    else if (digitalRead(door2) == HIGH) {
      lcd.setCursor ( 16, 1 );
      lcd.print("OPEN");
    }

    digitalWrite(redLamp, LOW);
    digitalWrite(whiteLamp, LOW);
    digitalWrite(yellowLamp1, LOW);
    digitalWrite(yellowLamp2, LOW);

    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");

    digitalWrite(siren, HIGH);
    delay(250);
    digitalWrite(siren, LOW);
    delay(250);

    digitalWrite(redLamp, HIGH);
    digitalWrite(whiteLamp, HIGH);
    if (digitalRead(door1) == HIGH) {
      digitalWrite(yellowLamp1, HIGH);
    }
    if (digitalRead(door2) == HIGH) {
      digitalWrite(yellowLamp2, HIGH);
    }

    digitalWrite(siren, HIGH);
    delay(250);
    digitalWrite(siren, LOW);
    delay(250);

    if (digitalRead(door1) == LOW) { //Updates Door open/closed status on LCD screen
      lcd.setCursor ( 4, 1 );
      lcd.print("CLSD");
    }
    else if (digitalRead(door1) == HIGH) {
      lcd.setCursor ( 4, 1 );
      lcd.print("OPEN");
    }
    if (digitalRead(door2) == LOW) {
      lcd.setCursor ( 16, 1 );
      lcd.print("CLSD");
    }
    else if (digitalRead(door2) == HIGH) {
      lcd.setCursor ( 16, 1 );
      lcd.print("OPEN");
    }

    digitalWrite(redLamp, LOW);
    digitalWrite(whiteLamp, LOW);
    digitalWrite(yellowLamp1, LOW);
    digitalWrite(yellowLamp2, LOW);

    lcd.setCursor ( 0, 3 );
    lcd.print("INSRT KEY TO DCATVTE");

    digitalWrite(siren, HIGH);
    delay(250);
    digitalWrite(siren, LOW);
    delay(250);

    digitalWrite(redLamp, HIGH);
    digitalWrite(whiteLamp, HIGH);
    if (digitalRead(door1) == HIGH) {
      digitalWrite(yellowLamp1, HIGH);
    }
    if (digitalRead(door2) == HIGH) {
      digitalWrite(yellowLamp2, HIGH);
    }

    digitalWrite(siren, HIGH);
    delay(250);
    digitalWrite(siren, LOW);
    delay(250);

    if (digitalRead(door1) == LOW) { //Updates Door open/closed status on LCD screen
      lcd.setCursor ( 4, 1 );
      lcd.print("CLSD");
    }
    else if (digitalRead(door1) == HIGH) {
      lcd.setCursor ( 4, 1 );
      lcd.print("OPEN");
    }
    if (digitalRead(door2) == LOW) {
      lcd.setCursor ( 16, 1 );
      lcd.print("CLSD");
    }
    else if (digitalRead(door2) == HIGH) {
      lcd.setCursor ( 16, 1 );
      lcd.print("OPEN");
    }

    digitalWrite(redLamp, LOW);
    digitalWrite(whiteLamp, LOW);
    digitalWrite(yellowLamp1, LOW);
    digitalWrite(yellowLamp2, LOW);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");

    digitalWrite(siren, HIGH);
    delay(250);
    digitalWrite(siren, LOW);
    delay(250);

    digitalWrite(redLamp, HIGH);
    digitalWrite(whiteLamp, HIGH);
    if (digitalRead(door1) == HIGH) {
      digitalWrite(yellowLamp1, HIGH);
    }
    if (digitalRead(door2) == HIGH) {
      digitalWrite(yellowLamp2, HIGH);
    }

    digitalWrite(siren, HIGH);
    delay(250);
    digitalWrite(siren, LOW);
    delay(250);
  }

  if (digitalRead(redLed) == HIGH && digitalRead(greenLed) == LOW && digitalRead(blueLed) == HIGH && digitalRead(securityKey) == LOW && digitalRead(redButton) == HIGH) {
    digitalWrite(siren, LOW);
    digitalWrite(blueLed, LOW);
    digitalWrite(redLamp, LOW);
    digitalWrite(whiteLamp, HIGH);
    lcd.setCursor ( 0, 3 );
    lcd.print("TURN OFF: RED BUTTON");
    digitalWrite(redButtonLed, HIGH);
    //Red LED remains active
  }

}
