int x = A0;
int y = A1;
int z = A2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(x,INPUT);
  pinMode(y,INPUT);
  pinMode(z,INPUT);    
}

void loop() {
  // put your main code here, to run repeatedly:
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
