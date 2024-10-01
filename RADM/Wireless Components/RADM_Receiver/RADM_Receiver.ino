//RADM Receiver Code

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8); // CE, CSN - Note that in the pictures for the MEGA, the CE and CSN are set to 9,10 - 9,8 are fine for final code, just be sure to correct pins to match code

int redLed = 5;
int blueLed = 4;
int d1Status[4];
int d2Status[4];

bool d1Bool = false; //FALSE = OPEN, TRUE = CLOSED
bool d2Bool = false;
bool d1StatusSent = false;
bool d2StatusSent = true;

const byte address[6] = "RADM1";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW); //MIN, LOW, or HIGH
  radio.startListening(); //RECEIVER

  pinMode(redLed, OUTPUT);
}

void loop() {

if (radio.available() && d2StatusSent == true){

  d2StatusSent == false;
  delay(20);

  radio.read(d1Status, 1);
  delay(20);
  
  if (d1Status[0] == 1){ //CLOSED = TRUE
    d1Bool = true;
    Serial.println("Door 1 Closed");
    delay(20);
    digitalWrite(redLed, HIGH);
  }

  if (d1Status[0] == 2){ //OPEN = FALSE
    d1Bool = false;
    Serial.println("Door 1 Open");
    delay(20);
    digitalWrite(redLed, LOW);
  }

  d1StatusSent = true;
  delay(20);
  
}

delay(40);

if (radio.available() && d1StatusSent == true){

  d1StatusSent = false;
  delay(20);
  
  radio.read(d2Status, 1);
  delay(20);
  
  if (d2Status[0] == 1){ //CLOSED = TRUE
    digitalWrite(blueLed, HIGH);
    d2Bool = true;
    Serial.println("Door 2 Closed");
    delay(20);
  }
  
  if (d2Status[0] == 2){ //OPEN = FALSE
    d2Bool = false;
    digitalWrite(blueLed, LOW);
    Serial.println("Door 2 Open");
    delay(20);
  }

  d2StatusSent = true;
  delay(20);
}
}
