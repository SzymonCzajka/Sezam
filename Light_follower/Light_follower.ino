#define L_PWM 5
#define L_DIR 4
#define R_PWM 6
#define R_DIR 9
#define PWM_MAX 165
#define PWM_MIN 30

#define L_LIGHT_SENSOR A1
#define R_LIGHT_SENSOR A0
#define BUZZER 10

#define LED 13

int bip=0;


void setup(){
  // Bridge H configuration
  pinMode(L_DIR,OUTPUT);
  pinMode(R_DIR,OUTPUT);
  pinMode(L_PWM,OUTPUT);
  pinMode(R_PWM,OUTPUT);

  // Other elements configuration
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER,0);

  Serial.begin(9600);


}// end of setups

void loop(){
  int odczytLewy = analogRead (L_LIGHT_SENSOR);
  int odczytPrawy = analogRead(R_LIGHT_SENSOR);
  int roznica = odczytLewy-odczytPrawy;
  migLED();
  stopMotors();

  while (odczytPrawy <500 || odczytLewy <500){
    // beep i times
    if(bip <3){
      BUZZASTER();
      bip++;
    }// end of if
    else{
    START();
  }// end of else
} // end of  while

}// end of loop



void leftMotor(int V){ // Left engine
  if (V>0){
    V = map(V,0, 100,PWM_MIN, PWM_MAX);
    digitalWrite(L_DIR,0); // Forward
    analogWrite(L_PWM,V); // Speed
  }// end of if
  else{
    V=abs(V);
    V=map (V,0,100,PWM_MIN,PWM_MAX);
    digitalWrite(L_DIR,1);// Reverse
    analogWrite(L_PWM,V); // Speed

  }// end of else

}// end of function

void rightMotor(int V) { // Right engine
  if (V > 0) {
    V = map(V, 0, 100, PWM_MIN, PWM_MAX);
    digitalWrite(R_DIR, 0);
    analogWrite(R_PWM, V);
  } else {
    V = abs(V);
    V = map(V, 0, 100, PWM_MIN, PWM_MAX);
    digitalWrite(R_DIR, 1);
    analogWrite(R_PWM, V);
  }
}

void stopMotors(){ // Stop both engines
  analogWrite(L_PWM,0);
  analogWrite(R_PWM,0);

}

void przyspieszanie(){ //Acceleration
  for( int i=PWM_MIN;i<PWM_MAX;i++){
  leftMotor(i);
  rightMotor(-i);
  delay(100);
  }
}

void zwalnianie(){// Braking
  for( int i=PWM_MAX;i>PWM_MIN;i--){
  leftMotor(-i);
  rightMotor(i);
  delay(100);
  }
}

void START(){
  int odczytLewy = analogRead (L_LIGHT_SENSOR);
  int odczytPrawy = analogRead(R_LIGHT_SENSOR);
  int roznica = odczytLewy-odczytPrawy;
  if (roznica>75){ // Turn Right
    leftMotor(-30);
    rightMotor(30);
  }// end of if
  else if(roznica <-75){ // Turn Left
    leftMotor(30);
    rightMotor(-30);
  } // end of else if

  else{
    leftMotor(30);
    rightMotor(30);
  }// end of else
}// end of function

void migLED(){
  digitalWrite(LED,1);
  delay(500);
  digitalWrite(LED,0);
  delay(500);
}// end of function

void BUZZASTER(){
  digitalWrite(BUZZER,1);
  delay(500);
  digitalWrite(BUZZER,0);
  delay(500);
}// end of function
