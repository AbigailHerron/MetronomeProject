// THIS IS A POSSIBLE SOLUTION TO METRONOME PROBLEM - THIS SHOULD RUN
/*NOTES:
 * 1) Continuing forward with millis() as the measurement used is in milliseconds, which is consistent
  with the delay() fuction, also measured in milliseconds.
  
  2) Clock() revolves around clocks per cycle which makes it incompatible with delay() when used raw - would
  have to incorperate CLOCKS_PER_SEC, thus making the program more complicated

  3) Was unsure if the MIC input pin was going to be Analogue or Digital.  For now, it is set to Analogue

  4) Included a constant called THRESHOLD to hold the sound value.  If this needs tweaking, change the value
     of the constant - this will update throughout the rest of the program automatically
  
  5) Creating a function to calculate beats per minute as this gives a better METRONOME rhythm than the
  random length of time between two beats, and thus better for actually keeping a musical beat*/

// Declaring Variables and Constants
  // Declaring pins
const int LED = 7;  // Place LED in pin 7 please
const int MIC = A0; // Place MIC in pin A0 please

  // Declaring sound threshold here
const int THRESHOLD = 0; // feel free to raise this value if MIC is picking up background noise
const unsigned long MINUTE = 60000; // there are 60 thousand milliseconds in a minute

  // Declaring millisecond variables
unsigned long a; // time-stamp at start
unsigned long b; // updates as GetBeats() runs
unsigned long c; // is the returned length between each beat in a minute

  // Declaring beat counter
int beat = 0;
int val = 0;


// Setting up Pins
void setup() {
  pinMode(MIC, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);  // Unsure whether this is necessary or not...
}




// Running the Program
void loop() {

  // only want to run this while no beats have been recorded
  if(beat == 0)
  {
    // declaring val variable (local to loop only)
    val = analogRead(MIC);
    GetBeats(val);
  }

  digitalWrite(LED, HIGH);
  delay(250); // LED shoudl be on for a quater of a second
  digitalWrite(LED, LOW);
  delay(c);
}




// CALCULATES HOW MANY BEATS THERE ARE IN A MINUTE BASED ON THE INPUT OF THE MIC
void GetBeats(int sound)
{
  a = millis(); // Getting initial time here so it doesn't update within the loop
  
  while(b < 6000) // Until 6 seconds have passed
  {
    if(sound > THRESHOLD)
    {
      beat++; // increments the number of beats
    }// end if

    sound = analogRead(MIC);
    b = millis() - a; // this will update the length of time stored in b
  }// end while

  // updating beats to match a minutes worth
  beat = beat * 10;

  // avoiding 'division by 0' errors
  if(beat == 0)
  {
    beat++;
  }


  c = MINUTE / beat;

  
}// end GetBeats()
