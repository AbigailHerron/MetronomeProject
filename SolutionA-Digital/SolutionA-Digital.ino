// THIS IS A POSSIBLE SOLUTION TO METRONOME PROBLEM - THIS SHOULD RUN
/*NOTES:
 * The only difference between Solution A and Solution A-Digital is that the MIC has been switched from Analoge to Digital
   and the removal of Serial.begin(9600).*/

// Declaring Variables and Constants
  // Declaring pins
const int LED = 7;  // Place LED in pin 7 please
const int MIC = 9; // Place MIC in pin 9 please

  // Declaring sound threshold here
const int THRESHOLD = 0; // feel free to raise this value if MIC is picking up background noise
const unsigned long MINUTE = 60000; // there are 60 thousand milliseconds in a minute

  // Declaring millisecond variables
unsigned long a; // time-stamp at start
unsigned long b; // updates as GetBeats() runs
unsigned long c; // is the returned length between each beat in a minute

  // Declaring beat counter
int beat = 0;


// Setting up Pins
void setup() {
  pinMode(MIC, INPUT);
  pinMode(LED, OUTPUT);
}




// Running the Program
void loop() {

  // only want to run this while no beats have been recorded
  if(beat == 0)
  {
    // declaring val variable (local to loop only)
    unsigned long val = digitalRead(MIC);
    unsigned long beatDelay = GetBeats(val);
  }

  digitalWrite(LED, HIGH);
  delay(250); // LED shoudl be on for a quater of a second
  digitalWrite(LED, LOW);
  delay(beatDelay - 250);
}




// CALCULATES HOW MANY BEATS THERE ARE IN A MINUTE BASED ON THE INPUT OF THE MIC
unsigned long GetBeats(unsigned long sound)
{
  a = millis(); // Getting initial time here so it doesn't update within the loop
  
  while(b < 6000) // Until 6 seconds have passed
  {
    if(sound > THRESHOLD)
    {
      beat++; // increments the number of beats
    }// end if

    sound = digitalRead(MIC);
    b = millis() - a; // this will update the length of time stored in b
  }// end while

  // updating beats to match a minutes worth
  beat = beat * 10;

  c = MINUTE / beat;

  return c;
  
}// end GetBeats()