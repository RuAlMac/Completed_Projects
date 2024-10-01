#include <SD.h>
#include <TMRpcm.h>

#define SD_ChipSelectPin 53

int button = 8;

int At = 28;
int Bt = 29;
int Ct = 30;
int Dt = 31;
int Et = 32;
int Ft = 33;
int Gt = 34;

int Ab = 22;
int Bb = 23;
int Cb = 24;
int Eb = 25;
int Fb = 26;
int Gb = 27;

TMRpcm tmrpcm; //crete an object for speaker library

void setup() {
  Serial.begin(9600);
  tmrpcm.speakerPin = 46;

  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("Fail");
    return;
  }

  tmrpcm.setVolume(5);

  pinMode(button, INPUT_PULLUP);

  pinMode(At, OUTPUT);
  pinMode(Bt, OUTPUT);
  pinMode(Ct, OUTPUT);
  pinMode(Dt, OUTPUT);
  pinMode(Et, OUTPUT);
  pinMode(Ft, OUTPUT);
  pinMode(Gt, OUTPUT);

  pinMode(Ab, OUTPUT);
  pinMode(Bb, OUTPUT);
  pinMode(Cb, OUTPUT);
  pinMode(Eb, OUTPUT);
  pinMode(Fb, OUTPUT);
  pinMode(Gb, OUTPUT);
}

void loop() {

  if (digitalRead(button) == LOW) {
    part1();
    part2();
    part2();
    part3();
    part3();
  }
}

void lightsOff() {
  digitalWrite(At, LOW);
  digitalWrite(Bt, LOW);
  digitalWrite(Ct, LOW);
  digitalWrite(Dt, LOW);
  digitalWrite(Et, LOW);
  digitalWrite(Ft, LOW);
  digitalWrite(Gt, LOW);

  digitalWrite(Ab, LOW);
  digitalWrite(Bb, LOW);
  digitalWrite(Cb, LOW);
  digitalWrite(Eb, LOW);
  digitalWrite(Fb, LOW);
  digitalWrite(Gb, LOW);
}

void part1() { //******************************************************************

  tmrpcm.play("part1.wav");
  //****INDEX #:1
  digitalWrite(Et, HIGH);

  digitalWrite(Fb, HIGH);

  delay(200);

  lightsOff();

  //****INDEX #:2
  digitalWrite(Et, HIGH);

  digitalWrite(Fb, HIGH);

  delay(400);

  lightsOff();

  //****INDEX #:3
  digitalWrite(Et, HIGH);

  digitalWrite(Eb, HIGH);

  delay(400);

  lightsOff();

  //****INDEX #:4
  digitalWrite(Ct, HIGH);

  digitalWrite(Fb, HIGH);

  delay(270);

  lightsOff();

  //****INDEX #:5
  digitalWrite(Et, HIGH);

  digitalWrite(Fb, HIGH);

  delay(320);

  lightsOff();

  //****INDEX #:6
  digitalWrite(Gt, HIGH);

  digitalWrite(Gb, HIGH);

  delay(810);

  lightsOff();

  //****INDEX #:7
  digitalWrite(Gt, HIGH);

  digitalWrite(Gb, HIGH);

  delay(450);

  lightsOff();

  delay(500);
}

