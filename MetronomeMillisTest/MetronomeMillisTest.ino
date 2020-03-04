// THIS PROGRAM IS A TEST - TRYING TO GET THE TIMING INTERVAL BETWEEN TWO SOUNDS USING MILLIS()

// declare constants for the pin locations
const int LED = 7; // digital output pin 7
const int MIC = A0; // analogue input pin A0


// declaring variables
int beatCount = 0;
unsigned long t;

void setup() {
  Serial.begin(9600); // sets the pin mode for the analog MIC 
  pinMode(LED, OUTPUT); // this is making the LED an output devide in the program
}

void loop() {

  // finding the time interval between two beats
//---------------------------------------------------------------------
  while(beatCount != 2)
  {
    if(analogRead(MIC) > 500) // the 500 may have to be raised or lowered depending on how noisy the room is
    {
      t = millis(); // records the time-stamp the first sound is made
      beatCount++; // increases the beatCount if a successful sound is recorded
    }
  }
  t = millis() - t; // takes the previous time-stamp away from the current time-stamp
 //---------------------------------------------------------------------
  
  digitalWrite(LED, HIGH);
  delay(250);
  digitalWrite(LED, LOW);
  delay(t - 250);
}
