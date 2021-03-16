/*
Notes:
1. To change variable value in function, assign global variable to passed variable or directly change value of global variable in function
*/

#include <Timer.h>
Timer tt;
// Mode
int mode = 1;                     // Control mode. 0 for ball mode (next revision) or 1 for slab mode.
// Variable Declarations
int a1 = 1;                       // Analog pin that reads accelerometer i that corresponds to motor i
int a2 = 2;                       // ""
int read1 = analogRead(A1);       // analogRead(ai)
int read2 = analogRead(A2);       // ""
int i,j,k,m,n;                    // Counters used in for loops
int critAngle1 = 290;             // Critical angle representing transition from State 0 to State 1
int critAngle2 = 290;             // ""
String in;                        // Input string that represents series of nodes in simple cycle (N1 = a, N2 = b, N3 = c, N4 = d, ...)
//int Input[4];                     // Array of node integers in simple cycle, e.g. "12341"  <-- R2! try to eliminate this!
unsigned int len;                 // Length of Input String. 
int arr[4];                       // Array that stores parsed Input string
bool M11,M12,M21,M22;             // Digital logic level for TA8428K motor driver, e.g. m12 = motor 1, pin 2 logic level (HIGH or LOW)
int isActive1 = 0;                // Activation state for each limb
int isActive2 = 0;                // ""
int activeArr[2];                 // Array of activation states isActive1 & isActive2
int activeCheckArr[2];            // Array of activation states to check against activeArr to determine whether to activate/deactive motor
int nextState[25];                    // Stores arr[i+1]. Used to compare current state to next state
char char_array[0];               // Array of characters in input string "in".
int a,b;                          //test acc
int limbs = 2;                    // number of limbs on robot


// Function Declarations
void takeReading();
void getNodeSeries();
void getCurrentState();
void getNextState();
void goToState();


// Setup Loop. Assign key variables and call control functions
void setup() {
  // put your setup code here, to run once:
  switch(mode){
    case 0:
      // Ball mode code (Next revision)
      Serial.begin("Ball Mode");
    case 1:
      Serial.println("Flat Mode");
      Serial.begin(9600);
      pinMode(13,OUTPUT);
      pinMode(8,OUTPUT);
      pinMode(12,OUTPUT);
      pinMode(7,OUTPUT);
      digitalWrite(12,LOW);
      digitalWrite(7,LOW);
      tt.every(10,takeReading);
      isActive1 = 0;
      isActive2 = 0;
      int a,b;
      for(m=0;m<5;m++){
        a = analogRead(A1);
        b = analogRead(A2);
        Serial.print(a);Serial.print("\t");
        Serial.print(b);Serial.print("\n");
      }
      Serial.print("i:\t");Serial.println(i);
      getNodeSeries(in,len);
      for (i=0;i<in.length();i++){
        getCurrentState(read1, read2, isActive1, isActive2, critAngle1, critAngle2);      // add i as j,k,l,m,n,etc
        getNextState(i, in, nextState[i], activeCheckArr[0], activeCheckArr[1], len);
        goToState(limbs, activeArr[0], activeArr[1], activeCheckArr[0], activeCheckArr[1], M11, M12, M21, M22);
      }
    default:
      Serial.println("Mode selection Failed");
      break;
  }
}





// After driving everything, print accelerometer readings. 
// Not critical to final project. May change later.
void loop() {
  tt.update();
}


void takeReading(){
  a = analogRead(a1);
  b = analogRead(a2);
}


// Read and parse Input string, store in array
void getNodeSeries(String &Input, unsigned int &arrLen){
  while (!Serial.available()){
    Serial.println("waiting for input...");
    delay(1000);
  }
  while (Serial.available()){
    Input = Serial.readString();
  }
  Serial.println(Input);
  arrLen = Input.length();
  Serial.print("size of string:\t");
  for(int ii=1; ii<=arrLen; ii++){
    Serial.print((int)Input[ii-1]-48);
    if (ii==arrLen){
      Serial.println();
    }
    else{
      Serial.print(",");
    }
  }
  Serial.print("size of string:\t");
  Serial.println(arrLen);
}





