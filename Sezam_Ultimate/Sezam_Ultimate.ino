#include <Servo.h>
Servo serwo;
#define SERWO_PIN 11

#define L_PWM 5
#define L_DIR 4
#define R_PWM 6
#define R_DIR 9
#define PWM_MAX 165
#define PWM_MIN 50


#define L_SIDE_SENSOR A1
#define R_SIDE_SENSOR A0
#define BUZZER 10

//Distance sensor configuration
#define trigPin 8
#define echoPin 7

void setup() {
  //Bridge H configuration
  pinMode(L_DIR, OUTPUT);
  pinMode(R_DIR, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);

  // Mechanical sensor configuration
  pinMode(R_SIDE_SENSOR, INPUT_PULLUP);
  pinMode(L_SIDE_SENSOR, INPUT_PULLUP);

  //Other elements configuration
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, 0); //Buzzer off    

  // Distance sensor configuration
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 


  serwo.attach(SERWO_PIN);
  serwo.write(90);
  
  randomSeed(analogRead(5));
}

void loop() {
    int los =random(5,20)*10;
    
    //Obstacles at distance of 40cm
  if (zmierzOdleglosc() > 40) {
    leftMotor(40); //If not go forward
    rightMotor(40);
  } else {
     //If obstacle
     stopMotors(); //Stop
     serwo.write(20); //Turn right
     delay(800); 
     

    //Check if obstacles is on right side 
    if (zmierzOdleglosc() > 40) {
       //If not
      leftMotor(40);
      rightMotor(-40);
      serwo.write(90);
      delay(400); 
    } else {
      // if it is
      serwo.write(160); //Turn left
      delay(800); //wait

    //Check if obstacles is on right side 
      if (zmierzOdleglosc() > 40) {
         //If not
        leftMotor(-40);
        rightMotor(40);
        serwo.write(90);
        delay(400); //Turn left
      } else {
        //If it is
          leftMotor(-40);
          rightMotor(-40);
          serwo.write(90);
          delay(400);
      }
    }   
    serwo.write(90);
  }
serwo.write(90);
  delay(100); 

// If it's an obstacle
  if(digitalRead(L_SIDE_SENSOR)==LOW){
    // Go back
    
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
  }// end of if
  if(digitalRead(R_SIDE_SENSOR)==LOW){
    // go back
    
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
  }//end of if
  
  
}

int zmierzOdleglosc() {
  long czas, dystans;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  czas = pulseIn(echoPin, HIGH);
  dystans = czas / 58;

  return dystans;
}

void leftMotor(int V) {
  if (V > 0) { //
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(L_DIR, 0); //Go forward
    analogWrite(L_PWM, V); //Speed setting 
  } else {
    V = abs(V); 
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(L_DIR, 1); // Go back
    analogWrite(L_PWM, V); //Speed Setting    
  }
}

void rightMotor(int V) {
  if (V > 0) { 
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(R_DIR, 0); //Go forward
    analogWrite(R_PWM, V); //Speed setting
  } else {
    V = abs(V); //Funkcja abs() 
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(R_DIR, 1); //Go back
    analogWrite(R_PWM, V); //Speed Setting    
  }
}

void stopMotors() {
  analogWrite(L_PWM, 0); //Left engine off
  analogWrite(R_PWM, 0); //Right engine off
}
