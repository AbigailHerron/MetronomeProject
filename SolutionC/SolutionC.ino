// THIS IS A POSSIBLE SOLUTION TO METRONOME PROBLEM - THIS SHOULD RUN
/*NOTES:
 * This is almost identical to Solution B.
 
   Problem faced with Solution B is that, despite the initial recording portion displaying correctly,
   the tempo did not update.
   
   As the recording section DOES start with two LED blips and ends with two LED blips, the millis() countdown
   section of GetBeat() is operational.

   This leads to the conclution that beatDelay is not recording the correct value.  Possible solution, as made in
   Solution C, is to TYPE CAST the initial analogRead(MIC) (which reats as an int) to unsigned long.

   As an added measure, the value of c at the end of GetBeat() is also TYPE CAST to unsigned long to ensure that the
   correct data type is passed into the temp delay() section, as delay() will ONLY ACCEPT VALUES of type unsigned long.
   */

// Declaring Variables and Constants
  // Declaring pins
const int LED = 7;
const int MIC = A0; // 1) NOTE: if MIC is a digital input, replace line with: const int MIC = 13

  // Declaring sound threshold here
const int THRESHOLD = 0;  // 2) NOTE: if MIC is digital, replace line with: const string THRESHOLD = "HIGH";
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
    unsigned long val = (unsigned long)analogRead(MIC); // 4) NOTE: if MIC is digital, replace line with: unsigned long val = digitalRead(MIC);
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
unsigned long GetBeats(unsigned long val) // 5) NOTE: if MIC is digital, replace line with: int GetBeats(string sound);
{
  a = millis(); // Getting initial time here so it doesn't update within the loop
  
  while(b < 6000) // Until 6 seconds have passed
  {
    if(val > THRESHOLD) // 6) NOTE: if MIC is digital, replace line with: if(sound == THRESHOLD)
    {
      beat++; // increments the number of beats
    }// end if

    val = (unsigned long)analogRead(MIC); // 7) NOTE: if MIC is digital, replace line with: val = (unsigned long)digitalRead(MIC);
    b = millis() - a; // this will update the length of time stored in b
  }// end while

  // updating beats to match a minutes worth
  beat = beat * 10;

  c = (unsigned long)(MINUTE / beat);

  return c;
  
}// end GetBeats()
