
 

int IRAnalogPin= 1;
float IRReading;
 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor

}
 
void loop(void) {
  
  int i =0;

  while (i<50){

    IRReading = IRReading + (float)analogRead(IRAnalogPin);
    i++;  
  }

  IRReading = IRReading/50;

  
  Serial.print("Sharp IR sensor reading = ");
  Serial.println(IRReading);
 
  
}
