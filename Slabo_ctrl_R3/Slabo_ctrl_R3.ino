/*
Notes:
1. To change variable value in function, assign global variable to passed variable or directly change value of global variable in function
*/

int a1, a2;                       // Analog pin that reads accelerometer i that corresponds to motor i
int read1, read2;                 // analogRead(ai)
int i,j,k,m,n;                    // Counters used in for loops
int critAngle1, critAngle2;       // Critical angle representing transition from State 0 to State 1
int Input[4];                     // Array of node integers in simple cycle, e.g. "12341"
int len;                          // Length of Input String. 
int arr[4];                       // Array that stores parsed Input string
bool m11,m12,m21,m22;             // Digital logic level for TA8428K motor driver, e.g. m12 = motor 1, pin 2 logic level (HIGH or LOW)
int isActive1, isActive2;         // Activation state for each limb
int activeArr[2];                 // Array of activation states isActive1 & isActive2
int activeCheckArr[2];            // Array of activation states to check against activeArr to determine whether to activate/deactive motor
int nextState;                    // Stores arr[i+1]. Used to compare current state to next state

// Function declarations
void getCurrentState();
void getNextState();
void getSimpleCycle();

void setup() {
  // put your setup code here, to run once:
  Serial.println("begin");
  Serial.begin(9600);
  i = 0;
  a1 = A1;
  a2 = A2;
  read1 = analogRead(a1);
  read2 = analogRead(a2);
  critAngle1 = 290;
  critAngle2 = 290;
  isActive1 = 0;
  isActive2 = 0;
  Serial.println("setup check");
  getSimpleCycle();
  getCurrentState(read1,read2,isActive1,isActive2,critAngle1,critAngle2);
  goToState();
}

void loop() {
  // put your main code here, to run repeatedly:
}

// Read and parse Input string, store in array
void getSimpleCycle(){
  bool wait = true;
  while (wait == true){
    Serial.println("getSimpleCycle");
    if (Serial.available() > 0) { // insert for loop to account for posirion of input array
      for   
        Serial.println("available");
        int inChar = Serial.read();
        Serial.println("read");
        if (isDigit(inChar)) {
          // convert the incoming byte to a char and add it to the string:
          Input += inChar;
          Serial.print("Input:\t");
          Serial.println(Input);
        }
        // if you get a newline, print the string, then the string's value:
        if (inChar == '\n') {
          len = sizeof(Input);
          Serial.println("Value:");
          for (j=0;j<len;j++){
            arr[j] = (int)Input[j];
            Serial.print("arr[j]:\t");
            Serial.println(arr[j]);
          }
          Serial.println(Input.toInt());
          Serial.println("String: ");
          Serial.println(Input);
          // clear the string for new input:
          Input = "";
          Serial.println("clear Input");
          wait = false;
        }
        Serial.println("Input State Pathway. Example:1234");
          while(!Serial.available()){
            if (Serial.available() > 0) {
              Input = Serial.readString(); 
            }
            Serial.println("Pathway:");
            Serial.println(Input);
        }  
    }
    else{
      //do nothing
      Serial.println("Waiting for Input..");
      delay(250);
    }
    Serial.println("end of while loop");
  }
}
// Detects robot's current state, e.g. 0,1
void getCurrentState(int r1, int r2, int iA1, int iA2, int cA1, int cA2){
  Serial.println("begin getCurrentState");
  if (r1 < cA1){
    isActive1 = 0;
    Serial.println("r1<cA1");
  }
  else if (r1 >= cA1){
    isActive1 = 1;
    Serial.println("r1>=cA1");
  }
  else if (r2 < cA2){
    isActive2 = 0;
    Serial.println("r2<cA2");
  }
  else if (r2 >= cA2){
    isActive2 = 1;
    Serial.println("r2>=cA2");
  }
  else{
    Serial.println("ERROR: Cannot determine state.");  
  }
}

void getNextState(int a){
  Serial.println("begin getNextState");
  nextState = arr[i+1];
  switch(nextState){
    case 1:
      Serial.println("case1");
      activeCheckArr[0] = 0;
      activeCheckArr[1] = 0;
    case 2:
      Serial.println("case2");
      activeCheckArr[0] = 0;
      activeCheckArr[1] = 1;
    case 3:
      Serial.println("case3");
      activeCheckArr[0] = 1;
      activeCheckArr[1] = 0;
    case 4:
      Serial.println("case4");
      activeCheckArr[0] = 1;
      activeCheckArr[1] = 1;
    default:
      Serial.println("End of simple cycle");
  }
}

void goToState(){
  Serial.println("begin goToState");
  if(activeArr[0] == activeCheckArr[0] && activeArr[1] == activeCheckArr[1]){
    //do nothing
    Serial.println("do Nothing");
  }
  if(activeArr[0] == activeCheckArr[0] && activeArr[1] != activeCheckArr[1]){
    //m1: do nothing
    if(activeCheckArr[1] == 1){
      Serial.println("motor2 on");
      m21 = HIGH;
      m22 = LOW;
    }
    else{
      Serial.println("motor2 off");
      m21 = LOW;
      m22 = LOW;
    }
  }
  if(activeArr[0] != activeCheckArr[0] && activeArr[1] == activeCheckArr[1]){
    if(activeCheckArr[0] == 1){
      Serial.println("motor1 on");
      m11 = HIGH;
      m12 = LOW; 
    }
    else{
      Serial.println("motor1 off");
      m11 = LOW;
      m12 = LOW;
    }
  }
  if(activeArr[0] != activeCheckArr[0] && activeArr[1] != activeCheckArr[1]){
    if(activeCheckArr[0] == 1){
      Serial.println("motor1 on");
      m11 = HIGH;
      m12 = LOW; 
    }
    else{
      Serial.println("motor1 off");
      m11 = LOW;
      m12 = LOW;
    }
    if(activeCheckArr[1] == 1){
      Serial.println("motor2 on");
      m21 = HIGH;
      m22 = LOW;
    }
    else{
      Serial.println("motor2 off");
      m21 = LOW;
      m22 = LOW;
    }        
  }      
}
