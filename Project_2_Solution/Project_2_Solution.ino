// THIS IS A POSSIBLE SOLUTION TO METRONOME PROBLEM - THIS SHOULD RUN
/*NOTES:
 * This carries on from Project_1_Solution to include the ability to send the Interval data to Google Sheets
 * and to read the last Interval placed on the Google Sheet
 *
 * ADDED: 1) GetLastBeat(), which takes the last recorded interval on Google Sheets and makes that the
 *                          current interval
 *
 * OTHER NOTES: This does compile, and I've put a lot of work into trying to get Google Sheets, Pushingbox and
 *              the Metronome Project on Google Developer to work but who knows if it actually does.  I don't
 *              have an Arduino Yun here to test it out, so I'm just kind of winging it here.*/


// Adding Internet Functionality
#include <Bridge.h>
#include <HttpClient.h>


// Declaring Variables and Constants
  // Declaring pins
const int BUTTON = 9; 
const int LED = 7;
const int MIC = A0;

  // Declaring sound threshold here
const int THRESHOLD = 150;


  // Declaring millisecond variables
unsigned long a; // time-stamp at start
unsigned long b; // updates as GetBeats() runs
unsigned long interval = 0; // is the returned length between each beat in a minute
const unsigned long MINUTE = 60000; // there are 60 thousand milliseconds in a minute

  // Declaring beat counter
int beat = 0;
int val = 0;

  // Declaring Connectivity Variables
char serverName[] = "api.pushingbox.com";
char devid[] = "v9319B7F0AF429A7";
boolean DEBUG = true;


// SETTING UP PINS
void setup() {
  pinMode(MIC, INPUT);
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  
  Serial.begin(9600);
  while(!Serial);  
}// end setup()




// RUNNING THE PROGRAM
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
    val = analogRead(MIC);
    GetBeats(val);

    // Initializing the Client Library
    HttpClient client;

    // Logging 'interval' Data to Google Sheets
    String APIRequest;
    APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid)+ "&IDtag=100" + "&Interval={0}", interval;
    client.get (APIRequest);


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
  delay(200);
  digitalWrite(LED, LOW);
  delay(interval);
}// end loop()




// CALCULATES HOW MANY BEATS THERE ARE IN A MINUTE BASED ON THE INPUT OF THE MIC
void GetBeats(int sound)
{
  a = millis(); // Getting initial time here so it doesn't update within the loop
  while(b < 6000) // Until 6 seconds have passed
  {
    if(sound > THRESHOLD)
    {
      beat++; // increments the number of beats
    }
    if(digitalRead(BUTTON) == HIGH)
    {
      interval = GetLastBeat();
      break;
    }
    sound = analogRead(MIC);
    b = millis() - a; // this will update the length of time stored in b
  }// end while

  // avoiding 'division by 0' error
  if(beat == 0)
  {
    beat++;
  }

  // ensuring that 'interval' doesn't get re-written if the value was requested from Google Sheets
  if(interval == 0)
  {
  interval = (MINUTE / beat) - 200;
  }
}// end GetBeats()




// REQUESTS THE LAST SAVED 'interval' VALUE ON GOOGLE SHEETS
unsigned long GetLastBeat()
{
// Initializing the Client Library
    HttpClient client;
  
  String intervalRequest = "https://sheets.googleapis.com/v4/spreadsheets/858919912724-gcmeice7emiijf9ubpj6fktdcfpk7vvm.apps.googleusercontent.com/values/C2:C2";
  return client.get(intervalRequest);
}// end GetLastBeat
