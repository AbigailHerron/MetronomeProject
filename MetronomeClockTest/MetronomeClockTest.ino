// THIS PROGRAM IS A TEST - TRYING TO GET THE TIMING INTERVAL BETWEEN TWO SOUNDS USING CLOCK()

/* Now that more research on C++ has been done, the changes made to this test are done in the hopes that it
   will actually run this time.
   Source of information: https://www.programiz.com/cpp-programming/library-function/ctime/clock

   
   CHANGES MADE:
   
   1) Removed the MIC sensor as the test only requires the LED (testing the clock() and associated functions
      to see whether it is better / easier to use than the millis())
      
   2) Moved the timing section to a new function: GetDelay()*/


// need to import Ctime header file in order for clock() to work
#include <ctime>


// declare constants for the pin locations
const int LED = 7; // digital output pin 7

// declaring variables
 clock_t t1;
 clock_t t2;
 unsigned long timing;



void setup() {
  pinMode(LED, OUTPUT);
  GetDelay();  // calling the function here as it only needs to run once
}



void loop() {
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(timing);
}

unsigned long GetDelay();
{
  t1 = clock();
  delay(350);
  t2 = clock() - t1;
  
  timing = t2 / CLOCKS_PER_SEC;
  return timing;  
}
