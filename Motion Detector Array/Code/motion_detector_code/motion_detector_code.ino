int led1 = 7;
int led2 = 6;
int led3 = 5;
int led4 = 4;

int sensor1 = 12;
int sensor2 = 11;
int sensor3 = 10;
int sensor4 = 9;


void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(sensor1) == HIGH) {
    digitalWrite(led1, HIGH);
  }

  if (digitalRead(sensor1) == LOW) {
    digitalWrite(led1, LOW);
  }


  if (digitalRead(sensor2) == HIGH) {
    digitalWrite(led2, HIGH);
  }

  if (digitalRead(sensor2) == LOW) {
    digitalWrite(led2, LOW);
  }


  if (digitalRead(sensor3) == HIGH) {
    digitalWrite(led3, HIGH);
  }

  if (digitalRead(sensor3) == LOW) {
    digitalWrite(led3, LOW);
  }


  if (digitalRead(sensor4) == HIGH) {
    digitalWrite(led4, HIGH);
  }

  if (digitalRead(sensor4) == LOW) {
    digitalWrite(led4, LOW);
  }  
}
