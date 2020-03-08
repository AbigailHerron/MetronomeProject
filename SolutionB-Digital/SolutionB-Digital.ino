// THIS IS A POSSIBLE SOLUTION TO METRONOME PROBLEM - THIS SHOULD RUN
/*NOTES:
 * The only difference between Solution B and Solution B - Digital is that the MIC pin has been changed from
   Analoge to Digital*/

// Declaring Variables and Constants
  // Declaring pins
const int LED = 7; // Place LED in pin 7 please
const int MIC = 9; // Place MIC sensor in pin 9 please

  // Declaring sound threshold here
const int THRESHOLD = 0;


  // Declaring millisecond variables
unsigned long a; // time-stamp at start
unsigned long b; // updates as GetBeats() runs
unsigned long c; // is the returned length between each beat in a minute
unsigned long minute = 60000; // there are 60 thousand milliseconds in a minute

  // Declaring beat counter
int beat = 0;


// Setting up Pins
void setup() {
  pinMode(MIC, INPUT);
  pinMode(LED, OUTPUT);
}// end setup()




// Running the Program
void loop() {

  // only want to run this while no beats have been recorded
  if(beat == 0)
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

    
    // declaring val and beatDelay variables (local to loop only)
    unsigned long val = digitalRead(MIC);
    unsigned long beatDelay = GetBeats(val);


    // Two LED blips after recording
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(3000);     // 3 second delay before the LED starts repeating the recorded interval
  } // end of if() - end of recording beats


  // LED begins blinking to tempo
  digitalWrite(LED, HIGH);
  delay(250); // LED shoudl be on for a quater of a second
  digitalWrite(LED, LOW);
  delay(beatDelay - 250);
}// end loop()




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

  c = minute / beat;

  return c;
  
}// end GetBeats()