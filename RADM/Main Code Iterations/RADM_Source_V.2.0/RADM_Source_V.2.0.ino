//Room Automated Defense Manager (RADM) | Source Code | Version 2.0 Revised | Russell A.D. MacGregor | 12/27/2020-12/29/2020
/*********************************************************************************************************************************************************************/

//NOTE: This project features heavily redundant code, as it was among the first I completed.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <SPI.h> //2.0 Additions (Libraries) 
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8);

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

//V 2.0 UpSdates :: Wireless Capability Variables ********
int dStatus[2];

bool d1Bool = false; //FALSE = OPEN, TRUE = CLOSED
bool d2Bool = false;
bool d1StatusSent = false;
bool d2StatusSent = true;

bool alarmTriggered = false;

const byte address[6] = "RADM1";
//********

//Serial Monitor Status Variables
bool doorStatusToggle = false;
bool systemReset = false;
int serialInput = 0;
//

void(* resetFunc) (void) = 0;

void setup() {

  //Pin Mode Settings
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

  //LCD Initialization
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight
  lcd.noCursor();
  lcd.noBlink();

  lcd.setCursor ( 0, 0 );            // go to the top left corner
  lcd.print("RADM | V2.0 | ONLINE"); //"ONLINE" changed from "ACTIVE"
  lcd.setCursor ( 0, 1 );            // go to the 2nd row
  lcd.print("D1: (..) || D2: (..)");
  lcd.setCursor ( 0, 2 );            // go to the third row
  lcd.print("   SEC KEY: ERROR   ");
  lcd.setCursor ( 0, 3 );            // go to the fourth row
  lcd.print(" STATUS: NOT READY  ");

  digitalWrite(redLamp, LOW);
  digitalWrite(redLed, LOW);

  //V.2.0 Updates ********
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH); //MIN, LOW, or HIGH, set to HIGH before final implementation ?!
  radio.startListening(); //RECEIVER
  //********

  Serial.print("RADM V2.0 ONLINE | Press X to toggle door status updates | Press R to reset system");
}

void checkDoorStatus() { //TO BE RECALLED IN MAIN CODE
  if (radio.available() && d1StatusSent == false && d2StatusSent == true) {

    radio.read(&dStatus[0], sizeof(dStatus[0]));

    if (dStatus[0] == 1) { //CLOSED = TRUE
      d1Bool = true;
      if (doorStatusToggle == true) {
        Serial.println("Door 1 Closed");
      }
      lcd.setCursor ( 4, 1 );
      lcd.print("CLSD");
      if (digitalRead(greenButton) == LOW) {
        digitalWrite(yellowLamp1, HIGH);
      }
    }

    if (dStatus[0] == 2) { //OPEN = FALSE
      d1Bool = false;
      if (doorStatusToggle == true) {
        Serial.println("Door 1 Open");
      }
      lcd.setCursor ( 4, 1 );
      lcd.print("OPEN");
      digitalWrite(yellowLamp1, LOW);
    }

    if (doorStatusToggle == true) {
      Serial.println(d1Bool);
    }

    d1StatusSent = true;
    d2StatusSent = false;
  }

  if (radio.available() && d1StatusSent == true && d2StatusSent == false) {
    radio.read(&dStatus[1], sizeof(dStatus[1]));

    if (dStatus[1] == 1) { //CLOSED = TRUE
      d2Bool = true;
      if (doorStatusToggle == true) {
        Serial.println("Door 2 Closed");
      }
      lcd.setCursor ( 16, 1 );
      lcd.print("CLSD");
      if (digitalRead(greenButton) == LOW) {
        digitalWrite(yellowLamp2, HIGH);
      }
    }

    if (dStatus[1] == 2) { //OPEN = FALSE
      d2Bool = false;
      if (doorStatusToggle == true) {
        Serial.println("Door 2 Open");
      }
      lcd.setCursor ( 16, 1 );
      lcd.print("OPEN");
      digitalWrite(yellowLamp2, LOW);
    }
    
    if (doorStatusToggle == true) {
      Serial.println(d2Bool);
    }
    
    d1StatusSent = false;
    d2StatusSent = true;
  }
}

