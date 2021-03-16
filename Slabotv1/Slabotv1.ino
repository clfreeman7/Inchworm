
#include "MotorActuator.h"
#include "MsTimer2.h"

int key;
// Motors and parameters
const int noofLimbs = 4;
MotorActuator limbMotors[noofLimbs];
int pinA[] = {4, 22, 6, 8};
int pinB[] = {5, 23, 7, 9};
int ePinA[] = {12,10,15,25};
int ePinB[] = {13,11,14,24};
int pinAccelerometers[] = {A13, A14, A15};
void sendAccelerometer();
void sendEncoderData();

void setup() {
  //Serial communication rate
  Serial.begin(115200);

  //    3. Initializing Motors and their parameters - all in milliseconds (ms)
  //    3a. Set pins
  for (int ii = 0; ii < noofLimbs; ii++)
  {
    limbMotors[ii].setPin(pinA[ii], pinB[ii]);
    limbMotors[ii].setState(0);
    limbMotors[ii].setEncoderPins(ePinA[ii],ePinB[ii]);
  }
  //    4. Defining the accelerometer pins
  for (int jj=0; jj<3; jj++)
  {
    pinMode(pinAccelerometers[jj], INPUT);
  }
  MsTimer2::set(10, timerFunction);
  MsTimer2::start();
}

void timerFunction()
{
  for (int ii = 0; ii < noofLimbs; ii++)
  {
    limbMotors[ii].updateEncoderReadings();
  }
}

void loop()
{
  if (Serial.available() > 0)
  {
//    Reading States
    while (Serial.peek() == 'L')
    { //check for the character that signifies that this will be a command
      Serial.read(); //remove the L off the serial buffer
      for (int ii = 0; ii < noofLimbs; ii++)
      {
        Serial.read(); //removes the S
        limbMotors[ii].implementState(Serial.parseInt());
//        Serial.print("S");
//        Serial.print(ii+1);
//        Serial.print(limbMotors[ii].getCurrentState());
      }
    }
    clearBuffer();
  }
  delay(500);
  Serial.print("D");
  sendAccelerometer();
  sendEncoderData();
  Serial.println();
  
}

void clearBuffer()
{
  while (Serial.available() > 0) { //Discard everything that we didn't expect
    Serial.read();
  }
}

void sendAccelerometer()
{
  for (int jj=0; jj<3; jj++)
  {
    Serial.print("A");
    Serial.print(jj+1);
    Serial.print(analogRead(pinAccelerometers[jj]));
  }  
}

void sendEncoderData()
{
  for (int jj=0; jj<noofLimbs; jj++)
  {
    Serial.print("E");
    Serial.print(jj+1);
//    Serial.print(" Value = ");
    Serial.print(limbMotors[jj].getEncoderReadings());
  }  
}

