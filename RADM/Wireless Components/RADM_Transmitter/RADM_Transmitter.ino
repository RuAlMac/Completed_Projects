//RADM Transmitter Code

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8);  // CE, CSN

const byte address[6] = "RADM1";

int dStatus[2];
int door1 = 6;
int door2 = 4;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH); //MIN, LOW, or HIGH
  radio.stopListening(); //TRANSMITTER

  pinMode(door1, INPUT_PULLUP);
  pinMode(door2, INPUT_PULLUP);
}
void loop() {

  if (digitalRead(door1) == LOW) {
    dStatus[0] = 1;
    Serial.println(dStatus[0]);
    radio.write(&dStatus[0], 1);
    delay(100); //Should be set to 250 so updates are transmitted every 0.25 seconds, OR should be deleted altogether
  }
  else if (digitalRead(door1) == HIGH) {
    dStatus[0] = 2;
    Serial.println(dStatus[0]);
    radio.write(&dStatus[0], 1);
    delay(100);
  }

  delay(250);

  if (digitalRead(door2) == LOW) {
    dStatus[1] = 1;
    Serial.println(dStatus[1]);
    Serial.println("-");
    radio.write(&dStatus[1], 1);
    delay(100);
  }
  else if (digitalRead(door2) == HIGH) {
    dStatus[1] = 2;
    Serial.println(dStatus[1]);
    Serial.println("-");
    radio.write(&dStatus[1], 1);
    delay(100);
  }
}
