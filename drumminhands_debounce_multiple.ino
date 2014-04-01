/* 
  Modified by combining these tutorials
    Blink without Delay  http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
    State change detection (edge detection) http://arduino.cc/en/Tutorial/ButtonStateChange
    http://www.arduino.cc/en/Tutorial/Debounce
 */

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin[] = {4,7,13};      // the number of the LED pin
const int totalPins = 3; //how many LED's are in the chain

// Variables will change:
int ledState[] = {HIGH,HIGH,HIGH};         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

// variables for keeping track of programs
int programState = 0;         // current program seleted -- buttonpresses rotate between programs
int numOfPrograms = 3;        // how many programs are there total, not including the off state

unsigned long currentMillis = 0;  //for programs
long previousMillis = 0;        // will store last time LED was updated
long interval[] = {1000, 500, 250}; // interval at which to blink (milliseconds)

void setup() {
  pinMode(buttonPin, INPUT);

  // set initial LED state
  for (int i = 0; i < numOfPrograms; i++) {  
    pinMode(ledPin[i], OUTPUT);  
    digitalWrite(ledPin[i], ledState[i]);
  }
  
  Serial.begin(9600);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        Serial.println("ProgramState: " + String(programState));
        //change the program
        programState = (programState + 1) % (numOfPrograms + 1); //include numOfPrograms + 1, since there is an off state program not included in the number of programs
      }
    }
    //run the chosen program 
    switch (programState) {
      case 0:
        programOff();
        break; 
      case 1:
        programOne();
        break;        
      case 2:
        programTwo();
        break;
      case 3:
        programThree();
        break;
      default: 
        // if nothing else matches, do the default   
       programOff(); 
    }
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}


void programOff(){ 
  Serial.println( "Program OFF started");
  
  // turn everything off
  for (int i = 0; i < numOfPrograms; i++) { 
    ledState[i] = LOW; //set the state
  }
  
  // set the LEDs
  for (int i = 0; i < totalPins; i++) {  
    digitalWrite(ledPin[i], ledState[i]);
  }
}

void programOne(){ 
  Serial.println( "Program ONE started");
  
  currentMillis = millis();
  Serial.println("currentMillis: " + String(currentMillis));
  Serial.println("previousMillis: " + String(previousMillis));
  Serial.println("interval[0]: " + String(interval[0]));
 
  if(currentMillis - previousMillis > interval[0]) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (ledState[0] == LOW)
      ledState[0] = HIGH;
    else
      ledState[0] = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin[0], ledState[0]);
  }  
}

void programTwo(){ 
  Serial.println( "Program TWO started");
  
  // turn everything off
  for (int i = 0; i < numOfPrograms; i++) { 
    ledState[i] = LOW; //set the state
  }
  
  //set the pin high 
  ledState[1] = HIGH;
  
  // set the LEDs
  for (int i = 0; i < totalPins; i++) {  
    digitalWrite(ledPin[i], ledState[i]);
  }
}

void programThree(){ 
  Serial.println( "Program THREE started");
  
  // turn everything off
  for (int i = 0; i < numOfPrograms; i++) { 
    ledState[i] = LOW; //set the state
  }
  
  //set the pin high 
  ledState[2] = HIGH;
  
  // set the LEDs
  for (int i = 0; i < totalPins; i++) {  
    digitalWrite(ledPin[i], ledState[i]);
  }
}
