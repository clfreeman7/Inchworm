#include <Timer.h>
#include "Timer.h"

#define FREQUENCY 200
#define arrLen 33
#define START_BYTE1 3
#define START_BYTE2 31

Timer tt;
byte Data[arrLen];
unsigned long tic0, toc0, dt0, tic1, toc1, dt1, tic2, toc2, dt2;
int alertPin = 10;

// C module union uses the same memory space to store two data types (float and type in this case).
// The new defined data type fVal stores a float as a series of bytes. Both the original float and
// individual bytes are accessible.
typedef union {
  unsigned long dt;
  char bytes[4];
} fVal;

// Objects of type fVal will store each dt reading as both floats and bytes.
fVal packedFloat0;
fVal packedFloat1;
fVal packedFloat2;

void falling0()
{
  toc0 = micros();
  dt0 = toc0 - tic0;
  packedFloat0.dt = dt0;
}

void falling1()
{
  toc1 = micros();
  dt1 = toc1 - tic1;
  packedFloat1.dt = dt1;
}

void falling2()
{
  toc2 = micros();
  dt2 = toc2 - tic2;
  packedFloat2.dt = dt2;
}

void rising0()
{
  tic0 = micros();
}

void rising1()
{
  tic1 = micros();
}

void rising2()
{
  tic2 = micros();
}

void setup() {
  // Run the DAQ loop at a set frequency.
  Serial.begin(115200);
  pinMode(alertPin,INPUT);
  tt.every(1000/FREQUENCY, DAQ);

  // Assign the start byte values to the first two elements of the data array.
  // This will notify the Python DAQ program on the PC to start reading from the serial port. 
  Data[0] = START_BYTE1;
  Data[1] = START_BYTE2;

  attachInterrupt (0, rising0, RISING);  // attach interrupt handler
  attachInterrupt (1, falling0, FALLING); // attach interrupt handler
  attachInterrupt (2, rising1, RISING);  // attach interrupt handler
  attachInterrupt (3, falling1, FALLING); // attach interrupt handler
  attachInterrupt (4, rising2, RISING);  // attach interrupt handler
  attachInterrupt (5, falling2, FALLING); // attach interrupt handler
  
}

void DAQ() {
  //int tic = micros();
  // Read all four analog readings from the ADXL.
  int x1 = analogRead(A0);
  int y1 = analogRead(A1);
  int z1 = analogRead(A2);
  
  int x2 = analogRead(A3);
  int y2 = analogRead(A4);
  int z2 = analogRead(A5);

  int x3 = analogRead(A6);
  int y3 = analogRead(A7);
  int z3 = analogRead(A8);

  int x4 = analogRead(A9);
  int y4 = analogRead(A10);
  int z4 = analogRead(A11);
  
  // Convert each analog reading from an integer value (0 to 1023) to a high and low byte value.
  Data[2] = highByte(x1);
  Data[3] = lowByte(x1);
  Data[4] = highByte(y1);
  Data[5] = lowByte(y1);
  Data[6] = highByte(z1);
  Data[7] = lowByte(z1);

  Data[8] = highByte(x2);
  Data[9] = lowByte(x2);
  Data[10] = highByte(y2);
  Data[11] = lowByte(y2);
  Data[12] = highByte(z2);
  Data[13] = lowByte(z2);

  Data[14] = highByte(x3);
  Data[15] = lowByte(x3);
  Data[16] = highByte(y3);
  Data[17] = lowByte(y3);
  Data[18] = highByte(z3);
  Data[19] = lowByte(z3);

  Data[20] = highByte(x4);
  Data[21] = lowByte(x4);
  Data[22] = highByte(y4);
  Data[23] = lowByte(y4);
  Data[24] = highByte(z4);
  Data[25] = lowByte(z4);

  Data[26] = packedFloat1.bytes[1];
  Data[27] = packedFloat1.bytes[0];

  Data[28] = packedFloat0.bytes[1];
  Data[29] = packedFloat0.bytes[0];

  Data[30] = packedFloat2.bytes[1];
  Data[31] = packedFloat2.bytes[0];
  Data[32] = byte(digitalRead(10));  
  
  //Write the data array to the serial port. The Python program will take over from here.
  Serial.write(Data,arrLen);  
}

void loop(){
  tt.update();
}
