#include <RC5.h>

#define TSOP_PIN 3
#define L_PWM 5
#define L_DIR 4
#define R_PWM 6
#define R_DIR 9
#define PWM_MAX 165
#define PWM_MIN 30
 
#define BUZZER 10
#define LED 13

RC5 rc5(TSOP_PIN); // Inofrmacja o podlaczeniu odbiornika TSOP

//Zmienne dla RC5
byte address;
byte command;
byte toggle;

void setup(){
 //Konfiguracja pinow od mostka H
  pinMode(L_DIR, OUTPUT);
  pinMode(R_DIR, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);
 
  //Konfiguracja pozostalych elementow
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, 0); //Wylaczenie buzzera  
  pinMode(LED, OUTPUT); 
  digitalWrite(LED, 0); //Wylaczenie diody
 
  Serial.begin(9600);
}// koniec setup

int predkosc = 30;
byte togglePoprzedni =0;

void loop(){
  if(rc5.read(&toggle, &address, &command)){
  
  switch (command){
    case 2:
    leftMotor(predkosc);
    rightMotor(predkosc);
    break;
    case 8:
    leftMotor(-predkosc);
    rightMotor(-predkosc);
    break;
    case 5:
    stopMotors();
    break;
    case 4:
    leftMotor(-predkosc);
    rightMotor(predkosc);
    break;
    case 6:
    leftMotor(predkosc);
    rightMotor(-predkosc);
    break;
    case 9:
    leftMotor(-predkosc);
    rightMotor(-predkosc*0.5);
    break;
    case 3:
    leftMotor(predkosc);
    rightMotor(predkosc*0.5);
    break;
    case 1:
    leftMotor(predkosc*0.5);
    rightMotor(predkosc);
    break;
    case 7:
    leftMotor(-predkosc*0.5);
    rightMotor(-predkosc);
    break;
    case 12:
    digitalWrite(BUZZER, 1);
    delay(500);
    digitalWrite(BUZZER,0);
    break;
  }// koniec switch
    


  //Jeśli bit toggle jest taki sam jak poprzednio
    if (toggle == togglePoprzedni) {
      predkosc++; //Zwieksz predkosc obrotu o 1
 
      //Jeśli wartość prędkości przekroczy 90
      if (predkosc >= 90) {
        predkosc = 30; //To ustawiamy stadnardowe 30
      }//koniec if3
    }// koniec if2
    else { //Jeśli bit toggle jest różny
      //Ustaw predkosc na standardową
      predkosc = 30;    
    }// koniec else
    //Zapamiętanie poprzedniej wartości toggle
    togglePoprzedni = toggle;
  }// koniec if1
  }// koniec loop
  


void leftMotor(int V){ // sterownaie lewym silnikiem
  if (V>0){
    V = map(V,0, 100,PWM_MIN, PWM_MAX);
    digitalWrite(L_DIR,0); // Kierunek do przodu
    analogWrite(L_PWM,V); // Ustawienie Predkosci
  }// koniec if
  else{
    V=abs(V); // Funkcja abs() zworci wartosc V bez znaku
    V=map (V,0,100,PWM_MIN,PWM_MAX);
    digitalWrite(L_DIR,1);// Kierunek do tylu
    analogWrite(L_PWM,V); // Ustawienie predkosci
    
  }// koniec else
  
}// koniec funkcji

void rightMotor(int V) { // funkcja sterujaca prawym silnikiem
  if (V > 0) { //Jesli predkosc jest wieksza od 0 (dodatnia)
    V = map(V, 0, 100, PWM_MIN, PWM_MAX);
    digitalWrite(R_DIR, 0); //Kierunek: do przodu
    analogWrite(R_PWM, V); //Ustawienie predkosci 
  } else {
    V = abs(V); //Funkcja abs() zwroci wartosc V  bez znaku
    V = map(V, 0, 100, PWM_MIN, PWM_MAX);
    digitalWrite(R_DIR, 1); //Kierunek: do tyłu
    analogWrite(R_PWM, V); //Ustawienie predkosci    
  }// koniec else
} // koniec funkcji

void stopMotors(){ // funkcja zatrzymujaca robota
  analogWrite(L_PWM,0); // Zatrzymanie lewego sinika 
  analogWrite(R_PWM,0); // zatrymanie prawego silnika

}// koniec funckji

void przyspieszanie(){
  for( int i=PWM_MIN;i<PWM_MAX;i++){
  leftMotor(i);
  rightMotor(-i);
  delay(100);
  }// koniec for
}// koniec funckji

void zwalnianie(){
  for( int i=PWM_MAX;i>PWM_MIN;i--){
  leftMotor(-i);
  rightMotor(i);
  delay(100);  
  }//koniec for
}// koniec funckji



void migLED(){
  digitalWrite(LED,1);
  delay(500);
  digitalWrite(LED,0);
  delay(500);
}// koniec funkcji

void BUZZASTER(){
  digitalWrite(BUZZER,1);
  delay(500);
  digitalWrite(BUZZER,0);
  delay(500);
}// koniec funkcji
