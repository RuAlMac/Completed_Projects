#include <SD.h> //include SD module library
#include <TMRpcm.h>
//include speaker control library

#define SD_ChipSelectPin 4 //define CS pin

TMRpcm tmrpcm; //crete an object for speaker library

int button = 3;
int output = 7;

void setup(){
tmrpcm.speakerPin = 9; //define speaker pin.
//you must use pin 9 of the Arduino Uno and Nano
//the library is using this pin

if (!SD.begin(SD_ChipSelectPin)) { //see if the card is present and can be initialized
return; //don't do anything more if not
}

pinMode(button, INPUT_PULLUP);
pinMode(output, OUTPUT);

tmrpcm.setVolume(5); //0 to 7. Set volume level
}
void loop(){
  if (digitalRead(button) == LOW){
    digitalWrite(output, HIGH);
    delay(100);
    digitalWrite(output, LOW);
    tmrpcm.play("test2.wav");
  }
}
