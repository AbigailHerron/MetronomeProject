// THIS PROGRAM IS A TEST - TRYING TO GET THE TIMING INTERVAL BETWEEN TWO SOUNDS USING MILLIS()
/*After some research on how C++ works (bare in mind, I have no C++ knowledge), I have updated this test so
  that it actually works.
  
  CHANGES MADE: 
  1)  Removed the MIC sensor (just need to know if millis() works)
              -  Also removed all assosiated variables
              
  2)  Removed Serial.begin(9600) - I'll be honest, even after researching this, I still don't know what it does.
      I think it deals with how many bits of data are processed per second - in relation to the console, as in
      how quickly information is printed to the screen.
      
  3)  Moved the time-recording section to a new function - GetDelay()*/

// declare constants for the pin locations
const int LED = 7; // digital output pin 7


// declaring variables
unsigned long t1; // takes first time-stamp using millis()
unsigned long t2; // records the differents between the first time-stamp (t1) and the current millis()



void setup() {
  pinMode(LED, OUTPUT); // this is making the LED an output devide in the program
  GetDelay(); // setting up the timing delay here since the function only needs to run once
}



void loop() {
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(t2);
}



// GetDelay() assigns the delay to variable t2
unsigned long GetDelay()
{
  t1 = millis();
  delay(350); // I'm not sure how long this is, I know it's more than a 1/4 second and less than 1/2 a second
  t2 = t1 - millis();
  return t2;
}
