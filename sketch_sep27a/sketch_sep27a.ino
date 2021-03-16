
int PWMpin = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PWMpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(PWMpin,179);
}