void part2() { //******************************************************************

  tmrpcm.play("part2.wav");
  //****INDEX #:1
  digitalWrite(Ct, HIGH);

  digitalWrite(Gb, HIGH);

  delay(560);

  lightsOff();

  //****INDEX #:2
  digitalWrite(Gt, HIGH);

  digitalWrite(Eb, HIGH);

  delay(610);

  lightsOff();

  //****INDEX #:3
  digitalWrite(Et, HIGH);

  digitalWrite(Cb, HIGH);

  delay(560);

  lightsOff();

  //****INDEX #:4
  digitalWrite(At, HIGH);
  digitalWrite(Ft, HIGH);

  //NO BASS NOTES for this note

  delay(400);

  lightsOff();

  //****INDEX #:5
  digitalWrite(Bt, HIGH);
  digitalWrite(Gt, HIGH);

  //NO BASS NOTES for this note

  delay(410);

  lightsOff();

  //****INDEX #:6
  digitalWrite(Bt, HIGH);
  digitalWrite(Gt, HIGH);

  //NO BASS NOTES for this note

  delay(250);

  lightsOff();

  //****INDEX #:7
  digitalWrite(At, HIGH);
  digitalWrite(Ft, HIGH);

  //NO BASS NOTES for this note

  delay(390);

  lightsOff();

  //****INDEX #:8
  digitalWrite(Gt, HIGH);

  digitalWrite(Cb, HIGH);

  delay(200);

  lightsOff();

  //****INDEX #:9
  digitalWrite(Et, HIGH);

  digitalWrite(Gb, HIGH);

  delay(190);

  lightsOff();

  //****INDEX #:10
  digitalWrite(Gt, HIGH);

  digitalWrite(Cb, HIGH);

  delay(220);

  lightsOff();

  //****INDEX #:11
  digitalWrite(At, HIGH);
  digitalWrite(Ft, HIGH);

  //NO BASS NOTES for this note

  delay(360);

  lightsOff();

  //****INDEX #:12
  digitalWrite(Ft, HIGH);
  digitalWrite(Dt, HIGH);

  //NO BASS NOTES for this note

  delay(230);

  lightsOff();

  //****INDEX #:13
  digitalWrite(Gt, HIGH);
  digitalWrite(Et, HIGH);

  //NO BASS NOTES for this note

  delay(400);

  lightsOff();

  //****INDEX #:14
  digitalWrite(Et, HIGH);
  digitalWrite(Ct, HIGH);

  //NO BASS NOTES for this note

  delay(370);

  lightsOff();

  //****INDEX #:15
  digitalWrite(Ct, HIGH);
  digitalWrite(At, HIGH);

  //NO BASS NOTES for this note

  delay(230);

  lightsOff();

  //****INDEX #:16
  digitalWrite(Dt, HIGH);
  digitalWrite(Bt, HIGH);

  //NO BASS NOTES for this note

  delay(200);

  lightsOff();

  //****INDEX #:17
  digitalWrite(Bt, HIGH);
  digitalWrite(Gt, HIGH);

  //NO BASS NOTES for this note

  delay(190);

  lightsOff();

  delay(500);
}

