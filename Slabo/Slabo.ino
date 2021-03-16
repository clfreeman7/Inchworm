int o1m1 = 13;
int o2m1 = 12;
int o1m2 = 22;
int o2m2 = 23;

int i = 0;
int phi = 50;
int del = 100;

void setup() {
  Serial.begin(9600);
  pinMode(o1m1, OUTPUT);
  pinMode(o2m1, OUTPUT);
  pinMode(o1m2, OUTPUT);
  pinMode(o2m2, OUTPUT); 
}

void loop() {
  delay(1000);
  for (i;i<10;i++){
    digitalWrite(o1m1, LOW);
    digitalWrite(o2m1, HIGH);
    delay(phi);
    Serial.println("phi");
    digitalWrite(o1m2, LOW);
    digitalWrite(o2m2, HIGH);
    delay(del);
    Serial.println("del");

    digitalWrite(o1m1, LOW);
    digitalWrite(o2m1, LOW);
    digitalWrite(o1m2, LOW);
    digitalWrite(o2m2, LOW);   
    delay(del);    
  }
}
