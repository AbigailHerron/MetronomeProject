// THIS IS A POSSIBLE SOLUTION TO METRONOME PROBLEM - THIS SHOULD RUN
/*NOTES:
 * This is almost identical to Solution B: CHANGES BELOW
 * 
 * 1) Moved the initial setup of beatDelay to the setup() as it only runs once.
 * 
 * 2) Put the initial blinking LED to indicate Start and Stop recording into the GetBeat() function.
 * 
 * 3) Declared int val and unsigned long beatDelay before either setup() or loop() functions
 *  */

// Declaring Variables and Constants
  // Declaring pins
const int LED = 7;
const int MIC = A0; // 1) NOTE: if MIC is a digital input, replace line with: const int MIC = 13

  // Declaring sound threshold here
const int THRESHOLD = 0;  // 2) NOTE: if MIC is digital, replace line with: const string THRESHOLD = "HIGH";


  // Declaring millisecond variables
unsigned long a; // time-stamp at start
unsigned long b; // updates as GetBeats() runs
unsigned long c; // is the returned length between each beat in a minute
unsigned long minute = 60000; // there are 60 thousand milliseconds in a minute
unsigned long beatDelay = 0;

  // Declaring beat counter
int beat = 0;
int val = 0;


void setup() {

  // Setting up Pins
  pinMode(LED, OUTPUT);
  Serial.begin(9600); // 3) NOTE: if MIC is digital, replace line with: pinMode(MIC, INPUT);

  // only want to run this while no beats have been recorded
  if(beat == 0)
  {
    val = analogRead(MIC); // 4) NOTE: if MIC is digital, replace line with: unsigned long val = digitalRead(MIC);
    beatDelay = GetBeats(val);
 
    delay(3000);     // 3 second delay before the LED starts repeating the recorded interval in loop()
  } // end of if() - end of recording beats

}// end setup()




// Running the Program
void loop() {
  // LED begins blinking to tempo
  digitalWrite(LED, HIGH);
  delay(250); // LED shoudl be on for a quater of a second
  digitalWrite(LED, LOW);
  delay(beatDelay - 250);
}// end loop()




// CALCULATES HOW MANY BEATS THERE ARE IN A MINUTE BASED ON THE INPUT OF THE MIC
unsigned long GetBeats(int sound) // 5) NOTE: if MIC is digital, replace line with: int GetBeats(string sound);
{
  // Two LED blips before recording
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);

  
  a = millis(); // Getting initial time here so it doesn't update within the loop
  
  while(b < 6000) // Until 6 seconds have passed
  {
    if(sound > THRESHOLD) // 6) NOTE: if MIC is digital, replace line with: if(sound == THRESHOLD)
    {
      beat++; // increments the number of beats
    }// end if

    sound = analogRead(MIC); // 7) NOTE: if MIC is digital, replace line with: sound = (unsigned long)digitalRead(MIC);
    b = millis() - a; // this will update the length of time stored in b
  }// end while

  // Two LED blips after recording
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);  

  // updating beats to match a minutes worth
  beat = beat * 10;

  c = minute / beat;

  return c;
}// end GetBeats()
