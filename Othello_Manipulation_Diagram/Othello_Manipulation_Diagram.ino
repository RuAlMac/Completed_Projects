int o1 = 8;
int o2 = 9;
int o3 = 10;
int o4 = 4;

int i1 = 13;
int i2 = 12;
int i3 = 11;

int d1 = 7;
int d2 = 6;
int d3 = 5;

int intrasequenceDelay = 1000;
int intersequenceDelay = 1000;

void setup() {
  pinMode(o1, OUTPUT);
  pinMode(o2, OUTPUT);
  pinMode(o3, OUTPUT);
  pinMode(o4, OUTPUT);

  pinMode(i1, OUTPUT);
  pinMode(i2, OUTPUT);
  pinMode(i3, OUTPUT);

  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);

  delay(20);
  ledProgram();
}

void ledProgram() {
  //Sequence 1: Iago
  digitalWrite(i1, HIGH);
  delay(intrasequenceDelay);

  digitalWrite(i2, HIGH);
  delay(intrasequenceDelay);

  digitalWrite(i3, HIGH);
  delay(intrasequenceDelay);

  ledOff();
  delay(intersequenceDelay);

  //Sequence 2: Othello
  digitalWrite(o1, HIGH);
  delay(intrasequenceDelay);

  digitalWrite(o2, HIGH);
  delay(intrasequenceDelay);

  digitalWrite(o3, HIGH);
  delay(intrasequenceDelay);

  digitalWrite(o4, HIGH);
  delay(intrasequenceDelay);

  ledOff();
  delay(intersequenceDelay);

  //Sequence 3: Desdemona
  digitalWrite(d1, HIGH);
  delay(intrasequenceDelay);

  digitalWrite(d2, HIGH);
  delay(intrasequenceDelay);

  digitalWrite(d3, HIGH);
  delay(intrasequenceDelay);

  ledOff();
  delay(intersequenceDelay);
}

void ledOff() {
  digitalWrite(o1, LOW);
  digitalWrite(o2, LOW);
  digitalWrite(o3, LOW);
  digitalWrite(o4, LOW);

  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);

  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
}

void loop() {}
