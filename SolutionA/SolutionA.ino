// THIS IS A POSSIBLE SOLUTION TO METRONOME PROBLEM - THIS SHOULD RUN
/*NOTES:
 * 1) Continuing forward with millis() as the measurement used is in milliseconds, which is consistent
  with the delay() fuction, also measured in milliseconds.
  
  2) Clock() revolves around clocks per cycle which makes it incompatible with delay() when used raw - would
  have to incorperate CLOCKS_PER_SEC, thus making the program more complicated

  3) Was unsure if the MIC input pin was going to be Analogue or Digital.  For now, it is set to Analogue,
  but comments are placed where and how these lines should be changed if MIC is indeed Digital.
    - Will place the LED in slot 7, and MIC in slot 13 to keep them as far away from each other as possible
      on the Arduino Yun board.
    - Included are 7 listed changes to be made on the off chance MIC is Digital

  4) Included a constant called THRESHOLD to hold the sound value.  If this needs tweaking, change the value
     of the constant - this will update throughout the rest of the program automatically
  
  5) Creating a function to calculate beats per minute as this gives a better METRONOME rhythm than the
  random length of time between two beats, and thus better for actually keeping a musical beat.*/

// Declaring Variables and Constants
  // Declaring pins
const int LED = 7;
const int MIC = A0; // 1) NOTE: if MIC is a digital input, replace line with: const int MIC = 13

  // Declaring sound threshold here
const int THRESHOLD = 500;  // 2) NOTE: if MIC is digital, replace line with: const string THRESHOLD = "HIGH";
const unsigned long MINUTE = 60000; // there are 60 thousand milliseconds in a minute

  // Declaring millisecond variables
unsigned long a; // time-stamp at start
unsigned long b; // updates as GetBeats() runs
unsigned long c; // is the returned length between each beat in a minute

  // Declaring beat counter
int beat = 0;


// Setting up Pins
void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600); // 3) NOTE: if MIC is digital, replace line with: pinMode(MIC, INPUT);

}




// Running the Program
void loop() {
  // declaring val variable (local to loop only)
  unsigned long val = analogRead(MIC); // 4) NOTE: if MIC is digital, replace line with: unsigned long val = digitalRead(MIC);
  unsigned long beatDelay = GetBeats(val);

  digitalWrite(LED, HIGH);
  delay(250); // LED shoudl be on for a quater of a second
  digitalWrite(LED, LOW);
  delay(beatDelay - 250);
}




// CALCULATES HOW MANY BEATS THERE ARE IN A MINUTE BASED ON THE INPUT OF THE MIC
unsigned long GetBeats(int sound) // 5) NOTE: if MIC is digital, replace line with: int GetBeats(string sound);
{
  a = millis(); // Getting initial time here so it doesn't update within the loop
  
  while(b < 60000) // Until 6 seconds have passed
  {
    if(sound > THRESHOLD) // 6) NOTE: if MIC is digital, replace line with: if(sound == THRESHOLD)
    {
      beat++; // increments the number of beats
    }// end if

    sound = analogRead(sound); // 7) NOTE: if MIC is digital, replace line with: sound = digitalRead(sound);
    b = millis() - a; // this will update the length of time stored in b
  }// end while

  // updating beats to match a minutes worth
  beat = beat * 10;

  c = MINUTE / beat;

  return c;
  
}// end GetBeats()
