// THIS IS A POSSIBLE SOLUTION TO METRONOME PROBLEM - THIS SHOULD RUN
/*NOTES:
 * This is almost identical to Solution B: CHANGES BELOW
 * 
 * 1) Moved the initial setup of beatDelay to the setup() as it only runs once.
 * 
 * 2) Put the initial blinking LED to indicate Start and Stop recording into the GetBeat() function.
 * 
 * 3) Declared int val before either setup() or loop() functions
 * 
 * 4) Deleted beatDelay - changed GetBeat() to type VOID and had it update variable c instead
 * 
 * 5) Returned MINUTE to a constant, included the time we want the LED to stay on as the constant LED_BLINK
 * 
 * 6) Passed variable c to delay instead of beatDelay, updated the time of variable c to include the loss of LED_BLINK length
 *    so that the tempo delay() wouldn't have to perform a calculation inside it
 *    
 * 7) Removed Serial.begin(9600) and replaced it with pinMode(MIC, INPUT)*/

// Declaring Variables and Constants
  // Declaring pins
const int LED = 7;
const int MIC = A0; // 1) NOTE: if MIC is a digital input, replace line with: const int MIC = 13

  // Declaring sound threshold here
const int THRESHOLD = 0;  // 2) NOTE: if MIC is digital, replace line with: const string THRESHOLD = "HIGH";


const unsigned long LED_BLINK = 250;  // Declaring LED ON length here
const unsigned long MINUTE = 60000;  // there are 60 thousand milliseconds in a minute


  // Declaring millisecond variables
unsigned long a; // time-stamp at start
unsigned long b; // updates as GetBeats() runs (new time-stamp minus a (old time-stamp))
unsigned long c; // is the returned length between each beat in a minute

  // Declaring beat counter
int beat = 0;
int val = 0;


void setup() {

  // Setting up Pins
  pinMode(MIC, INPUT); 
  pinMode(LED, OUTPUT);
  
  // only want to run this while no beats have been recorded
  if(beat == 0)
  {
    val = analogRead(MIC); // 3) NOTE: if MIC is digital, replace line with: unsigned long val = digitalRead(MIC);
    GetBeats(val);
 
    delay(3000);     // 3 second delay before the LED starts repeating the recorded interval in loop()
  } // end of if() - end of recording beats

}// end setup()




// Running the Program
void loop() {
  // LED begins blinking to tempo
  digitalWrite(LED, HIGH);
  delay(250); // LED shoudl be on for a quater of a second
  digitalWrite(LED, LOW);
  delay(c);
}// end loop()




// CALCULATES HOW MANY BEATS THERE ARE IN A MINUTE BASED ON THE INPUT OF THE MIC
void GetBeats(int sound) // 4) NOTE: if MIC is digital, replace line with: int GetBeats(string sound);
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
    if(sound > THRESHOLD) // 5) NOTE: if MIC is digital, replace line with: if(sound == THRESHOLD)
    {
      beat++; // increments the number of beats
    }// end if

    sound = analogRead(MIC); // 6) NOTE: if MIC is digital, replace line with: sound = (unsigned long)digitalRead(MIC);
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

  c = (MINUTE / beat) - LED_BLINK;
}// end GetBeats()
