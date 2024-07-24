
// Code template for the switch debounce exercise
//
// Author: Ben Taylor
// University of Sheffield
// Date: September 2021
//
// This is a partially completed code template for the switch debounce exercise of the 
// Introduction to Arduino: – Digital I/O activity

// assign the pin number for the button input
const byte buttonPin = 2;

// display timer store
unsigned long lastDisplay = 0;

// Initialise button state variables
// the current reading from the input pin
int buttonState = HIGH;
// the previous reading from the input pin
int lastButtonState = LOW;

int buttonRead = HIGH;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 100;    // the debounce time; increase if the output flickers


// counter for debounced events
int debouncedCounter = 0;

// counter for bounced events
// unDebouncedCounter is used within an interrupt, hence the volatile keyword
// is required to allow the variable to be updated outside of the main program flow
volatile unsigned int unDebouncedCounter = 0;

// ----------------------------------------------
// Setup function is run once at the start of program execution
void setup() {

  // initialise the display timer variable value
  lastDisplay = millis();

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);

  // configure an interrupt on a change in value of the buttonPin
  // The pinInterruptHandler function will run each time a change in value is
  // detected on the pin
  attachInterrupt(digitalPinToInterrupt(buttonPin), pinInterruptHandler, CHANGE);
}

void loop() {

  lastButtonState = buttonRead;
  buttonRead = digitalRead(buttonPin);

  // *************************************************************
  // Add your user code between these two starred lines
  if(buttonRead != lastButtonState){
    if((millis()-lastDebounceTime)> debounceDelay){
      debouncedCounter++;
      lastDebounceTime= millis();
      
    }
  }


  // *************************************************************
  // The remaining portion of the loop() function displays the values of the
  // unDebouncedCounter and debouncedCounter variables onto the serial monitor
  // approximately every 250ms


  // Display the bounce counters every 250ms
  if (millis() >= lastDisplay + 250) {
    // set lastDisplay to the current millis() time
    lastDisplay = millis();

    // write the counter values to the serial monitor;
    Serial.print("Undebounced Counter = ");
    Serial.print(unDebouncedCounter);
    Serial.print(", Debounced Counter = ");
    Serial.print(debouncedCounter);
    Serial.println("        ");
  }

}


// ------------------------------------------------
// Interrupt service routine assigned to the buttonPin interrupt
void pinInterruptHandler(void) {

  // Increment the unDebouncedCounter
  unDebouncedCounter++;

}
