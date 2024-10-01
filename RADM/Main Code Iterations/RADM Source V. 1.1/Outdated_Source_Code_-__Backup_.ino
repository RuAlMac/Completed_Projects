#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); 

int door1 = 5; //32
int door2 = 4; //33
int redLamp = 28;
int whiteLamp = 6; //29
int yellowLamp1 = 30;
int yellowLamp2 = 31;
int redButtonLed = 10; //38
int greenButtonLed = 40;
int blueButtonLed = 42;
int redButton = 8; //44
int greenButton = 7; //46
int blueButton = 48;
int securityKey = 9; //37
int redLed = 13; //34
int greenLed = 12; //35
int blueLed = 11; //36

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
 

//LCD Initialization
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
  lcd.noCursor();
  lcd.noBlink();
   
  lcd.setCursor ( 0, 0 );            // go to the top left corner
  lcd.print("RADM | V.1R | ACTIVE");
  lcd.setCursor ( 0, 1 );            // go to the 2nd row
  lcd.print("D1: //// || D2: ////"); 
  lcd.setCursor ( 0, 2 );            // go to the third row
  lcd.print("SEC KEY: /////");
  lcd.setCursor ( 0, 3 );            // go to the fourth row
  lcd.print(" STATUS: NOT READY  ");
}

