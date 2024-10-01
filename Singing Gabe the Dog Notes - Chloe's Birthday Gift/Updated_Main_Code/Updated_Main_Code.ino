#include <SD.h>
#include <TMRpcm.h>
#include <Servo.h>

#define SD_ChipSelectPin 53

Servo ABtreble;
Servo CDtreble;
Servo Etreble;
Servo Ftreble;
Servo Gtreble;
Servo ABbass;
Servo Cbass;
Servo Ebass;
Servo Fbass;
Servo Gbass;

int button = 8;
int secretButton = 9; //******************REMOVE FROM PRINTED OUT CODE

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

int servoResting = 150;
int servoActive = 120;

int servoDelay = 250;

TMRpcm tmrpcm; //create an object for speaker library

void setup() {

  Serial.begin(9600);
  tmrpcm.speakerPin = 46;

  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("Fail");
    return;
  }

  tmrpcm.setVolume(5);

  pinMode(button, INPUT_PULLUP);
  pinMode(secretButton, INPUT_PULLUP); //******************REMOVE FROM PRINTED OUT CODE

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

  ABtreble.attach(36);
  CDtreble.attach(38);
  Etreble.attach(40);
  Ftreble.attach(42);
  Gtreble.attach(44);
  ABbass.attach(35);
  Cbass.attach(37);
  Ebass.attach(39);
  Fbass.attach(41);
  Gbass.attach(43);

delay(2000);
  resetServos();
}

void loop() {

  if (digitalRead(button) == LOW) {

    part1();
    part2();
    part2();
    part3();
    part3();
    
    resetServos();
  }

  if (digitalRead(9) == LOW) {
    activateServos();

    delay(2000);
    tmrpcm.play("test4.wav");
    delay(37000);

    delay(100);
  }
}

void resetServos() {
  ABtreble.write(servoResting);
  delay(servoDelay);
  CDtreble.write(servoResting);
  delay(servoDelay);
  Etreble.write(servoResting);
  delay(servoDelay);
  Ftreble.write(servoResting);
  delay(servoDelay);
  Gtreble.write(servoResting);
  delay(servoDelay);


  ABbass.write(servoResting);
  delay(servoDelay);
  Cbass.write(servoResting);
  delay(servoDelay);
  Ebass.write(servoResting);
  delay(servoDelay);
  Fbass.write(servoResting);
  delay(servoDelay);
  Gbass.write(servoResting);
  delay(servoDelay);
}

void activateServos() {
  ABtreble.write(servoActive);
  digitalWrite(At, HIGH);
  digitalWrite(Bt, HIGH);
  delay(servoDelay);
  CDtreble.write(servoActive);
  digitalWrite(Ct, HIGH);
  digitalWrite(Dt, HIGH);
  delay(servoDelay);
  Etreble.write(servoActive);
  digitalWrite(Et, HIGH);
  delay(servoDelay);
  Ftreble.write(servoActive);
  digitalWrite(Ft, HIGH);
  delay(servoDelay);
  Gtreble.write(servoActive);
  digitalWrite(Gt, HIGH);
  delay(servoDelay);

  ABbass.write(servoActive);
  digitalWrite(Ab, HIGH);
  digitalWrite(Bb, HIGH);
  delay(servoDelay);
  Cbass.write(servoActive);
  digitalWrite(Cb, HIGH);
  delay(servoDelay);
  Ebass.write(servoActive);
  digitalWrite(Eb, HIGH);
  delay(servoDelay);
  Fbass.write(servoActive);
  digitalWrite(Fb, HIGH);
  delay(servoDelay);
  Gbass.write(servoActive);
  digitalWrite(Gb, HIGH);
  delay(servoDelay);
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

void initialize() {
  digitalWrite(At , HIGH);
  digitalWrite(Bt, HIGH);
  digitalWrite(Ct, HIGH);
  digitalWrite(Dt, HIGH);
  digitalWrite(Et, HIGH);
  digitalWrite(Ft, HIGH);
  digitalWrite(Gt, HIGH);

  digitalWrite(Ab, HIGH);
  digitalWrite(Bb, HIGH);
  digitalWrite(Cb, HIGH);
  digitalWrite(Eb, HIGH);
  digitalWrite(Fb, HIGH);
  digitalWrite(Gb, HIGH);

  tmrpcm.play("part1.wav");

  delay(1000);
}

void part1() { //******************************************************************

  tmrpcm.play("part1.wav");
  //****INDEX #:1
  // Etreble.write(servoActive);
  //Fbass.write(servoActive);

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
  //Ebass.write(servoActive);


  digitalWrite(Et, HIGH);

  digitalWrite(Eb, HIGH);

  delay(400);

  lightsOff();

  //****INDEX #:4

  //CDtreble.write(servoActive);

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

  //Gtreble.write(servoActive);
  //  Gbass.write(servoActive);

  digitalWrite(Gt, HIGH);

  digitalWrite(Gb, HIGH);

  delay(810);

  lightsOff();

  //****INDEX #:7
  digitalWrite(Gt, HIGH);

  digitalWrite(Gb, HIGH);

  delay(450);

  lightsOff();

  delay(750);
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

  //Cbass.write(servoActive);

  digitalWrite(Et, HIGH);

  digitalWrite(Cb, HIGH);

  delay(560);

  lightsOff();

  //****INDEX #:4

  //  ABtreble.write(servoActive);
  //Ftreble.write(servoActive);

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

  delay(750);
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

  //  ABbass.write(servoActive);

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

  delay(750);
}
