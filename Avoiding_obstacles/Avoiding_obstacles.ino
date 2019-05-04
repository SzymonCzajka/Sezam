#define L_PWM 5
#define L_DIR 4
#define R_PWM 6
#define R_DIR 9
#define PWM_MAX 165
#define PWM_MIN 50

#define L_SIDE_SENSOR A1
#define R_SIDE_SENSOR A0
#define BUZZER 10





void setup(){
  // Bridge H configuration
  pinMode(L_DIR,OUTPUT);
  pinMode(R_DIR,OUTPUT);
  pinMode(L_PWM,OUTPUT);
  pinMode(R_PWM,OUTPUT);
  // Sensors configuration
  pinMode(R_SIDE_SENSOR, INPUT_PULLUP);
  pinMode(L_SIDE_SENSOR, INPUT_PULLUP);
  // Other elements configurations
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER,0);

  randomSeed(analogRead(5));
}// setup ends

void loop(){
// Go forward

  leftMotor(40);
  rightMotor(40);
  int los =random(5,20)*10;
  
// When you find obstacles
  if(digitalRead(L_SIDE_SENSOR)==LOW){
    // go back
    
    leftMotor(-40);
    rightMotor(-40);
    digitalWrite(BUZZER,1);
    delay(140+los);
    
    //Turn
    
    leftMotor(40);
    rightMotor(-40);
    digitalWrite(BUZZER,0);
    delay(500);
    
    // Go forward
  }// If enf
  if(digitalRead(R_SIDE_SENSOR)==LOW){
    // Go back
    
    leftMotor(-40);
    rightMotor(-40);
    digitalWrite(BUZZER,1);
    delay(140+los);
    
    //Turn
    
    leftMotor(-40);
    rightMotor(40);
    digitalWrite(BUZZER,0);
    delay(500);
    
    // Go forward
  }// End of if
  }// End of loop


  
void leftMotor(int V){ // Left engine 
  if (V>0){
    V = map(V,0, 100,PWM_MIN, PWM_MAX);
    digitalWrite(L_DIR,0); // Forward
    analogWrite(L_PWM,V); // Speed setting
  }// End of if
  else{
    V=abs(V); // 
    V=map (V,0,100,PWM_MIN,PWM_MAX);
    digitalWrite(L_DIR,1);// Go back
    analogWrite(L_PWM,V); // Speed setting
    
  }// End of else
  
}// End of function

void rightMotor(int V) { // Right engine
  if (V > 0) { //
    V = map(V, 0, 100, PWM_MIN, PWM_MAX);
    digitalWrite(R_DIR, 0); //Go forward
    analogWrite(R_PWM, V); //Speed setting 
  } else {
    V = abs(V); //
    V = map(V, 0, 100, PWM_MIN, PWM_MAX);
    digitalWrite(R_DIR, 1); //Go back
    analogWrite(R_PWM, V); //Speed setting     
  }// End of else
} // End of function

void stopMotors(){ // Stop
  analogWrite(L_PWM,0); // Left Engine Stop
  analogWrite(R_PWM,0); // Right Engine Stop

}// End of function

void przyspieszanie(){
  for( int i=PWM_MIN;i<PWM_MAX;i++){
  leftMotor(i);
  rightMotor(-i);
  delay(100);
  }// End of for
}// End of function

void zwalnianie(){
  for( int i=PWM_MAX;i>PWM_MIN;i--){
  leftMotor(-i);
  rightMotor(i);
  delay(100);  
  }//End of for
}// End of fucntion
