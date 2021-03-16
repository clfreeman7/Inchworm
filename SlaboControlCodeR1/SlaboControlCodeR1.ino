
String Input;
int RestingAngle1;
int RestingAngle2;
int RestingAngleOffset;
int CritAngle1;
int CritAngle2;
int Trash;

int a1 = A1;
int a2 = A2;
int x1 = analogRead(a1);
int x2 = analogRead(a2);

void State1();
void State2();
void State3();
void State4();

//Setup ---------------------------------------------------------------------------

void setup() {
  
Serial.begin(9600);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);

//start state for motor controller
digitalWrite(6, LOW); //Motor 1: Input 1
digitalWrite(7, LOW); //Motor 1: Input 2
digitalWrite(8, LOW); //Motor 2: Input 1
digitalWrite(9, LOW); //Motor 2: Input 2

Serial.println("Input State Pathway. Example:1234");
while(!Serial.available());
  if (Serial.available() > 0) {
     Input = Serial.readString(); 
  }
  Serial.print("Pathway:");
  Serial.println(Input);
  
Serial.println("Input Critical Angle 1");    
while(!Serial.available());
  if (Serial.available() > 0) {
     CritAngle1 = Serial.parseInt(); 
  } 
  Serial.print("Critical Angle 1:");
  Serial.println(CritAngle1);

Serial.println("Input Critical Angle 2");    
while(!Serial.available());
  if (Serial.available() > 0) {
     CritAngle2 = Serial.parseInt(); 
  } 
  Serial.print("Critical Angle 2:");
  Serial.println(CritAngle2);

Serial.println("Input Resting Angle Offset");    
while(!Serial.available());
  if (Serial.available() > 0) {
     RestingAngleOffset = Serial.parseInt(); 
  } 
  Serial.print("Resting Angle Offset:");
  Serial.println(RestingAngleOffset);


Serial.println("Taking resting angles, make sure slabo is flat");

RestingAngle1 = x1 + RestingAngleOffset;
RestingAngle2 = x2 + RestingAngleOffset;


}

//Main Code -----------------------------------------------------------------------

void loop() {

//Check inputs from Serial
int i;
int longness = Input.length();
while(!Serial.available()){
    for (i=0;i<longness;i++){
      char Current = Input.charAt(i);
      if (Current == '1'){
        State1();
      }
      else if (Current == '2'){
        State2();
      }
      else if (Current == '3'){
        State3();
      }
      else if (Current == '4'){
        State4();
      }
    
    }
  }
if (Serial.available() > 0) {
     Trash = Serial.parseInt(); 
  } 
    

}

// Functions ----------------------------------------------------------------------------------------------------------------------------

//State 1: Motor 1 OFF Motor 2 OFF
//Turns off Motor 1 and 2 then advances once they have both reached their resting angles.

void State1(){
  digitalWrite(6, LOW);
  digitalWrite(7, LOW); 
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  Serial.println("State 1");

    while(x1 >= RestingAngle1 || x2 >= RestingAngle2){
     
    }
  
  }

//State 2: Motor 1 ON Motor 2 OFF
//Turns off Motor 2 then reads digital data from accelerometers to determine if Motor 1 needs to be turned on or held to keep slabo at critical angle, 
//then advances once Motor 2 has reached it's resting angle and Motor 1 has reached it's critical angle.

void State2(){
  Serial.println("State 2");
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
      
      while(x1 <= CritAngle1 || x2 >= RestingAngle2){

      if (x1 >= CritAngle1){
          digitalWrite(6, HIGH);
          digitalWrite(7, HIGH);
      }
      else {
        
         digitalWrite(6, HIGH);
         digitalWrite(7, LOW); 
      }
      
    }
  
}

//State 3: Motor 1 OFF Motor 2 ON
//Turns off Motor 1 then reads digital data from accelerometers to determine if Motor 2 needs to be turned on or held to keep slabo at critical angle, 
//then advances once Motor 1 has reached it's resting angle and Motor 2 has reached it's critical angle.

void State3(){
  Serial.println("State 3");
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
      
      while(x1 >= RestingAngle1 || x2 <= CritAngle2){

      if (x2 >= CritAngle2){
          digitalWrite(8, HIGH);
          digitalWrite(9, HIGH);
      }
      else {
        
         digitalWrite(8, HIGH);
         digitalWrite(9, LOW); 
      }
      
    }
  
}

//State 4: Motor 1 ON Motor 2 ON
//Reads digital data from accelerometers to determine if Motor 1 or 2 needs to be turned on or held to keep slabo at critical angle, then advances 
//once both Motor 1 and 2 have reached their critical angles.

void State4(){
  Serial.println("State 4 Start");
      
      while(x1<= CritAngle1 || x2 <= CritAngle2){
      if (x2 >= CritAngle1){
          digitalWrite(6, HIGH);
          digitalWrite(7, HIGH);
      }
      else {
        
         digitalWrite(6, HIGH);
         digitalWrite(7, LOW); 
      }
      if (x2 >= CritAngle2){
          digitalWrite(8, HIGH);
          digitalWrite(9, HIGH);
      }
      else {
        
         digitalWrite(8, HIGH);
         digitalWrite(9, LOW); 
      }
      
    }
  
}
