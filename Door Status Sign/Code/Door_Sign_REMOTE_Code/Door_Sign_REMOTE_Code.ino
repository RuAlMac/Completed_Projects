//REMOTE CODE
#include <SPI.h> //2.0 Additions (Libraries)
#include <nRF24L01.h>
#include <RF24.h>

#include <Wire.h> //LCD Screen Libraries
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

#include "pitches.h"
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};

RF24 radio(9, 8);

int availableSetting[2];
bool doorbellSetting[2];
const byte address[6] = "ALARM";

int buttonDelay = (150);

int redButton = 22;
int yellowButton = 23;
int greenButton = 24;
int blueButton = 25;

int sleepSwitch = 44;

int redLed = 30;

int redCLed = 40;
int greenCLed = 31;
int blueCLed = 32;

int buzzer = 7;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH); //MIN, LOW, or HIGH
  radio.stopListening();

  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight

  pinMode(redButton, INPUT_PULLUP);
  pinMode(yellowButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);

  pinMode(redLed, OUTPUT);

  pinMode(redCLed, OUTPUT);
  pinMode(greenCLed, OUTPUT);
  pinMode(blueCLed, OUTPUT);

  pinMode(buzzer, OUTPUT);

//  pinMode(sleepSwitch, INPUT_PULLUP);
}

void loop() {
    radio.openReadingPipe(0, address);
    radio.startListening();

    if (radio.available()) {

      radio.read(&doorbellSetting[0], sizeof(doorbellSetting[0]));

      Serial.println(doorbellSetting[0]);

      if (doorbellSetting[0] == true) {
        digitalWrite(redLed, HIGH);
        playDoorbell();
        digitalWrite(redLed, LOW);
        doorbellSetting[0] == false;
      }
    }

    //Switching to Transmitter Mode:

    if (digitalRead(redButton) == LOW) {
      radio.stopListening();
      availableSetting[0] = 1;
      delay(buttonDelay);
      radio.write(&availableSetting[0], 1);
      updateUI();
    }

    if (digitalRead(yellowButton) == LOW) {
      radio.stopListening();
      availableSetting[0] = 2;
      delay(buttonDelay);
      radio.write(&availableSetting[0], 1);
      updateUI();
    }

    if (digitalRead(greenButton) == LOW) {
      radio.stopListening();
      availableSetting[0] = 3;
      delay(buttonDelay);
      radio.write(&availableSetting[0], 1);
      updateUI();
    }

    if (digitalRead(blueButton) == LOW) {
      radio.stopListening();
      availableSetting[0] = 4;
      delay(buttonDelay);
      radio.write(&availableSetting[0], 1);
      updateUI();
    }

    Serial.println(availableSetting[0]);
}

void updateUI() {
  if (availableSetting[0] == 1) {
    lcd.setCursor ( 0, 0 );            // go to the top left corner
    lcd.print("Mode: Do Not Dis");
    lcd.setCursor ( 0, 1 );            // go to the 2nd row
    lcd.print(" [Doorbell Off] ");

    digitalWrite(redCLed, HIGH);
    digitalWrite(greenCLed, LOW);
    digitalWrite(blueCLed, LOW);
  }

  if (availableSetting[0] == 2) {
    lcd.setCursor ( 0, 0 );            // go to the top left corner
    lcd.print(" Mode: Working  ");
    lcd.setCursor ( 0, 1 );            // go to the 2nd row
    lcd.print(" [Doorbell On]  ");

    digitalWrite(redCLed, HIGH);
    digitalWrite(greenCLed, HIGH);
    digitalWrite(blueCLed, LOW);
  }

  if (availableSetting[0] == 3) {
    lcd.setCursor ( 0, 0 );            // go to the top left corner
    lcd.print("Mode: Available ");
    lcd.setCursor ( 0, 1 );            // go to the 2nd row
    lcd.print(" [Doorbell On]  ");

    digitalWrite(redCLed, LOW);
    digitalWrite(greenCLed, HIGH);
    digitalWrite(blueCLed, LOW);
  }

  if (availableSetting[0] == 4) {
    lcd.setCursor ( 0, 0 );            // go to the top left corner
    lcd.print(" Mode: Not Here ");
    lcd.setCursor ( 0, 1 );            // go to the 2nd row
    lcd.print(" [Doorbell Off] ");

    digitalWrite(redCLed, LOW);
    digitalWrite(greenCLed, LOW);
    digitalWrite(blueCLed, HIGH);
  }
}

void playDoorbell() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(buzzer, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(buzzer);
  }
}