void updateSecurityLamp() {
  if (digitalRead(securityKey) == LOW) {
    lcd.setCursor ( 0, 2 );            // go to the third row

    if (digitalRead(greenLed) == LOW) {
      lcd.print("  SEC KEY: ACTIVE   ");
    }

    if (digitalRead(greenButton) == LOW) {
      digitalWrite(whiteLamp, HIGH);
    }
  }
  else if (digitalRead(securityKey) == HIGH) {
    lcd.setCursor ( 0, 2 );            // go to the third row

    if (digitalRead(greenLed) == LOW) {
      lcd.print(" SEC KEY: INACTIVE  ");
    }

    if (digitalRead(greenButton) == HIGH) {
      digitalWrite(whiteLamp, LOW);
    }
  }
}

void checkSerialInputs() {

  if (Serial.available() > 0) {
    serialInput = Serial.read();
    //Serial.println("Input Recieved");
    delay(250);
  }
Serial.println(serialInput, DEC);
  //Checking Door Status Toggle Setting
  if (serialInput == "120" || serialInput == "88") { //120 DEC translates to "x" in ASCII, 88 DEC translates to "X" in ASCII

    if (doorStatusToggle == false) {
      doorStatusToggle == true;
    }
    else if (doorStatusToggle == true) {
      doorStatusToggle == false;
    }
  }
}

void updateInputs() { //******** | IF Statements to update indicators during countdown

  //Security Key-Related Updates
  updateSecurityLamp();

  //Door Statuses
  checkDoorStatus();

  //Serial Monitor Updates
  checkSerialInputs();

  //Green Button Settings
  if (digitalRead(greenButton) == LOW) {
    digitalWrite(greenButtonLed, HIGH);
    lcd.backlight();
  }
  else if (digitalRead(greenButton) == HIGH) {
    digitalWrite(greenButtonLed, LOW);
    lcd.noBacklight();
  }

  //Blue Button Settings << Could incorporate this into Green Button settings for more concise, "beautiful" code

  if (digitalRead(blueButton) == LOW && digitalRead(greenButton) == LOW) { //BLUE BUTTON NOT IN USE
    digitalWrite(blueButtonLed, HIGH);
  }
  else if (digitalRead(blueButton) == HIGH || digitalRead(greenButton) == HIGH) {
    digitalWrite(blueButtonLed, LOW);
  }

  if (digitalRead(greenButton) == HIGH) { //if green button is DEACTIVATED

    digitalWrite(yellowLamp1, LOW);
    digitalWrite(yellowLamp2, LOW);
    digitalWrite(whiteLamp, LOW);
    digitalWrite(redLamp, LOW);
    digitalWrite(redButtonLed, LOW);
    digitalWrite(greenButtonLed, LOW);
    digitalWrite(blueButtonLed, LOW);
    lcd.noBacklight();
  }
}

