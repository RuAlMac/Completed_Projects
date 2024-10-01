/* MEGA Pins:
    CE = 9
    CSN = 8
    SCK = 52
    MOSI = 51
    MISO = 50
    NRF24L01+ Documentation: https://nrf24.github.io/RF24/
*/

//RECEIVER CODE
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8);

int led = 7;
int button = 4;

int availableSetting[2];
bool doorbellSetting[2];
const byte address[6] = "ALARM";

void setup() {
  pinMode(led, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW); //MIN, LOW, or HIGH
  radio.startListening(); //RECEIVER

  digitalWrite(13, LOW);
}

void loop() {
  if (radio.available()) {

    radio.read(&availableSetting[0], sizeof(availableSetting[0]));

    if (availableSetting[0] == 1) {
      digitalWrite(led, HIGH);
    }

    if (availableSetting[0] == 2) {
      digitalWrite(led, LOW);
    }
    
    Serial.println(availableSetting[0]);
  }

  if (digitalRead(button) == LOW) {

    doorbellSetting[0] = true;
    
    digitalWrite(13, HIGH);

    //Switching to Transmitter Mode
    radio.openWritingPipe(address);
    radio.stopListening();
    radio.write(&doorbellSetting[0], sizeof(doorbellSetting[0]));

    delay(250);

    //Return to Receiver Mode
    radio.startListening();

    digitalWrite(13, LOW);
  }
}
