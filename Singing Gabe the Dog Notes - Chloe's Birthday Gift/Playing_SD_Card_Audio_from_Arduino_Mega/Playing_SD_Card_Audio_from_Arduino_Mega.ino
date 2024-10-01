#include <SD.h> //include SD module library
#include <TMRpcm.h>
//include speaker control library

#define SD_ChipSelectPin 53 //define CS pin

TMRpcm tmrpcm; //crete an object for speaker library

void setup(){
  Serial.begin(9600);
tmrpcm.speakerPin = 46; //define speaker pin.
//you must use pin 9 of the Arduino Uno and Nano, 46 or 11 of the Mega
//the library is using this pin

if (!SD.begin(SD_ChipSelectPin)) { //see if the card is present and can be initialized
Serial.println("Fail");
return; //don't do anything more if not
}

tmrpcm.setVolume(5); //0 to 7. Set volume level
    tmrpcm.play("part1.wav");
}
void loop(){
}