void loop() {
  updateInputs();

  //Alarm Stage 1: "Not Ready"
  //Default Stage established during program initialization

  //Alarm Stage 2: "Ready"

  //If user attempts to activate alarm without inserting security key first
  if (d1Bool == true && d2Bool == true && digitalRead(securityKey) == HIGH && digitalRead(redButton) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: ACTIVATE KEY");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: ACTIVATE KEY");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: ACTIVATE KEY");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: NOT READY  ");
  }

  //If user attempts to activate alarm without closing Door 1 first
  if (d1Bool == false && d2Bool == true && digitalRead(securityKey) == LOW && digitalRead(redButton) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: CLOSE DOOR 1");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: CLOSE DOOR 1");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: CLOSE DOOR 1");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: CLOSE DOOR 1");
  }

  //If user attempts to activate alarm without closing Door 2 first
  if (d1Bool == true && d2Bool == false && digitalRead(securityKey) == LOW && digitalRead(redButton) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: CLOSE DOOR 2");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: CLOSE DOOR 2");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: CLOSE DOOR 2");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: CLOSE DOOR 2");
  }

  //If user attempts to activate alarm without closing both doors or activating security key first
  if (d1Bool == false && d2Bool == false && digitalRead(securityKey) == HIGH && digitalRead(redButton) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOORS AND KEY  ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOORS AND KEY  ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOORS AND KEY  ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: NOT READY  ");
  }

  //If user attempts to activate alarm without closing Door 1 or activating security key first
  if (d1Bool == false && d2Bool == true && digitalRead(securityKey) == HIGH && digitalRead(redButton) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOOR 1 AND KEY ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOOR 1 AND KEY ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOOR 1 AND KEY ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: NOT READY  ");
  }

  //If user attempts to activate alarm without closing Door 1 or activating security key first
  if (d1Bool == true && d2Bool == false && digitalRead(securityKey) == HIGH && digitalRead(redButton) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOOR 2 AND KEY ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOOR 2 AND KEY ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" !!> DOOR 2 AND KEY ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: NOT READY  ");
  }

  //If user attempts to activate alarm without closing Door 1 or Door 2, Security Key active
  if (d1Bool == false && d2Bool == false && digitalRead(securityKey) == LOW && digitalRead(redButton) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print("!!> CLOSE DOORS 1+2 ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("!!> CLOSE DOORS 1+2 ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("!!> CLOSE DOORS 1+2 ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: NOT READY  ");
  }

  if (d1Bool == true && d2Bool == true && digitalRead(securityKey) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print("   STATUS: READY    ");
  }
  else if ((d1Bool == false || d2Bool == false || securityKey == HIGH) && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print(" STATUS: NOT READY  ");
  }

  if (d1Bool == true && d2Bool == true && digitalRead(securityKey) == LOW && digitalRead(redButton) == LOW) {
    lcd.setCursor ( 0, 3 );
    lcd.print("STATUS: ACTIVE IN 10");
    digitalWrite(redButtonLed, HIGH);
    updateInputs();

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("09");
    digitalWrite(redButtonLed, LOW);
    updateInputs();

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("08");
    digitalWrite(redButtonLed, HIGH);
    updateInputs();

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("07");
    digitalWrite(redButtonLed, LOW);
    updateInputs();

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("06");
    digitalWrite(redButtonLed, HIGH);
    updateInputs();

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("05");
    digitalWrite(redButtonLed, LOW);
    updateInputs();

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("04");
    digitalWrite(redButtonLed, HIGH);
    updateInputs();

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("03");
    digitalWrite(redButtonLed, LOW);
    updateInputs();

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("02");
    digitalWrite(redButtonLed, HIGH);
    updateInputs();

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("01");
    digitalWrite(redButtonLed, LOW);
    updateInputs();

    delay(1000);

    lcd.setCursor ( 18, 3 );
    lcd.print("00");
    digitalWrite(redButtonLed, HIGH);
    updateInputs();

    delay(1000);

    digitalWrite(redButtonLed, LOW);
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, HIGH);
    digitalWrite(blueLed, HIGH);
  }

  //Check to see if either door is open before "Active" stage is completely activated
  if ((d1Bool == false || d2Bool == false) && alarmTriggered == false && digitalRead(redLed) == HIGH && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == HIGH) {
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    Serial.println("Door 1 is open before active stage triggered");
    //Blue LED remains HIGH
  }

  while (digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == HIGH && d1Bool == false && d2Bool == true) {
    lcd.setCursor ( 0, 3 );
    lcd.print("  CLOSE DOOR 1 NOW  ");
    digitalWrite(yellowLamp1, HIGH);
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    digitalWrite(yellowLamp1, LOW);
    delay(500);
    updateInputs();
  }

  while (digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == HIGH && d1Bool == true && d2Bool == false) {
    lcd.setCursor ( 0, 3 );
    lcd.print("  CLOSE DOOR 2 NOW  ");
    digitalWrite(yellowLamp2, HIGH);
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    digitalWrite(yellowLamp2, LOW);
    delay(500);
    updateInputs();
  }

  while (digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == HIGH && d1Bool == false && d2Bool == false) {
    lcd.setCursor ( 0, 3 );
    lcd.print("  CLOSE DOORS NOW   ");
    digitalWrite(yellowLamp1, HIGH);
    digitalWrite(yellowLamp2, HIGH);
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    digitalWrite(yellowLamp1, LOW);
    digitalWrite(yellowLamp2, LOW);
    delay(500);
    updateInputs();
  }

  if ((digitalRead(redLed) == HIGH && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == HIGH && d1Bool == true && d2Bool == true) || (digitalRead(blueLed) == HIGH && digitalRead(greenLed) == LOW && digitalRead(redLed) == LOW && d1Bool == true && d2Bool == true)) {
    digitalWrite(greenLed, HIGH);
    digitalWrite(blueLed, LOW);
    digitalWrite(redLed, LOW);
    Serial.println("Green LED is turned on while Red and Blue are turned off");

    lcd.setCursor ( 0, 3 );
    lcd.print("   STATUS: ACTIVE   ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("   STATUS: ACTIVE   ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("   STATUS: ACTIVE   ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("   STATUS: ACTIVE   ");
    //  digitalWrite(redLamp, HIGH); <<< REMOVED: redLamp is set to HIGH when securityKey is inactive (HIGH) after the WHILE statement below
  }

  //Deactivation without opening doors (e.g. if someone activates the alarm and does not leave the room)

  while (digitalRead(redLed) == LOW && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == LOW && digitalRead(securityKey) == LOW && digitalRead(redButton) == HIGH) { //d1Bool == true && d2Bool == true REMOVED FROM CONDITIONS ?!
    updateInputs();
    if (digitalRead(securityKey) == LOW && digitalRead(redButton) == HIGH) {
      lcd.setCursor ( 0, 2 );
      lcd.print("REMOVE KEY TO SECURE");
      updateInputs();
      delay(2000);
      lcd.setCursor ( 0, 2 );
      lcd.print("                    ");
    }

    updateInputs();

    if (digitalRead(securityKey) == LOW && digitalRead(redButton) == HIGH) {
      delay(500);
      lcd.setCursor ( 0, 2 );
      lcd.print("HOLD OFF: RED BUTTON");
      if (digitalRead(greenButton) == LOW) {
        digitalWrite(redButtonLed, HIGH);
      }
      updateInputs();
      if (digitalRead(redButton) == HIGH) {
        delay(2000);
        lcd.setCursor ( 0, 2 );
        lcd.print("                    ");
        digitalWrite(redButtonLed, LOW);
        updateInputs();
        delay(500);
      }
    }
  }

  //redLamp activation setting (RESET FOR redLamp LOCATED IN VOID SETUP)
  if (digitalRead(greenLed) == HIGH && digitalRead(redLed) == LOW && digitalRead(blueLed) == LOW && digitalRead(securityKey) == HIGH) { //Not revised; this section has a specific action for redLamp that is not included in updateInputs()
    if (digitalRead(greenButton) == HIGH) {
      digitalWrite(redLamp, LOW);
    }
    else if (digitalRead(greenButton) == LOW) {
      digitalWrite(redLamp, HIGH);
    }
    checkDoorStatus();
  }

  if (digitalRead(redLed) == LOW && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == LOW && digitalRead(securityKey) == HIGH && d1Bool == true && d2Bool == true) {
    digitalWrite(redButtonLed, LOW);
    lcd.setCursor ( 0, 2 );
    lcd.print("INSRT KEY TO DCATVTE");
    //digitalWrite(redLamp, HIGH); ?!
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
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    updateInputs();
    delay(500);
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    updateInputs();
    delay(500);
    resetFunc();
  }

  //Deactivation after door(s) opened + Alarm System

  if (digitalRead(redLed) == LOW && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == LOW && digitalRead(securityKey) == HIGH && (d1Bool == false || d2Bool == false)) {
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
    if (digitalRead(securityKey) == HIGH) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 09  ");
      delay(1000);
    }
    //    updateSecurityLamp(); << All of these were removed from the remaining if statements in this countdown; replace them if necessary

    if (digitalRead(securityKey) == HIGH) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 08  ");
      delay(1000);
    }

    if (digitalRead(securityKey) == HIGH) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 07  ");
      delay(1000);
    }

    if (digitalRead(securityKey) == HIGH) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 06  ");
      delay(1000);
    }

    if (digitalRead(securityKey) == HIGH) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 05  ");
      delay(1000);
    }

    if (digitalRead(securityKey) == HIGH) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 04  ");
      delay(1000);
    }

    if (digitalRead(securityKey) == HIGH) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 03  ");
      delay(1000);
    }

    if (digitalRead(securityKey) == HIGH) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 02  ");
      delay(1000);
    }

    if (digitalRead(securityKey) == HIGH) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 01  ");
      delay(1000);
    }

    if (digitalRead(securityKey) == HIGH) {
      lcd.setCursor ( 0, 3 );
      lcd.print(" ALARM SIREN IN 00  ");
      delay(1000);
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
  //BELOW CODE HAS NOT BEEN UPDATED YET ?!
  //If alarm is activated but security key is inserted before end (this first part has been added to the code above - redundancy) AND after security key is activated in response to siren
  if (((digitalRead(redLed) == HIGH && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW) || (digitalRead(redLed) == HIGH && digitalRead(greenLed) == LOW && digitalRead(blueLed) == HIGH)) && digitalRead(securityKey) == LOW && digitalRead(redButtonLed) == HIGH) {
    lcd.setCursor ( 0, 2 );
    lcd.print("   SEC KEY ACTIVE   ");
    lcd.setCursor ( 0, 3 );
    lcd.print("TURN OFF: RED BUTTON");
    updateInputs();
    digitalWrite(redButtonLed, HIGH);
    digitalWrite(greenLed, HIGH); //Turns on Green LED with Red LED - new configuration of status/memory RGB LED
  }

  if (digitalRead(redLed) == HIGH && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == LOW && digitalRead(securityKey) == LOW && digitalRead(redButton) == LOW) {
    alarmTriggered = false;
    digitalWrite(redButtonLed, LOW);
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    delay(500);
    updateInputs();
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    updateInputs();
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    delay(500);
    updateInputs();
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    updateInputs();
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    delay(500);
    updateInputs();
    lcd.setCursor ( 0, 3 );
    lcd.print("                    ");
    delay(500);
    updateInputs();
    lcd.setCursor ( 0, 3 );
    lcd.print("  ALARM DISENGAGED  ");
    delay(500);
    updateInputs();
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW); //?!
    resetFunc();
  }

  //If alarm is triggered but Security Key is not active
  if (digitalRead(redLed) == HIGH && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW  && digitalRead(securityKey) == HIGH) {
    //Red LED remains active
    digitalWrite(blueLed, HIGH);
    alarmTriggered = true;
  }

  //Alarm - alarmTriggered boolean is also used to prevent an error regarding to Line 523
  while (alarmTriggered == true && digitalRead(redLed) == HIGH && digitalRead(greenLed) == LOW && digitalRead(blueLed) == HIGH && digitalRead(securityKey) == HIGH) {
    lcd.setCursor ( 0, 3 );
    lcd.print("ALARM/SIREN ENGAGED ");

    digitalWrite(greenButtonLed, LOW);
    digitalWrite(yellowLamp1, LOW);
    digitalWrite(yellowLamp2, LOW);

    digitalWrite(redLamp, LOW);
    digitalWrite(whiteLamp, LOW);
    digitalWrite(yellowLamp1, LOW);
    digitalWrite(yellowLamp2, LOW);

    if (d1Bool == true) { //Updates Door open/closed status on LCD screen
      lcd.setCursor ( 4, 1 );
      lcd.print("CLSD");
    }
    else if (d1Bool == false) {
      lcd.setCursor ( 4, 1 );
      lcd.print("OPEN");
    }
    if (d2Bool == true) {
      lcd.setCursor ( 16, 1 );
      lcd.print("CLSD");
    }
    else if (d2Bool == false) {
      lcd.setCursor ( 16, 1 );
      lcd.print("OPEN");
    }

    digitalWrite(siren, HIGH);
    delay(250);
    digitalWrite(siren, LOW);
    delay(250);

    digitalWrite(redLamp, HIGH);
    digitalWrite(whiteLamp, HIGH);
    if (d1Bool == false) {
      digitalWrite(yellowLamp1, HIGH);
    }
    if (d2Bool == false) {
      digitalWrite(yellowLamp2, HIGH);
    }

    digitalWrite(siren, HIGH);
    delay(250);
    digitalWrite(siren, LOW);
    delay(250);

    if (d1Bool == true) { //Updates Door open/closed status on LCD screen
      lcd.setCursor ( 4, 1 );
      lcd.print("CLSD");
    }
    else if (d1Bool == false) {
      lcd.setCursor ( 4, 1 );
      lcd.print("OPEN");
    }
    if (d2Bool == true) {
      lcd.setCursor ( 16, 1 );
      lcd.print("CLSD");
    }
    else if (d2Bool == false) {
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
    if (d1Bool == false) {
      digitalWrite(yellowLamp1, HIGH);
    }
    if (d2Bool == false) {
      digitalWrite(yellowLamp2, HIGH);
    }

    digitalWrite(siren, HIGH);
    delay(250);
    digitalWrite(siren, LOW);
    delay(250);

    if (d1Bool == true) { //Updates Door open/closed status on LCD screen
      lcd.setCursor ( 4, 1 );
      lcd.print("CLSD");
    }
    else if (d1Bool == false) {
      lcd.setCursor ( 4, 1 );
      lcd.print("OPEN");
    }
    if (d2Bool == true) {
      lcd.setCursor ( 16, 1 );
      lcd.print("CLSD");
    }
    else if (d2Bool == false) {
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
    if (d1Bool == false) {
      digitalWrite(yellowLamp1, HIGH);
    }
    if (d2Bool == false) {
      digitalWrite(yellowLamp2, HIGH);
    }

    digitalWrite(siren, HIGH);
    delay(250);
    digitalWrite(siren, LOW);
    delay(250);

    if (d1Bool == true) { //Updates Door open/closed status on LCD screen
      lcd.setCursor ( 4, 1 );
      lcd.print("CLSD");
    }
    else if (d1Bool == false) {
      lcd.setCursor ( 4, 1 );
      lcd.print("OPEN");
    }
    if (d2Bool == true) {
      lcd.setCursor ( 16, 1 );
      lcd.print("CLSD");
    }
    else if (d2Bool == false) {
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
    if (d1Bool == false) {
      digitalWrite(yellowLamp1, HIGH);
    }
    if (d2Bool == false) {
      digitalWrite(yellowLamp2, HIGH);
    }

    digitalWrite(siren, HIGH);
    delay(250);
    digitalWrite(siren, LOW);
    delay(250);
  }

  if (digitalRead(redLed) == HIGH && digitalRead(greenLed) == LOW && digitalRead(blueLed) == HIGH && digitalRead(securityKey) == LOW && digitalRead(redButton) == HIGH) {
    digitalWrite(siren, LOW);
    digitalWrite(whiteLamp, HIGH);
    lcd.setCursor ( 0, 3 );
    lcd.print("TURN OFF: RED BUTTON");
    digitalWrite(blueLed, LOW);
    digitalWrite(redButtonLed, HIGH);
  }
}
