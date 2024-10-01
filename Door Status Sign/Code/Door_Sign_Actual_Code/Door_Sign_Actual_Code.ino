//RECEIVER CODE
#include <SPI.h> //2.0 Additions (Libraries)
#include <nRF24L01.h>
#include <RF24.h>

#include <Wire.h> //LCD Screen Libraries
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

RF24 radio(9, 8);

int availableSetting[2];
bool doorbellSetting[2];
const byte address[6] = "ALARM";

int redLed = 22;
int yellowLed = 23;
int greenLed = 24;
int blueLed = 25;

int redCLed = 30;
int greenCLed = 33;
int blueCLed = 32;

int button = 36;

int bootDelay = 500;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH); //MIN, LOW, or HIGH
  radio.startListening(); //RECEIVER

  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight

  doorbellSetting[0] = false;

  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  pinMode(redCLed, OUTPUT);
  pinMode(greenCLed, OUTPUT);
  pinMode(blueCLed, OUTPUT);

  pinMode(button, INPUT_PULLUP);

  bootSequence(); //Cosmetic-only boot sequence for LEDs
}

void loop() {
  if (radio.available()) {

    radio.read(&availableSetting[0], sizeof(availableSetting[0]));

    if (availableSetting[0] == 1) {
      updateUI();
      digitalWrite(redLed, HIGH);
    }

    if (availableSetting[0] == 2) {
      updateUI();
      digitalWrite(yellowLed, HIGH);
    }

    if (availableSetting[0] == 3) {
      updateUI();
      digitalWrite(greenLed, HIGH);
    }

    if (availableSetting[0] == 4) {
      updateUI();
      digitalWrite(blueLed, HIGH);
    }

    Serial.println(availableSetting[0]);
  }

  if (digitalRead(button) == LOW) {

    if (availableSetting[0] == 2 || availableSetting[0] == 3) {

      doorbellSetting[0] = true;

      digitalWrite(greenCLed, LOW);
      digitalWrite(blueCLed, LOW);
      digitalWrite(redCLed, HIGH);

      //Switching to Transmitter Mode //**************************
      radio.openWritingPipe(address);
      radio.stopListening(); //**************************
      radio.write(&doorbellSetting[0], sizeof(doorbellSetting[0])); //**************************

      delay(250); //REVIEW

      //Return to Receiver Mode
      radio.startListening(); //**************************

      digitalWrite(redCLed, LOW);
      doorbellSetting[0] = false;
    }

    if (availableSetting[0] == 1 || availableSetting[0] == 4) {
      lcd.setCursor ( 0, 0 );            // go to the top left corner
      lcd.print("NOTICE: Bell Off");
      lcd.setCursor ( 0, 1 );            // go to the 2nd row
      lcd.print("Come Back Later ");

      delay(500);

      lcd.setCursor ( 0, 0 );            // go to the top left corner
      lcd.print("                ");
      lcd.setCursor ( 0, 1 );            // go to the 2nd row
      lcd.print("                ");

      delay(500);

      lcd.setCursor ( 0, 0 );            // go to the top left corner
      lcd.print("NOTICE: Bell Off");
      lcd.setCursor ( 0, 1 );            // go to the 2nd row
      lcd.print("Come Back Later ");

      delay(500);

      lcd.setCursor ( 0, 0 );            // go to the top left corner
      lcd.print("                ");
      lcd.setCursor ( 0, 1 );            // go to the 2nd row
      lcd.print("                ");

      delay(500);

      lcd.setCursor ( 0, 0 );            // go to the top left corner
      lcd.print("NOTICE: Bell Off");
      lcd.setCursor ( 0, 1 );            // go to the 2nd row
      lcd.print("Come Back Later ");

      delay(2000);
      
      updateUI();
    }
  }
}

void updateUI() {
  ledOff();

  if (availableSetting[0] == 1) {
    lcd.setCursor ( 0, 0 );            // go to the top left corner
    lcd.print(" DO NOT DISTURB ");
    lcd.setCursor ( 0, 1 );            // go to the 2nd row
    lcd.print(" [Doorbell Off] ");
  }

  if (availableSetting[0] == 2) {
    lcd.setCursor ( 0, 0 );            // go to the top left corner
    lcd.print("  Knock First   ");
    lcd.setCursor ( 0, 1 );            // go to the 2nd row
    lcd.print(" [Doorbell On]  ");
  }

  if (availableSetting[0] == 3) {
    lcd.setCursor ( 0, 0 );            // go to the top left corner
    lcd.print("  Knock First   ");
    lcd.setCursor ( 0, 1 );            // go to the 2nd row
    lcd.print(" [Doorbell On]  ");
  }

  if (availableSetting[0] == 4) {
    lcd.setCursor ( 0, 0 );            // go to the top left corner
    lcd.print("Come Back Later ");
    lcd.setCursor ( 0, 1 );            // go to the 2nd row
    lcd.print(" [Doorbell Off] ");
  }
}

void ledOff() { //Turning off all Actual Sign LEDs aside from the RGB LEDs
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
}

void cLedOff(){ //Turning off only RGB LED pins
  digitalWrite(redCLed, LOW);
  digitalWrite(greenCLed, LOW);
  digitalWrite(blueCLed, LOW);
}

void bootSequence(){
  digitalWrite(redLed, HIGH); //Sequence 1
  digitalWrite(redCLed, HIGH);
  delay(bootDelay);
  
  ledOff();
  cLedOff();
  
  digitalWrite(yellowLed, HIGH); //Sequence 2
  digitalWrite(redCLed, HIGH);
  digitalWrite(greenCLed, HIGH);
  digitalWrite(blueCLed, HIGH);
  delay(bootDelay);  

  ledOff();
  cLedOff();

  digitalWrite(greenLed, HIGH);
  digitalWrite(greenCLed, HIGH);
  delay(bootDelay);

  ledOff();
  cLedOff();

  digitalWrite(blueLed, HIGH);
  digitalWrite(blueCLed, HIGH);
  delay(bootDelay);

  ledOff();
  cLedOff();
}