void loop() {
//Security Key LCD Status Setting

if (digitalRead(securityKey) == LOW && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW){
  lcd.setCursor ( 0, 2 );            // go to the third row
  lcd.print("  SEC KEY: ACTIVE   ");
}
  else if (digitalRead(securityKey) == HIGH && digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW){
  lcd.setCursor ( 0, 2 );            // go to the third row
  lcd.print(" SEC KEY: INACTIVE  ");
  }

//Door LCD Status Settings

if (digitalRead(door1) == LOW){
  lcd.setCursor ( 4, 1 );
  lcd.print("CLSD");
}
  else if (digitalRead(door1) == HIGH){
  lcd.setCursor ( 4, 1 );
  lcd.print("OPEN");
  }
if (digitalRead(door2) == LOW){
  lcd.setCursor ( 16, 1 );
  lcd.print("CLSD");
}
  else if (digitalRead(door2) == HIGH){
  lcd.setCursor ( 16, 1 );
  lcd.print("OPEN");
  }
//Lamp Function Assignments

if (digitalRead(greenButton) == LOW){ //if green button is ACTIVATED > more effective/optimal method for implemting this possible?

//lcd.backlight(); <<< REACTIVATE BEFORE FINAL IMPLEMENTATION

  if (digitalRead(door1) == LOW){
  digitalWrite(yellowLamp1, HIGH);
  }
    else if (digitalRead(door1) == HIGH){
    digitalWrite(yellowLamp1, LOW);
     }

  if (digitalRead(door2) == LOW){
  digitalWrite(yellowLamp2, HIGH);
  }
    else if (digitalRead(door2) == HIGH){
    digitalWrite(yellowLamp2, LOW);
    }
    
  if (digitalRead(securityKey) == LOW){
  digitalWrite(whiteLamp, HIGH);
  }
    else if (digitalRead(securityKey) == HIGH){
    digitalWrite(whiteLamp, LOW);
    }

  //Preliminary Button LED Activation Settings (Excepting Red)

  if (digitalRead(greenButton) == LOW){
    digitalWrite(greenButtonLed, HIGH);
  }
    else if (digitalRead(greenButton) == HIGH){
      digitalWrite(greenButtonLed, LOW);
    }

/*if (digitalRead(blueButton) == LOW){ //BLUE BUTTON NOT IN USE
  digitalWrite(blueButtonLed, HIGH);
}
  else if (digitalRead(blueButton) == HIGH){
    digitalWrite(blueButtonLed, LOW);
*/
}

if (digitalRead(greenButton) == HIGH){ //if green button is DEACTIVATED

  digitalWrite(yellowLamp1, LOW);
  digitalWrite(yellowLamp2, LOW);
  digitalWrite(whiteLamp, LOW);
  digitalWrite(redButtonLed, LOW);
  digitalWrite(greenButtonLed, LOW);
  digitalWrite(blueButtonLed, LOW);
  //lcd.noBacklight(); <<< REACTIVATE BEFORE FINAL IMPLEMENTATION
}

//Alarm Stage 1: "Not Ready"
  //Default Stage established during program initialization

//Alarm Stage 2: "Ready"

if (digitalRead(door1) == LOW && digitalRead(door2) == LOW && digitalRead(securityKey) == HIGH && digitalRead(redButton) == LOW){
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

if (digitalRead(door1) == LOW && digitalRead(door2) == LOW && digitalRead(securityKey) == LOW && digitalRead(greenLed) == LOW){
  lcd.setCursor ( 0, 3 );
  lcd.print("   STATUS: READY    ");
}
  else if (digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == LOW){
  lcd.setCursor ( 0, 3 );
  lcd.print(" STATUS: NOT READY  ");
  }

if (digitalRead(door1) == LOW && digitalRead(door2) == LOW && digitalRead(securityKey) == LOW && digitalRead(redButton) == LOW){
  lcd.setCursor ( 0, 3 );
  lcd.print("STATUS: ACTIVE IN 10");
  digitalWrite(redButtonLed, HIGH);
  delay(1000);
  lcd.setCursor ( 18, 3 );
  lcd.print("09");
  digitalWrite(redButtonLed, LOW);
  delay(1000);
  lcd.setCursor ( 18, 3 );
  lcd.print("08");
  digitalWrite(redButtonLed, HIGH);
  delay(1000);
  lcd.setCursor ( 18, 3 );
  lcd.print("07");
  digitalWrite(redButtonLed, LOW);
  delay(1000);
  lcd.setCursor ( 18, 3 );
  lcd.print("06");
  digitalWrite(redButtonLed, HIGH);
  delay(1000);
  lcd.setCursor ( 18, 3 );
  lcd.print("05");
  digitalWrite(redButtonLed, LOW);
  delay(1000);
  lcd.setCursor ( 18, 3 );
  lcd.print("04");
  digitalWrite(redButtonLed, HIGH);
  delay(1000);
  lcd.setCursor ( 18, 3 );
  lcd.print("03");
  digitalWrite(redButtonLed, LOW);
  delay(1000);
  lcd.setCursor ( 18, 3 );
  lcd.print("02");
  digitalWrite(redButtonLed, HIGH);
  delay(1000);
  lcd.setCursor ( 18, 3 );
  lcd.print("01");
  digitalWrite(redButtonLed, LOW);
  delay(1000);
  lcd.setCursor ( 18, 3 );
  lcd.print("00");
  digitalWrite(redButtonLed, HIGH);
  delay(1000);
  digitalWrite(redButtonLed, LOW);
  
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, HIGH);
  digitalWrite(blueLed, HIGH);
}

//Check to see if either door is open before "Active" stage is completely activated
if ((digitalRead(door1) == HIGH || digitalRead(door2) == HIGH)){
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, LOW);
  digitalWrite(blueLed, HIGH);
}

while (digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == HIGH && digitalRead(door1)== HIGH && digitalRead(door2)== LOW){
  lcd.setCursor ( 0, 4 );
  lcd.print("  CLOSE DOOR 1 NOW  ");
  digitalWrite(yellowLamp1, HIGH);
  delay(500);
  lcd.setCursor ( 0, 4 );
  lcd.print("                    ");
  digitalWrite(yellowLamp1, LOW);
  delay(500);
}

while (digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == HIGH && digitalRead(door1)== LOW && digitalRead(door2)== HIGH){
  lcd.setCursor ( 0, 4 );
  lcd.print("  CLOSE DOOR 2 NOW  ");
  digitalWrite(yellowLamp2, HIGH);
  delay(500);
  lcd.setCursor ( 0, 4 );
  lcd.print("                    ");
  digitalWrite(yellowLamp2, LOW);
  delay(500);
}

