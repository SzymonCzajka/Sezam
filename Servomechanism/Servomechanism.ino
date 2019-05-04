//Library 
#include <Servo.h>
Servo serwo;
#define SERWO_PIN 11

#define L_PWM 5
#define L_DIR 4
#define R_PWM 6
#define R_DIR 9
#define PWM_MAX 165

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

  //Other elements configuration
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, 0); //Buzzer Off    

  //Distance sensor configuration
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  //Servomechanism configuration
  serwo.attach(SERWO_PIN);
  serwo.write(90);
}

void loop() {
  //Obstacles at distance of 40cm
  if (zmierzOdleglosc() > 40) {
    leftMotor(40); //If not go forward
    rightMotor(40);
  } else {
     //If obstacle
     stopMotors(); //Stop
     serwo.write(20); //Turn right
     delay(800); //Wait

    //Check if obstacles is on right side 
    if (zmierzOdleglosc() > 40) {
       //If not
      leftMotor(40);
      rightMotor(-40);
      serwo.write(90);
      delay(400); //Wait 400ms
    } else {
      //If it
      serwo.write(160); //Turn left
      delay(800); //wait
      
      //Check if obstacles is on left side 
      if (zmierzOdleglosc() > 40) {
         //If not
        leftMotor(-40);
        rightMotor(40);
        serwo.write(90);
        delay(400); //
      } else {
        //If it's
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
  if (V > 0) { 
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(L_DIR, 0); //Go forward
    analogWrite(L_PWM, V); 
  } else {
    V = abs(V); 
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(L_DIR, 1); Go back
    analogWrite(L_PWM, V);    
  }
}

void rightMotor(int V) {
  if (V > 0) { 
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(R_DIR, 0); //Go forward
    analogWrite(R_PWM, V); 
  } else {
    V = abs(V);
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(R_DIR, 1); // Go back
    analogWrite(R_PWM, V); 
  }
}

void stopMotors() {
  analogWrite(L_PWM, 0); // Left engine off
  analogWrite(R_PWM, 0); //WRight engine off
}