// Detects robot's current state, e.g. 0,1
void getCurrentState(int &r1, int &r2, int &iA1, int &iA2, int &cA1, int &cA2){
  Serial.println("begin getCurrentState");
  r1 = analogRead(A1);
  r2 = analogRead(A2);
  Serial.print("acc1:\t");Serial.println(r1);
  Serial.print("acc2:\t");Serial.println(r2);
  Serial.print("isActive1:\t");Serial.println(iA1);
  Serial.print("isActive2:\t");Serial.println(iA2);
  Serial.print("critAngle1:\t");Serial.println(cA1);
  Serial.print("critAngle2:\t");Serial.println(cA2);
  if (r1 >= cA1){
    iA1 = 0;
    Serial.println("Limb1:\tState 0");
  }
  else if (r1 < cA1){
    iA1 = 1;
    Serial.println("Limb1:\tState 1");
  }
  else{
    Serial.println("ERROR: Cannot determine Limb 1's state.");    
  }
  if (r2 >= cA2){
    iA2 = 0;
    Serial.println("Limb2:\tState 0");
  }
  else if (r2 < cA2){
    iA2 = 1;
    Serial.println("Limb2:\tState 1");
  }
  else{
    Serial.println("ERROR: Cannot determine Limb 2's state.");  
  }
}





// Go to next element in input node array to get the state the robot should drive to next. 
void getNextState(int &j, String &Input, int &nS, int &aCA0, int &aCA1, unsigned int &arrLen){
  Serial.println("begin getNextState");  
//  nS = atoi(Input[j]);
  nS = (int)Input[j]-48;
  Serial.print("check for i:\t");Serial.println(i);
  Serial.print("nextState:\t");Serial.println(nS);
  switch(nS){
    case 1:
      Serial.println("case1");
      aCA0 = 0;
      aCA1 = 0;
      Serial.println(aCA0);
      Serial.println(aCA1);
      break;
    case 2:
      Serial.println("case2");
      aCA0 = 0;
      aCA1 = 1;
      Serial.println(aCA0);
      Serial.println(aCA1);
      break;
    case 3:
      Serial.println("case3");
      aCA0 = 1;
      aCA1 = 0;
      Serial.println(aCA0);
      Serial.println(aCA1);
      break;      
    case 4:
      Serial.println("case4");
      aCA0 = 1;
      aCA1 = 1;
      Serial.println(aCA0);
      Serial.println(aCA1);
      break;      
    default:
      Serial.println("End of simple cycle");
      break;
  }
}





// Compare current state to next state.
// For each motor, check to see if activation mode (ON,OFF) changes from current state to next state.
// If activation mode changes, turn motor off or on until the goal state is reached.
void goToState(int &Limbs, int &aA0, int &aA1, int &aCA0, int &aCA1, bool &m11, bool &m12, bool &m21, bool &m22){
  Serial.println("begin goToState");
  int nextNArr[Limbs] = {aCA0, aCA1};
  int activeArr[Limbs] = {aA0, aA1};
  int p1 = 13;
  int p2 = 8;
  bool dW[Limbs];
  for(n=0;n<Limbs;n++){
    Serial.println("for loop");
    if(nextNArr[n]==activeArr[n]){
      //doNothing
      Serial.print("Limb ");Serial.print(n+1);Serial.println(" at correct state.");
    }
    else if(nextNArr[n]!=activeArr[n] && nextNArr[n]==0){
      dW[n] = LOW;
      Serial.print("Limb ");Serial.print(n+1);Serial.println(" deactivate.");
    }
    else if(nextNArr[n]!=activeArr[n] && nextNArr[n]==1){
      dW[n] = HIGH;
      Serial.print("Limb ");Serial.print(n+1);Serial.println(" activate.");
    }    
    else{
      Serial.println("Error: goToState() Failed");
    }
  }
  while(nextNArr[0]!=activeArr[0] || nextNArr[1]!=activeArr[1]){
    digitalWrite(p1,dW[0]);
    digitalWrite(p2,dW[1]);
    Serial.println("driving robot");
    delay(1000);
  }
}