void part3() { //******************************************************************

  tmrpcm.play("part3.wav");
  //****INDEX #:1
  //NO TREBLE NOTES for this note

  digitalWrite(Cb, HIGH);

  delay(390);

  lightsOff();

  //****INDEX #:2
  digitalWrite(Gt, HIGH);

  //NO BASS NOTES for this note

  delay(200);

  lightsOff();

  //****INDEX #:3
  digitalWrite(Ft, HIGH);

  digitalWrite(Gb, HIGH);

  delay(220);

  lightsOff();

  //****INDEX #:4
  digitalWrite(Ft, HIGH);

  //NO BASS NOTES for this note

  delay(210);

  lightsOff();

  //****INDEX #:5
  digitalWrite(Et, HIGH);

  //NO BASS NOTES for this note

  delay(160);

  lightsOff();

  //****INDEX #:6
  //NO TREBLE NOTES for this note

  digitalWrite(Cb, HIGH);

  delay(190);

  lightsOff();

  //****INDEX #:7
  digitalWrite(Et, HIGH);

  //NO BASS NOTES for this note

  delay(390);

  lightsOff();

  //****INDEX #:8
  //NO TREBLE NOTES for this note

  digitalWrite(Fb, HIGH);

  delay(220);

  lightsOff();

  //****INDEX #:9
  digitalWrite(Gt, HIGH);

  //NO BASS NOTES for this note

  delay(240);

  lightsOff();

  //****INDEX #:10
  digitalWrite(At, HIGH);

  //NO BASS NOTES for this note

  delay(350);

  lightsOff();

  //****INDEX #:11
  digitalWrite(Ct, HIGH);

  //NO BASS NOTES for this note

  delay(250);

  lightsOff();

  //****INDEX #:12
  digitalWrite(At, HIGH);

  //NO BASS NOTES for this note

  delay(200);

  lightsOff();

  //****INDEX #:13
  digitalWrite(Ct, HIGH);

  //NO BASS NOTES for this note

  delay(210);

  lightsOff();

  //****INDEX #:14
  digitalWrite(Dt, HIGH);

  //NO BASS NOTES for this note

  delay(350);

  lightsOff();

  //****INDEX #:15
  //NO TREBLE NOTES for this note

  digitalWrite(Cb, HIGH);

  delay(210);

  lightsOff();

  //****INDEX #:16
  digitalWrite(Gt, HIGH);

  //NO BASS NOTES for this note

  delay(220);

  lightsOff();

  //****INDEX #:17
  digitalWrite(Ft, HIGH);

  digitalWrite(Gb, HIGH);

  delay(190);

  lightsOff();

  //****INDEX #:18
  digitalWrite(Ft, HIGH);

  //NO BASS NOTES for this note

  delay(190);

  lightsOff();

  //****INDEX #:19
  digitalWrite(Et, HIGH);

  //NO BASS NOTES for this note

  delay(200);

  lightsOff();

  //****INDEX #:20
  //NO TREBLE NOTES for this note

  digitalWrite(Cb, HIGH);

  delay(180);

  lightsOff();

  //****INDEX #:21
  digitalWrite(Et, HIGH);

  digitalWrite(Fb, HIGH);

  delay(200);

  lightsOff();

  //****INDEX #:22
  digitalWrite(Ct, HIGH);
  digitalWrite(Ft, HIGH);
  digitalWrite(Gt, HIGH);

  //NO BASS NOTES for this note

  delay(400);

  lightsOff();

  //****INDEX #:23
  digitalWrite(Ct, HIGH);
  digitalWrite(Ft, HIGH);
  digitalWrite(Gt, HIGH);

  //NO BASS NOTES for this note

  delay(200);

  lightsOff();

  //****INDEX #:24
  digitalWrite(Ct, HIGH);
  digitalWrite(Ft, HIGH);
  digitalWrite(Gt, HIGH);

  //NO BASS NOTES for this note

  delay(400);

  lightsOff();

  //****INDEX #:25
  //NO TREBLE NOTES for this note

  digitalWrite(Gb, HIGH);

  delay(410);

  lightsOff();

  //****INDEX #:26
  //NO TREBLE NOTES for this note

  digitalWrite(Cb, HIGH);

  delay(400);

  lightsOff();

  //****INDEX #:27
  digitalWrite(Gt, HIGH);

  //NO BASS NOTES for this note

  delay(200);

  lightsOff();

  //****INDEX #:28
  digitalWrite(Ft, HIGH);

  digitalWrite(Gb, HIGH);

  delay(220);

  lightsOff();

  //****INDEX #:29
  digitalWrite(Ft, HIGH);

  //NO BASS NOTES for this note

  delay(170);

  lightsOff();

  //****INDEX #:30
  digitalWrite(Et, HIGH);

  //NO BASS NOTES for this note

  delay(210);

  lightsOff();

  //****INDEX #:31
  //NO TREBLE NOTES for this note

  digitalWrite(Cb, HIGH);

  delay(190);

  lightsOff();

  //****INDEX #:32
  digitalWrite(Et, HIGH);

  //NO BASS NOTES for this note

  delay(200);

  lightsOff();

  //****INDEX #:33
  //NO TREBLE NOTES for this note

  digitalWrite(Fb, HIGH);

  delay(210);

  lightsOff();

  //****INDEX #:34
  digitalWrite(Gt, HIGH);

  //NO BASS NOTES for this note

  delay(210);

  lightsOff();

  //****INDEX #:35
  digitalWrite(At, HIGH);

  //NO BASS NOTES for this note

  delay(210);

  lightsOff();

  //****INDEX #:36
  digitalWrite(Ct, HIGH);

  //NO BASS NOTES for this note

  delay(380);

  lightsOff();

  //****INDEX #:37
  digitalWrite(At, HIGH);

  //NO BASS NOTES for this note

  delay(210);

  lightsOff();

  //****INDEX #:38
  digitalWrite(Ct, HIGH);

  //NO BASS NOTES for this note

  delay(190);

  lightsOff();

  //****INDEX #:39
  digitalWrite(Dt, HIGH);

  //NO BASS NOTES for this note

  delay(250);

  lightsOff();

  //****INDEX #:40
  digitalWrite(Et, HIGH);

  digitalWrite(Ab, HIGH);

  delay(350);

  lightsOff();

  //****INDEX #:41
  digitalWrite(Dt, HIGH);

  digitalWrite(Bb, HIGH);

  delay(600);

  lightsOff();

  //****INDEX #:42
  digitalWrite(Ct, HIGH);
  digitalWrite(Et, HIGH);

  digitalWrite(Cb, HIGH);

  delay(600);

  lightsOff();

  //****INDEX #:43
  //NO TREBLE NOTES for this note

  //NO BASS NOTES for this note

  delay(290);

  lightsOff();

  delay(500);
}
