#include <LiquidCrystal.h> // includes the LiquidCrystal Library
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); 
const int sigPinA = 12;
const int sigPinB = 13;
const int redA = 10;
const int greenA = 11;
const int redB = 8;
const int greenB = 9;
long durationA, durationB;
int distanceA, distanceB, vacant, occupied;

void setup() {
  lcd.begin(16,2);
  pinMode(redA, OUTPUT);
  pinMode(greenA, OUTPUT);
  pinMode(redB, OUTPUT);
  pinMode(greenB, OUTPUT);
}
void loop() {
  
  String A, B;
  
  occupied = 0;
  vacant = 0;
  
  pinMode(sigPinA,OUTPUT);
  digitalWrite(sigPinA,LOW);
  delayMicroseconds(2);
  
  digitalWrite(sigPinA, HIGH);
  delayMicroseconds(5);
  digitalWrite(sigPinA,LOW);
  
  pinMode(sigPinA,INPUT);
  
  durationA=pulseIn(sigPinA,HIGH);
  
  distanceA=(durationA*0.034)/2;
  
   pinMode(sigPinB,OUTPUT);
  
  digitalWrite(sigPinB,LOW);
  
  delayMicroseconds(2);
  
  digitalWrite(sigPinB, HIGH);
  
  delayMicroseconds(5);
  
  digitalWrite(sigPinB,LOW);
  
  pinMode(sigPinB,INPUT);
  
  durationB=pulseIn(sigPinB,HIGH);
  
  distanceB=(durationB*0.034)/2;
  
  if(distanceA > 200) {
    vacant++;
    digitalWrite(greenA, HIGH);
    digitalWrite(redA, LOW);
    A = '0';
  } else {
    occupied++;
    digitalWrite(greenA, LOW);
    digitalWrite(redA, HIGH);
    A = '1';
  };
     
  if(distanceB > 200) {
    vacant++;
    digitalWrite(greenB, HIGH);
    digitalWrite(redB, LOW);
    B = '0';
  } else {
    occupied++;
    digitalWrite(greenB, LOW);
    digitalWrite(redB, HIGH);
    B = '1';
  };
  
  lcd.setCursor(0,0); 
  lcd.print("vagas livres "); 
  lcd.print(vacant);
  
  lcd.setCursor(0,1); 
  lcd.print("vagas ocupadas "); 
  lcd.print(occupied);
  
  
  
  Serial.begin(16000);
  Serial.println("{\"A\":"+A+", \"B\":"+B+"}");
  Serial.end();

}