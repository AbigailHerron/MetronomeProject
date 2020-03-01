// THIS PROGRAM DOESN'T FUNCTION - IT'S A LOGIC FLOW EXPLANATION

// inport the right libraries
// something to do with time
// something to do with recording



// declare constants for the pin locations
const int LED = 7; // digital output pin 7
const int MIC = A0; // analogue input pin A0
const int SOUND_THRESHOLD = 1000; // to limit the sensitivity of the microphone (don't want background noise interfearing with the beat)
// declare variables that will need to be setup and reused
int beat = 0;
int beatsPerMinute = 0;
int beatDelay = 0;


void setup() {
  // set up pin modes
  // use timingFunction() on MIC serialInput() to set timing variable value
}

void loop() {
  // have LED blink at previously set interval
  // use digitalWrite(LED, HIGH), delay(quater of a second), digitalWrite(LED, LOW), delay(timing value - quater of a second)
}


// create timing function(int)
int timingFunction() { // int because it returns an int value
  /* while(countdown != 6){
   *  if(MIC INPUT > SOUND_THRESHOLD) {
   *    beat++;
   *  }
   * }
   * 
   * beatsPerMinute = beat * 10;
   * 
   * beatDelay = beatsPerMinute / 60;
   * 
   * return beatDelay;
    */
  }
