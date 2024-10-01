//Variables that can be changed by user
int maxNumberValues = 20; //***BE SURE TO CHANGE THE ARRAY CAPACITY IF THIS VALUE IS CHANGED***//
int tolerance = 25;//***********

//Variables used in calculations
int numberValuesInput;
int index;
float average;
int averageMinus;
int averagePlus;
//***********

//Values Array
int values[21];
//***********

//LDR Analog Input variables
int ldrPin = A0;
int newValue;
//***********

//Other variables
int led = 3;
int button = 13;
bool alarm = false;
//***********

void setup() {
  Serial.begin(9600);
  Serial.println("Initialized");

  pinMode(ldrPin, INPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  if (alarm == false) {
    newValue = analogRead(ldrPin); //Getting value from LDR sensor
    averageSurveillance();
  }

  if (alarm == true) {
    if (digitalRead(button) == LOW) {
      alarm = false;
      digitalWrite(led, LOW);
    }
  }
}

void averageSurveillance() {
  averageMinus = average - tolerance; //Replace the 50 with the tolerance variable
  averagePlus = average + tolerance; //Replace the 50 with the tolerance variable

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
      for (index = 0; index < maxNumberValues; ++index) { //Initializer: sets variable "index" to 0; Condition: index is less than maxNumberValues;
        values[index] = 0;
      }
      numberValuesInput = 0;
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
    digitalWrite(led, HIGH);
  }
}