while (digitalRead(redLed) == LOW && digitalRead(greenLed) == LOW && digitalRead(blueLed) == HIGH && digitalRead(door1)== HIGH && digitalRead(door2)== HIGH){
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

if ((digitalRead(redLed) == HIGH && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == HIGH && digitalRead(door1)== LOW && digitalRead(door2)== LOW)||(digitalRead(blueLed) == HIGH && digitalRead(greenLed) == LOW && digitalRead(redLed) == LOW && digitalRead(door1) == LOW && digitalRead(door2) == LOW)){
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
  digitalWrite(redLamp, HIGH);
}

//Deactivation without opening doors (e.g. if someone activates the alarm and does not leave the room)

if (digitalRead(redLed) == LOW && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == LOW && digitalRead(securityKey) == HIGH && digitalRead(door1) == LOW && digitalRead(door2) == LOW){
  lcd.setCursor ( 0, 2 );
  lcd.print("INSRT KEY TO DCATVTE");
}
  
if (digitalRead(redLed) == LOW && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == LOW && digitalRead(securityKey) == LOW && digitalRead(door1) == LOW && digitalRead(door2) == LOW && digitalRead(redButton) == HIGH){
  lcd.setCursor ( 0, 2 );
  lcd.print("TURN OFF: RED BUTTON");
  if (digitalRead(greenButton) == LOW){
    digitalWrite(redButtonLed, HIGH);
  }
}

if (digitalRead(redLed) == LOW && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == LOW && digitalRead(securityKey) == LOW && digitalRead(door1) == LOW && digitalRead(door2) == LOW && digitalRead(redButton) == LOW){
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

if (digitalRead(redLed) == LOW && digitalRead(greenLed) == HIGH && digitalRead(blueLed) == LOW && digitalRead(securityKey) == HIGH && (digitalRead(door1) == HIGH || digitalRead(door2) == HIGH)){
  lcd.setCursor ( 0, 3 );
  lcd.print("COUNTDOWN INITIATED ");
  delay(1000);
  lcd.setCursor ( 0, 3 );
  lcd.print(" ALARM SIREN IN 09  ");
  delay(1000);
  lcd.setCursor ( 0, 3 );
  lcd.print(" ALARM SIREN IN 08  ");
  delay(1000);
  lcd.setCursor ( 0, 3 );
  lcd.print(" ALARM SIREN IN 07  ");
  delay(1000);
  lcd.setCursor ( 0, 3 );
  lcd.print(" ALARM SIREN IN 06  ");
  delay(1000);
  lcd.setCursor ( 0, 3 );
  lcd.print(" ALARM SIREN IN 05  ");
  delay(1000);
  lcd.setCursor ( 0, 3 );
  lcd.print(" ALARM SIREN IN 04  ");
  delay(1000);
  lcd.setCursor ( 0, 3 );
  lcd.print(" ALARM SIREN IN 03  ");
  delay(1000);
  lcd.setCursor ( 0, 3 );
  lcd.print(" ALARM SIREN IN 02  ");
  delay(1000);
  lcd.setCursor ( 0, 3 );
  lcd.print(" ALARM SIREN IN 01  ");
  delay(1000);
  lcd.setCursor ( 0, 3 );
  lcd.print(" ALARM SIREN IN 00  ");
  delay(1000);
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, HIGH);
}


//If alarm is activated but security key is inserted before end
if (digitalRead(redLed) == HIGH && digitalRead(securityKey) == LOW && digitalRead(redButtonLed) == HIGH){
  lcd.setCursor ( 0, 2 );
  lcd.print("   SEC KEY ACTIVE   ");
  lcd.setCursor ( 0, 3 );
  lcd.print("TURN OFF: RED BUTTON");
  digitalWrite(redButtonLed, HIGH);
}

if (digitalRead(redLed) == HIGH && digitalRead(securityKey) == LOW && digitalRead(redButton) == LOW){
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
  resetFunc();
}

}
