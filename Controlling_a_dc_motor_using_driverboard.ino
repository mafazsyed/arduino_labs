
const int pinAI1 = 7;       // Pin allocation for AI1
const int pinAI2 = 8;       // Pin allocation for AI2
const int pinPWM = 5;       // Pin allocation for the PWM pin
const int pinStandBy = 9;   // Pin allocation for the standby pin
int potAnalogPin = 0;
int potReading;
int potAngle;

boolean AI1 = 0;            // AI1 pin value
boolean AI2 = 0;            // AI2 pin value
boolean standBy = 0;        // standBy pin Value

boolean rotDirect = 0;      // Rotation direction variable
unsigned char pwmValue = 0; // PWM value to be written to the output

void setup()
{
  // Assign the digital I/O pin directions
  pinMode(pinAI1, OUTPUT);
  pinMode(pinAI2, OUTPUT);
  pinMode(pinPWM, OUTPUT);
  pinMode(pinStandBy, OUTPUT);


  //Initialize the serial port
  Serial.begin(9600);

  // Drive the standby pin high to enable the output
  standBy = true;
  digitalWrite(pinStandBy, standBy);

  // Set Initial values for AI1 and AI2 control function pins
  AI1 = true;
  AI2 = false;

  // set an initial value for the PWM value
  pwmValue = 100;
}

void loop()
{

  potReading = analogRead(potAnalogPin);

  Serial.print("potentiometer: ");
  Serial.println(potReading);

  potAngle = map(potReading*1, 0,1023,-250,250);
  if(potAngle>0){
  pwmValue = potAngle;
    AI1 = true;
    AI2 = false;
    digitalWrite(pinAI1, AI1);
  digitalWrite(pinAI2, AI2);

  // Write the pwnValue to the PWM pin
  analogWrite(pinPWM, pwmValue);

  // Display the board variable status to the Serial Monitor
  Serial.print("PWM output value = ");
  Serial.print(pwmValue);
  Serial.print(", Standby = ");
  Serial.print(standBy);
  Serial.print(", AI1 = ");
  Serial.print(AI1);
  Serial.print(", AI2 = ");
  Serial.println(AI2);
  }
  else if(potAngle<0){
    pwmValue = -potAngle;
    AI1 = false;
    AI2 = true;
    digitalWrite(pinAI1, AI1);
  digitalWrite(pinAI2, AI2);

  // Write the pwnValue to the PWM pin
  analogWrite(pinPWM, pwmValue);

  // Display the board variable status to the Serial Monitor
  Serial.print("PWM output value = ");
  Serial.print(pwmValue);
  Serial.print(", Standby = ");
  Serial.print(standBy);
  Serial.print(", AI1 = ");
  Serial.print(AI1);
  Serial.print(", AI2 = ");
  Serial.println(AI2);
  }
  }
  