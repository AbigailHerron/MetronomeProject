// THIS IS A POSSIBLE SOLUTION TO METRONOME PROBLEM - THIS SHOULD RUN
/*NOTES:
 * This is almost identical to Solution C:  CHANGE MADE = MIC is now digital and all necessary switches to digital have been done*/

 

// Declaring Variables and Constants
  // Declaring pins
const int LED = 7;
const int MIC = 9;

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
  
  // only want to run this while no beats have been recorded
  if(beat == 0)
  {
    val = digitalRead(MIC);
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
void GetBeats(int sound)
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
    if(sound > THRESHOLD)
    {
      beat++; // increments the number of beats
    }// end if

    sound = digitalRead(MIC);
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
