

int irAnalogPin = 1; // The Potentiometer is connected to analog 0
int LEDpin = 11;      // The LED to pin 11 (PWM pin)
int irReading;      // the analog reading from the FSR resistor divider
float interpVal;
int LEDbrightness;

  // float LuT_1_xElements[] = {10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
  // float LuT_1_yElements[] = {0, 51, 102, 153, 204, 255, 204, 153, 102, 51, 0};                
// Define the elements in lookup table 1'
//
float LuT_1_xElements[] = {73.32, 74.75, 78.83, 85.48,95.97 , 103.95, 111.66,124.56,138.88,156.63, 179.89,211.23,262.24,338.81,510.24,543.88,618.58,633.68};
float LuT_1_yElements[] = {80,75,70,65,60,55,50,45,40,35,30,25,20,15,10,9,8,7};

// initialise  the lookup Table Array size variables
float LuT_1_xSize = 0; // Initialise variable as 0, to be calculated in setup()


// Function prototypes for the lookup Table functions
float LookUpTable1D(float inVal, float elementsArraySize, float xElements[], float yElements[]);
void CheckLuTArrays (float xArraySize, float yArraySize, float xElements[], float yElements[]);

// ----------------------------------------------
// Arduino setup function
void setup() {
  Serial.begin(9600);  // Initialise the serial communications bus with a 9600 baud rate
  pinMode(LEDpin, OUTPUT); // Set the pin mode for the LED pin

  //Calculate the size of the lookup table, LuT_1, xElements Array and yElements Array
  LuT_1_xSize = sizeof(LuT_1_xElements) / sizeof(LuT_1_xElements[0]);
  float LuT_1_ySize = sizeof(LuT_1_yElements) / sizeof(LuT_1_yElements[0]); //Note this is a local variable

  // Check the LuT_1 Arrays for size and increasing xElement Values
  CheckLuTArrays(LuT_1_xSize, LuT_1_ySize, LuT_1_xElements, LuT_1_yElements);

}

// ----------------------------------------------
// Arduino loop function
void loop() {

  // Read the potentiometer Value
  irReading = analogRead(irAnalogPin);
  // Perform the lookup table operation
  interpVal = LookUpTable1D(irReading, LuT_1_xSize, LuT_1_xElements, LuT_1_yElements);

  //Display results

  Serial.print("Analog reading = ");
  Serial.print(irReading);
  Serial.print(", Look - up Values = ");
  Serial.println(interpVal);

  // Use the output value from lookup table to control the brightness of an LED
  LEDbrightness = interpVal;
  analogWrite(LEDpin, LEDbrightness); // here you are using PWM !!!

  // Delay the next iteration of the loop
  delay(200);
}

// ----------------------------------------------
// This function performs the 1-D lookup table operation.
//
// The function will scan through the gaps between the elements in the xElement array, and find
// where the inVal is located. A simple linear interpolation will be performed between indexes n and n+1, 
// of xElements and yElements, to calculate the lookup output value relating to the input value
//
// If the inpt value does not lie in the range of values between the first and last elements of the xElements
// array, an overflow variable will be returned
//
float LookUpTable1D (float inVal, float elementsArraySize, float xElements[], float yElements[]) {

  //declare and initialise local variables
  float fraction = 0.0;

  // Scan through the gaps between the elements in the xElement array, and find where the inVal is
  // located. Perform a simple linear interpolation between indexes n and n+1, of xElements
  // and yElements, to calculate the lookup output value relating to the input value

  for (int n = 0; n <= elementsArraySize - 2; n++) {
    if ((inVal >= xElements[n]) && (inVal <= xElements[n + 1])) {
      fraction = (inVal - xElements[n]) / (xElements[n + 1] - xElements[n]);

      // Return the output value and exit the function
      return (fraction * (yElements[n + 1] - yElements[n])) + yElements[n];
    }

  }
  // Return an overflow value of the input value is not within the input range of the xElements array
  return 0xFFFFFFFF;
}

// ----------------------------------------------
// This function performs a simple check on the lookup table arrays to check the data is valid:
// 1. Check the xElements and yElements arrays are the same size
// 2. Chech that the values in the xElements array are increasing with index
//
// If an error is discovered, an error message is displated, and the code is held in an infinite 
// loop to block further execution
//
void CheckLuTArrays (float xArraySize, float yArraySize, float xElements[], float yElements[]) {

  // Check for array size missmatch between the xElements and yElements arrays
  // If found display an error message, then block the execution of the remainder
  // of the code
  if (xArraySize != yArraySize) { // check for array size missmatch
    Serial.println();
    Serial.println("Error: Number of elements in xElements array is not equal to the number of");
    Serial.println("elements in the yElements array.");
    Serial.println();
    Serial.println("This program will not execute further, and sit in an infinite loop");
    while (1); // Hold the execution at this point
  }

  //Check that the values in xElements are increasing as the index values increase
  // If not display an error message then block the execution of the remainder of the code
  for (int n = 0; n <= xArraySize - 2; n++) {
    // Scan through the xElement indexes
    if (LuT_1_xElements[n] >= LuT_1_xElements[n + 1]) {
      Serial.println();
      Serial.println("Error: the values in xElements are not all increasing with increasing");
      Serial.println("index values");
      Serial.println();
      Serial.println("This program will not execute further, and sit in an infinite loop");
      while (1); // Hold the execution at this point
    }
  }
}
