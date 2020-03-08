// THIS IS A POSSIBLE SOLUTION TO METRONOME PROBLEM - THIS SHOULD RUN
/*NOTES:
 * This is almost identical to Solution B: CHANGES BELOW
 * 
 * 1) Put the initial blinking LED to indicate Start and Stop recording into the GetBeat() function.
 * 
 * 2) Declared int val before either setup() or loop() functions
 * 
 * 3) Deleted beatDelay - changed GetBeat() to type VOID and had it update variable c instead
 * 
 * 4) Returned MINUTE to a constant, included the time we want the LED to stay on as the constant LED_BLINK
 * 
 * 5) Passed variable c to delay instead of beatDelay, updated the time of variable c to include the loss of LED_BLINK length
 *    so that the tempo delay() wouldn't have to perform a calculation inside it
 *    
 * 6) Removed Serial.begin(9600)*/

 

// Declaring Variables and Constants
  // Declaring pins
const int LED = 7;  // Place LED in pin 7 please
const int MIC = A0; // Place MIC sensor in pin A0 please

  // Declaring sound threshold here
const int THRESHOLD = 0;


const unsigned long LED_BLINK = 250;  // Declaring LED ON length here
const unsigned long MINUTE = 60000;  // there are 60 thousand milliseconds in a minute


  // Declaring millisecond variables
unsigned long a; // time-stamp at start
unsigned long b; // updates as GetBeats() runs (new time-stamp minus a (old time-stamp))
unsigned long c; // is the returned length between each beat in a minute (minuse the length of the LED being ON)

  // Declaring beat counter
int beat = 0;
int val = 0;


void setup() {

  // Setting up Pins
  pinMode(MIC, INPUT); 
  pinMode(LED, OUTPUT);
}// end setup()




// Running the Program
void loop() {

 
  // will only start recording the beats if the MIC picks up at least 1 sound 
  while(val <= THRESHOLD)
  {
    val = analogRead(MIC);
  }
  
  if(beat <= 0)
  {
    GetBeats(val);
    delay(3000);     // 3 second delay before the LED starts repeating the recorded interval in loop()
  } // end of if() - end of recording beats

  
  // LED begins blinking to tempo
  digitalWrite(LED, HIGH);
  delay(250); // LED shoudl be on for a quater of a second
  digitalWrite(LED, LOW);
  delay(c);
}// end loop()




// CALCULATES HOW MANY BEATS THERE ARE IN A MINUTE BASED ON THE INPUT OF THE MIC
void GetBeats(int sound)
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
  beat++; // avoiding 'division by 0' errors
  while(b < 6000) // Until 6 seconds have passed
  {
    if(sound > THRESHOLD)
    {
      beat++; // increments the number of beats
    }// end if

    sound = analogRead(MIC);
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
