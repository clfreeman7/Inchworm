#include "Timer.h"

Timer tt;
int x = A0;
int y = A1;
int z = A2;
int freq = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(x,INPUT);
  pinMode(y,INPUT);
  pinMode(z,INPUT);
  tt.every(1000/freq,takeReading);
}

void loop() {
  // put your main code here, to run repeatedly:
  tt.update();
}

void takeReading(){
  int Xread = analogRead(x); 
  int Yread = analogRead(y);
  int Zread = analogRead(z);
  Serial.print(Xread);
  Serial.print('\t');
  Serial.print(Yread);
  Serial.print('\t');
  Serial.print(Zread);
  Serial.print('\n'); 
}

