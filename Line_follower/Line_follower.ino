#define L_PWM 5
#define L_DIR 4
#define R_PWM 6
#define R_DIR 9
#define PWM_MAX 165
#define PWM_MIN 30
#define GRANICA 1015

#define L_LINE_SENSOR A1
#define R_LINE_SENSOR A0
#define BUZZER 10

#define LED 13
void setup() {
  // Konfiguracja pinow od mostka H
  pinMode(L_DIR,OUTPUT);
  pinMode(R_DIR,OUTPUT);
  pinMode(L_PWM,OUTPUT);
  pinMode(R_PWM,OUTPUT);

  // Konfiguacja pozostałych elementow
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER,0);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,0);

  Serial.begin(9600);
}

void loop() {

  if (leftSensor() == 0 && rightSensor() == 0) { //Jesli czujniki nie widza linii
    leftMotor(40); //Jazda prosto
    rightMotor(40);
  } else if (leftSensor() == 1) { //Jesli lewy czujnik widzi linie
    leftMotor(0); //Jazda po łuku w lewo
    rightMotor(40);    
  } else if (rightSensor() == 1) { //Jesli prawy czujnik widzi linie
    leftMotor(40); //Jazda po łuku w prawo
    rightMotor(0);
  }


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

void START(){
  int odczytLewy = analogRead (L_LINE_SENSOR);
  int odczytPrawy = analogRead(R_LINE_SENSOR);
  int roznica = odczytLewy-odczytPrawy;
  if (roznica>75){ // skret w prawo
    leftMotor(-30);
    rightMotor(30);
  }// koniec if
  else if(roznica <-75){ // skret w lewo
    leftMotor(30);
    rightMotor(-30);
  } // koniec else if

  else{
    leftMotor(30);
    rightMotor(30);
  }// koniec else
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

boolean leftSensor(){
  if (analogRead(L_LINE_SENSOR)> GRANICA){
    return 1;
  }// koniec if
  else{
    return 0;
  }// koniec else
}

boolean rightSensor(){
  if (analogRead(R_LINE_SENSOR)> GRANICA){
    return 1;
  }// koniec if
  else{
    return 0;
  }// koniec else
}
