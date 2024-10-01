//Variables that can be changed by user
int maxNumberValues = 20; //***BE SURE TO CHANGE THE ARRAY CAPACITY IF THIS VALUE IS CHANGED***//
int tolerance = 50;//***********

//Variables used in calculations
int numberValuesInput;
int numberValuesInput1;
int numberValuesInput2;
int index;
float average;
float average1;
float average2;
int averageMinus;
int averageMinus1;
int averageMinus2;
int averagePlus;
int averagePlus1;
int averagePlus2;
//***********

//Values Array
int values[21];
int values1[21];
int values2[21];
//***********

//LDR Analog Input variables
int ldrPin1 = A0;
int ldrPin2 = A1;
int newValue;
int newValue1;
int newValue2;
//***********

//Variables used for switching active LDR
int activeLdr = 1;
//***********

//Other variables
int led1 = 40;
int led2 = 41;
int button1 = 2;
int button2 = 3;
bool alarm = false;
bool alarm1 = false;
bool alarm2 = false;
//***********

void setup() {
  Serial.begin(9600);
  Serial.println("Initialized");

  pinMode(ldrPin1, INPUT);
  pinMode(ldrPin2, INPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  if (alarm1 == false) {
    newValue = analogRead(ldrPin1); //Getting value from LDR sensor
    averageSurveillance();
  }

  if (alarm1 == true) {
    digitalWrite(led1, HIGH);
    if (digitalRead(button1) == LOW) {
      alarm1 = false;
      digitalWrite(led1, LOW);

      for (index = 0; index < maxNumberValues; ++index) { //Initializer: sets variable "index" to 0; Condition: index is less than maxNumberValues; Increment: increases "index" by one
        values1[index] = 0;
      }
      averageMinus1 = 0;
      averagePlus1 = 0;
      numberValuesInput1 = 0;
      average1 = 0;
    }
  }

  //delay(1000);

  activeLdr = 2;

  if (alarm2 == false) {
    newValue = analogRead(ldrPin2); //Getting value from LDR sensor
    averageSurveillance();
  }

  if (alarm2 == true) {
    digitalWrite(led2, HIGH);
    if (digitalRead(button2) == LOW) {
      alarm2 = false;
      digitalWrite(led2, LOW);

      for (index = 0; index < maxNumberValues; ++index) { //Initializer: sets variable "index" to 0; Condition: index is less than maxNumberValues; Increment: increases "index" by one
        values2[index] = 0;
      }
      averageMinus2 = 0;
      averagePlus2 = 0;
      numberValuesInput2 = 0;
      average2 = 0;
    }
  }

  //  delay(1000);

  activeLdr = 1;

}

void initialVariableConfig() {
  if (activeLdr == 1) {
    numberValuesInput = numberValuesInput1;
    averageMinus = averageMinus1;
    averagePlus = averagePlus1;
    average = average1;

    for (index = 0; index < maxNumberValues; ++index) {
      values[index] = values1[index];
    }
  }

  if (activeLdr == 2) {
    numberValuesInput = numberValuesInput2;
    averageMinus = averageMinus2;
    averagePlus = averagePlus2;
    average = average2;

    for (index = 0; index < maxNumberValues; ++index) {
      values[index] = values2[index];
    }
  }
}

void finalVariableConfig() {
  if (activeLdr == 1) { //newValue, alarm
    numberValuesInput1 = numberValuesInput;
    averageMinus1 = averageMinus;
    averagePlus1 = averagePlus;
    average1 = average;
    alarm1 = alarm;

    for (index = 0; index < maxNumberValues; ++index) {
      values1[index] = values[index];
    }
  }

  if (activeLdr == 2) {
    numberValuesInput2 = numberValuesInput;
    averageMinus2 = averageMinus;
    averagePlus2 = averagePlus;
    average2 = average;
    alarm2 = alarm;

    for (index = 0; index < maxNumberValues; ++index) {
      values2[index] = values[index];
    }
  }
  alarm = false;
}

void averageSurveillance() {
  initialVariableConfig();

  averageMinus = average - tolerance; //Replace the 50 with the tolerance variable
  averagePlus = average + tolerance; //Replace the 50 with the tolerance variable

  if (numberValuesInput == 0) { //This only affects the averageMinus and averagePlus bounds on the very first measurement of the LDR after the board has initialized
    averageMinus = newValue - 50;
    averagePlus = newValue + 50;
  }

  Serial.print("\n");
  Serial.print("ACTIVE LDR: ");
  Serial.print(activeLdr);

  Serial.print("\n");
  Serial.print("averageMinus: ");
  Serial.print(averageMinus);

  Serial.print("\n");
  Serial.print("averagePlus: ");
  Serial.print(averagePlus);

  Serial.print("\n");
  Serial.print("newValue: ");
  Serial.print(newValue);

  if ( (newValue == average) || (numberValuesInput == 0) || ( (newValue > (averageMinus)) && (newValue < (averagePlus)) ) ) {    //IF THE newValue PASSES INSPECTION
    //**********
    Serial.print("\n");
    Serial.print("TRUE: newValue Accepted");

    if ( numberValuesInput == maxNumberValues ) { //If these conditions are true, all values in the array "values" are set to 0
      for (index = 0; index < maxNumberValues; ++index) { //Initializer: sets variable "index" to 0; Condition: index is less than maxNumberValues; Increment: increases "index" by one
        values[index] = 0;
      }
      numberValuesInput = 0;
      averageMinus = 0;
      averagePlus = 0;
      Serial.print("\n");
      Serial.print("***Array Cleared***");
    }

    values[numberValuesInput] = newValue; //Inserts the "newValue" into the array, using "numberValuesInput" as an index
    ++numberValuesInput; //Increases the value of "numberValuesInput" by one
    average = 0.00; //Sets average to 0.00

    for (index = 0; index < maxNumberValues; ++index) {
      average = values[index] + average;
    }

    average = average / numberValuesInput;

    Serial.print("\n");
    Serial.print("numberValuesInput: ");
    Serial.print(numberValuesInput);
    Serial.print("\n");
    Serial.print("Average: ");
    Serial.print(average);
    Serial.print("\n");
    Serial.print("*****************");
    Serial.print("\n");
    //**********
  }

  else {
    Serial.print("\n");
    Serial.print("FALSE: newValue REJECTED");
    Serial.print("\n");
    Serial.print("ALARM ACTIVATED");
    Serial.print("\n");
    Serial.print("*****************");
    Serial.print("\n");
    alarm = true;
  }

  finalVariableConfig();
}
