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

int input = 8;

void setup() {
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

  pinMode(input, INPUT_PULLUP);
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

void loop() {
  if (digitalRead(input) == LOW) {
    delay(100);
    //****INDEX #:1
    digitalWrite(Et, HIGH);

    digitalWrite(Fb, HIGH);

    delay(160);

    lightsOff();


    //****INDEX #:2
    digitalWrite(Et, HIGH);

    digitalWrite(Fb, HIGH);

    delay(190);

    lightsOff();

    //****INDEX #:3
    digitalWrite(Et, HIGH);

    digitalWrite(Fb, HIGH);

    delay(280);

    lightsOff();

    //****INDEX #:4
    digitalWrite(Ct, HIGH);

    digitalWrite(Fb, HIGH);

    delay(240);

    lightsOff();

    //****INDEX #:5
    digitalWrite(Et, HIGH);

    digitalWrite(Fb, HIGH);

    delay(330);

    lightsOff();

    //****INDEX #:6
    digitalWrite(Gt, HIGH);

    digitalWrite(Gb, HIGH);

    delay(270);

    lightsOff();

    //****INDEX #:7
    digitalWrite(Gt, HIGH);

    digitalWrite(Gb, HIGH);

    delay(560);

    lightsOff();

    //****INDEX #:8
    digitalWrite(Ct, HIGH);

    digitalWrite(Gb, HIGH);

    delay(610);

    lightsOff();

    //****INDEX #:9
    digitalWrite(Gt, HIGH);

    digitalWrite(Eb, HIGH);

    delay(470);

    lightsOff();

    //****INDEX #:10
    digitalWrite(Et, HIGH);

    digitalWrite(Cb, HIGH);

    delay(410);

    lightsOff();

    //****INDEX #:11
    digitalWrite(At, HIGH);
    digitalWrite(Ft, HIGH);

    //NO BASS NOTES for this note

    delay(400);

    lightsOff();

    //****INDEX #:12
    digitalWrite(Bt, HIGH);
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(390);

    lightsOff();

    //****INDEX #:13
    digitalWrite(Bt, HIGH);
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(250);

    lightsOff();

    //****INDEX #:14
    digitalWrite(At, HIGH);
    digitalWrite(Ft, HIGH);

    //NO BASS NOTES for this note

    delay(370);

    lightsOff();

    //****INDEX #:15
    digitalWrite(Gt, HIGH);

    digitalWrite(Cb, HIGH);

    delay(250);

    lightsOff();

    //****INDEX #:16
    digitalWrite(Et, HIGH);

    digitalWrite(Gb, HIGH);

    delay(200);

    lightsOff();

    //****INDEX #:17
    digitalWrite(Gt, HIGH);

    digitalWrite(Cb, HIGH);

    delay(250);

    lightsOff();

    //****INDEX #:18
    digitalWrite(At, HIGH);
    digitalWrite(Ft, HIGH);

    //NO BASS NOTES for this note

    delay(300);

    lightsOff();

    //****INDEX #:19
    digitalWrite(Ft, HIGH);
    digitalWrite(Dt, HIGH);

    //NO BASS NOTES for this note

    delay(220);

    lightsOff();

    //****INDEX #:20
    digitalWrite(Gt, HIGH);
    digitalWrite(Et, HIGH);

    //NO BASS NOTES for this note

    delay(370);

    lightsOff();

    //****INDEX #:21
    digitalWrite(Et, HIGH);
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(400);

    lightsOff();

    //****INDEX #:22
    digitalWrite(Ct, HIGH);
    digitalWrite(At, HIGH);

    //NO BASS NOTES for this note

    delay(270);

    lightsOff();

    //****INDEX #:23
    digitalWrite(Dt, HIGH);
    digitalWrite(Bt, HIGH);

    //NO BASS NOTES for this note

    delay(140);

    lightsOff();

    //****INDEX #:24
    digitalWrite(Bt, HIGH);
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(600);

    lightsOff();

    //****INDEX #:25
    digitalWrite(Ct, HIGH);

    digitalWrite(Gb, HIGH);

    delay(370);

    lightsOff();

    //****INDEX #:26
    digitalWrite(Gt, HIGH);

    digitalWrite(Eb, HIGH);

    delay(670);

    lightsOff();

    //****INDEX #:27
    digitalWrite(Et, HIGH);

    digitalWrite(Cb, HIGH);

    delay(760);

    lightsOff();

    //****INDEX #:28
    digitalWrite(At, HIGH);
    digitalWrite(Ft, HIGH);

    //NO BASS NOTES for this note

    delay(390);

    lightsOff();

    //****INDEX #:29
    digitalWrite(Bt, HIGH);
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(400);

    lightsOff();

    //****INDEX #:30
    digitalWrite(Bt, HIGH);
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(250);

    lightsOff();

    //****INDEX #:31
    digitalWrite(At, HIGH);
    digitalWrite(Ft, HIGH);

    //NO BASS NOTES for this note

    delay(360);

    lightsOff();

    //****INDEX #:32
    digitalWrite(Gt, HIGH);

    digitalWrite(Cb, HIGH);

    delay(250);

    lightsOff();

    //****INDEX #:33
    digitalWrite(Et, HIGH);

    digitalWrite(Gb, HIGH);

    delay(140);

    lightsOff();

    //****INDEX #:34
    digitalWrite(Gt, HIGH);

    digitalWrite(Cb, HIGH);

    delay(240);

    lightsOff();

    //****INDEX #:35
    digitalWrite(At, HIGH);
    digitalWrite(Ft, HIGH);

    //NO BASS NOTES for this note

    delay(350);

    lightsOff();

    //****INDEX #:36
    digitalWrite(Ft, HIGH);
    digitalWrite(Dt, HIGH);

    //NO BASS NOTES for this note

    delay(230);

    lightsOff();

    //****INDEX #:37
    digitalWrite(Gt, HIGH);
    digitalWrite(Et, HIGH);

    //NO BASS NOTES for this note

    delay(390);

    lightsOff();

    //****INDEX #:38
    digitalWrite(Et, HIGH);
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(380);

    lightsOff();

    //****INDEX #:39
    digitalWrite(Ct, HIGH);
    digitalWrite(At, HIGH);

    //NO BASS NOTES for this note

    delay(260);

    lightsOff();

    //****INDEX #:40
    digitalWrite(Dt, HIGH);
    digitalWrite(Bt, HIGH);

    //NO BASS NOTES for this note

    delay(150);

    lightsOff();

    //****INDEX #:41
    digitalWrite(Bt, HIGH);
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(600);

    lightsOff();

    //****INDEX #:42
    //NO TREBLE NOTES for this note

    digitalWrite(Cb, HIGH);

    delay(400);

    lightsOff();

    //****INDEX #:43
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(210);

    lightsOff();

    //****INDEX #:44
    digitalWrite(Ft, HIGH);

    digitalWrite(Gb, HIGH);

    delay(240);

    lightsOff();

    //****INDEX #:45
    digitalWrite(Ft, HIGH);

    //NO BASS NOTES for this note

    delay(200);

    lightsOff();

    //****INDEX #:46
    digitalWrite(Et, HIGH);

    //NO BASS NOTES for this note

    delay(150);

    lightsOff();

    //****INDEX #:47
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(220);

    lightsOff();

    //****INDEX #:48
    digitalWrite(Et, HIGH);

    //NO BASS NOTES for this note

    delay(390);

    lightsOff();

    //****INDEX #:49
    //NO TREBLE NOTES for this note

    digitalWrite(Fb, HIGH);

    delay(190);

    lightsOff();

    //****INDEX #:50
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(260);

    lightsOff();

    //****INDEX #:51
    digitalWrite(At, HIGH);

    //NO BASS NOTES for this note

    delay(340);

    lightsOff();

    //****INDEX #:52
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(260);

    lightsOff();

    //****INDEX #:53
    digitalWrite(At, HIGH);

    //NO BASS NOTES for this note

    delay(200);

    lightsOff();

    //****INDEX #:54
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(190);

    lightsOff();

    //****INDEX #:55
    digitalWrite(Dt, HIGH);

    //NO BASS NOTES for this note

    delay(360);

    lightsOff();

    //****INDEX #:56
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(200);

    lightsOff();

    //****INDEX #:57
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(210);

    lightsOff();

    //****INDEX #:58
    digitalWrite(Ft, HIGH);

    digitalWrite(Gb, HIGH);

    delay(200);

    lightsOff();

    //****INDEX #:59
    digitalWrite(Ft, HIGH);

    //NO BASS NOTES for this note

    delay(140);

    lightsOff();

    //****INDEX #:60
    digitalWrite(Et, HIGH);

    //NO BASS NOTES for this note

    delay(250);

    lightsOff();

    //****INDEX #:61
    //NO TREBLE NOTES for this note

    digitalWrite(Cb, HIGH);

    delay(220);

    lightsOff();

    //****INDEX #:62
    digitalWrite(Et, HIGH);

    digitalWrite(Fb, HIGH);

    delay(170);

    lightsOff();

    //****INDEX #:63
    digitalWrite(Ft, HIGH);
    digitalWrite(Ct, HIGH);
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(400);

    lightsOff();

    //****INDEX #:64
    digitalWrite(Ft, HIGH);
    digitalWrite(Ct, HIGH);
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(220);

    lightsOff();

    //****INDEX #:65
    digitalWrite(Ft, HIGH);
    digitalWrite(Ct, HIGH);
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(400);

    lightsOff();

    //****INDEX #:66
    //NO TREBLE NOTES for this note

    digitalWrite(Gb, HIGH);

    delay(380);

    lightsOff();

    //****INDEX #:67
    //NO TREBLE NOTES for this note

    digitalWrite(Cb, HIGH);

    delay(400);

    lightsOff();

    //****INDEX #:68
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(220);

    lightsOff();

    //****INDEX #:69
    digitalWrite(Ft, HIGH);

    digitalWrite(Gb, HIGH);

    delay(190);

    lightsOff();

    //****INDEX #:70
    digitalWrite(Ft, HIGH);

    //NO BASS NOTES for this note

    delay(210);

    lightsOff();

    //****INDEX #:71
    digitalWrite(Et, HIGH);

    //NO BASS NOTES for this note

    delay(210);

    lightsOff();

    //****INDEX #:72
    //NO TREBLE NOTES for this note

    digitalWrite(Cb, HIGH);

    delay(200);

    lightsOff();

    //****INDEX #:73
    digitalWrite(Et, HIGH);

    //NO BASS NOTES for this note

    delay(200);

    lightsOff();

    //****INDEX #:74
    //NO TREBLE NOTES for this note

    digitalWrite(Fb, HIGH);

    delay(180);

    lightsOff();

    //****INDEX #:75
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(200);

    lightsOff();

    //****INDEX #:76
    digitalWrite(At, HIGH);

    //NO BASS NOTES for this note

    delay(200);

    lightsOff();

    //****INDEX #:77
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(430);

    lightsOff();

    //****INDEX #:78
    digitalWrite(At, HIGH);

    //NO BASS NOTES for this note

    delay(170);

    lightsOff();

    //****INDEX #:79
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(260);

    lightsOff();

    //****INDEX #:80
    digitalWrite(Dt, HIGH);

    //NO BASS NOTES for this note

    delay(190);

    lightsOff();

    //****INDEX #:81
    digitalWrite(Et, HIGH);

    digitalWrite(Ab, HIGH);

    delay(340);

    lightsOff();

    //****INDEX #:82
    digitalWrite(Dt, HIGH);

    digitalWrite(Bb, HIGH);

    delay(610);

    lightsOff();

    //****INDEX #:83
    //NO TREBLE NOTES for this note

    //NO BASS NOTES for this note

    delay(590);

    lightsOff();

    //****INDEX #:84
    digitalWrite(Ct, HIGH);
    digitalWrite(Et, HIGH);

    digitalWrite(Cb, HIGH);

    delay(430);

    lightsOff();

    //****INDEX #:85
    //NO TREBLE NOTES for this note

    digitalWrite(Cb, HIGH);

    delay(220);

    lightsOff();

    //****INDEX #:86
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(210);

    lightsOff();

    //****INDEX #:87
    digitalWrite(Ft, HIGH);

    digitalWrite(Gb, HIGH);

    delay(780);

    lightsOff();

    //****INDEX #:88
    digitalWrite(Ft, HIGH);

    //NO BASS NOTES for this note

    delay(400);

    lightsOff();

    //****INDEX #:89
    digitalWrite(Et, HIGH);

    //NO BASS NOTES for this note

    delay(170);

    lightsOff();

    //****INDEX #:90
    //NO TREBLE NOTES for this note

    digitalWrite(Cb, HIGH);

    delay(200);

    lightsOff();

    //****INDEX #:91
    digitalWrite(Et, HIGH);

    //NO BASS NOTES for this note

    delay(230);

    lightsOff();

    //****INDEX #:92
    //NO TREBLE NOTES for this note

    digitalWrite(Fb, HIGH);

    delay(180);

    lightsOff();

    //****INDEX #:93
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(190);

    lightsOff();

    //****INDEX #:94
    digitalWrite(At, HIGH);

    //NO BASS NOTES for this note

    delay(210);

    lightsOff();

    //****INDEX #:95
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(200);

    lightsOff();

    //****INDEX #:96
    digitalWrite(At, HIGH);

    //NO BASS NOTES for this note

    delay(190);

    lightsOff();

    //****INDEX #:97
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(240);

    lightsOff();

    //****INDEX #:98
    digitalWrite(Dt, HIGH);

    //NO BASS NOTES for this note

    delay(360);

    lightsOff();

    //****INDEX #:99
    //NO TREBLE NOTES for this note

    digitalWrite(Cb, HIGH);

    delay(200);

    lightsOff();

    //****INDEX #:100
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(270);

    lightsOff();

    //****INDEX #:101
    digitalWrite(Ft, HIGH);

    digitalWrite(Gb, HIGH);

    delay(190);

    lightsOff();

    //****INDEX #:102
    digitalWrite(Ft, HIGH);

    //NO BASS NOTES for this note

    delay(330);

    lightsOff();

    //****INDEX #:103
    digitalWrite(Et, HIGH);

    //NO BASS NOTES for this note

    delay(220);

    lightsOff();

    //****INDEX #:104
    //NO TREBLE NOTES for this note

    digitalWrite(Cb, HIGH);

    delay(190);

    lightsOff();

    //****INDEX #:105
    digitalWrite(Et, HIGH);

    //NO BASS NOTES for this note

    delay(220);

    lightsOff();

    //****INDEX #:106
    //NO TREBLE NOTES for this note

    digitalWrite(Fb, HIGH);

    delay(190);

    lightsOff();

    //****INDEX #:107
    //NO TREBLE NOTES for this note

    //NO BASS NOTES for this note

    delay(200);

    lightsOff();

    //****INDEX #:108
    //NO TREBLE NOTES for this note

    //NO BASS NOTES for this note

    delay(210);

    lightsOff();

    //****INDEX #:109
    digitalWrite(Ft, HIGH);
    digitalWrite(Gt, HIGH);
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(370);

    lightsOff();

    //****INDEX #:110
    digitalWrite(Ft, HIGH);
    digitalWrite(Gt, HIGH);
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(210);

    lightsOff();

    //****INDEX #:111
    digitalWrite(Ft, HIGH);
    digitalWrite(Gt, HIGH);
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(420);

    lightsOff();

    //****INDEX #:112
    //NO TREBLE NOTES for this note

    digitalWrite(Gb, HIGH);

    delay(380);

    lightsOff();

    //****INDEX #:113
    //NO TREBLE NOTES for this note

    digitalWrite(Cb, HIGH);

    delay(410);

    lightsOff();

    //****INDEX #:114
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(200);

    lightsOff();

    //****INDEX #:115
    digitalWrite(Ft, HIGH);

    digitalWrite(Gb, HIGH);

    delay(210);

    lightsOff();

    //****INDEX #:116
    digitalWrite(Ft, HIGH);

    //NO BASS NOTES for this note

    delay(210);

    lightsOff();

    //****INDEX #:117
    digitalWrite(Et, HIGH);

    //NO BASS NOTES for this note

    delay(190);

    lightsOff();

    //****INDEX #:118
    //NO TREBLE NOTES for this note

    digitalWrite(Cb, HIGH);

    delay(190);

    lightsOff();

    //****INDEX #:119
    digitalWrite(Et, HIGH);

    //NO BASS NOTES for this note

    delay(200);

    lightsOff();

    //****INDEX #:120
    //NO TREBLE NOTES for this note

    digitalWrite(Fb, HIGH);

    delay(200);

    lightsOff();

    //****INDEX #:121
    digitalWrite(Gt, HIGH);

    //NO BASS NOTES for this note

    delay(210);

    lightsOff();

    //****INDEX #:122
    digitalWrite(At, HIGH);

    //NO BASS NOTES for this note

    delay(240);

    lightsOff();

    //****INDEX #:123
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(350);

    lightsOff();

    //****INDEX #:124
    digitalWrite(At, HIGH);

    //NO BASS NOTES for this note

    delay(200);

    lightsOff();

    //****INDEX #:125
    digitalWrite(Ct, HIGH);

    //NO BASS NOTES for this note

    delay(250);

    lightsOff();

    //****INDEX #:126
    digitalWrite(Dt, HIGH);

    //NO BASS NOTES for this note

    delay(270);

    lightsOff();

    //****INDEX #:127
    digitalWrite(Et, HIGH);

    digitalWrite(Ab, HIGH);

    delay(280);

    lightsOff();

    //****INDEX #:128
    digitalWrite(Dt, HIGH);

    digitalWrite(Bb, HIGH);

    delay(590);

    lightsOff();

    //****INDEX #:129
    digitalWrite(Ct, HIGH);
    digitalWrite(Et, HIGH);

    digitalWrite(Cb, HIGH);

    delay(600);

    lightsOff();

    //****INDEX #:130
    digitalWrite(Ct, HIGH);
    digitalWrite(Et, HIGH);

    digitalWrite(Cb, HIGH);

    delay(450);

    lightsOff();

    return;
  }
}
