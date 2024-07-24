
const int led2 = 2;     // the number of the pushbutton pin
const int led3 =  3;      // the number of the LED pin
const int led4 = 4;
      int i = 500;
      int j = 1000;
      int k = 2000;
      int i2,j3,k4;

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(led2, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(led3, OUTPUT);
   pinMode(led4, OUTPUT);
   i2 = millis();
   j3 = millis();
   k4 = millis();
}


void togglei2(){
  if(digitalRead(led2) == LOW){
    digitalWrite(led2, HIGH);
  }
  else{
    digitalWrite(led2, LOW);
  }
  i2= millis();
}
void togglej3(){
   if(digitalRead(led3) == LOW){
    digitalWrite(led3, HIGH);
  }
  else{
    digitalWrite(led3, LOW);
  }
  j3= millis();
}
void togglek4(){
   if(digitalRead(led4) == LOW){
    digitalWrite(led4, HIGH);
  }
  else{
    digitalWrite(led4, LOW);
  }
  k4= millis();
}

void loop() {
 
  Serial.println(led2);
   Serial.println(led3);
    Serial.println(led4);

    if((millis()-i2)>= i){
        togglei2 ();
}
if((millis()-j3)>= j){
        togglej3 ();
}
if((millis()-k4)>= k){
        togglek4 ();
}


 }
