
#include <Servo.h>

// define the macro pinServo1 as 9, to use for connecting the servo to pin 9
#define pinServo1 9

// Declare a servo motor class variable servo 1
Servo servo1;

int potAnalogPin = 0;
int potReading;
int Angle;
int ServoAngle;
// -------------------------------------
// Setup function
void setup()
{
  Serial.begin(9600);
  servo1.attach(pinServo1);
  servo1.write(0);
  delay(100);
}

// -------------------------------------
// Loop Function
void loop()
{

  potReading = analogRead(potAnalogPin);

  Angle = map(potReading*1,0,1023,-150,150);
  ServoAngle = map(potReading*1,0,1023,-90,90);
  servo1.write(Angle);
  Serial.print("potentiometer: ");
  Serial.println(Angle);
  Serial.print("Angle of Servo: ");
  Serial.println(ServoAngle);

 

}
