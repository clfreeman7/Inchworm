/*ECE 587 Lab Assignment 2
  Author: Michael Maynard
  CWID: 11367642
  created on: 12 Feb 2020
  updated last: 13 Feb 2020
*/

#include <avr/wdt.h>
void setup() {
  noInterrupts();
  /* Turn off Global Interrupt */
  wdt_disable();
  wdt_reset();
  /* Clear WDRF(watchdog sys. reset flag) in MCUSR */
  MCUSR &= ~(1 << WDRF);
  wdt_enable(WDTO_4S);
  interrupts();
  Serial.begin(9600);
  Serial.setTimeout(100);
  Serial.println("Enter any interger into the serial Monitor.");// put your setup code here, to run once:
  for (int i = 3; i < 13; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  float usrReactionTime = 0;
  //  static boolean timeout = false;
  static unsigned long startMillis = 0;
  static unsigned long currentMillis = 0;
  currentMillis = millis();
  if (Serial.available() > 0) {
    wdt_reset();
    /* Reset Watchdog Timer */
    //      currentMillis = millis();
    int strVal = Serial.parseInt();
//    Serial.print(strVal);
    usrReactionTime = (float)(currentMillis - startMillis) / 1000.0;
    startMillis = currentMillis;
    
    if (strVal < 16 && strVal >= 0) {
      Serial.print("Input Recieved: ");
      Serial.print(strVal, HEX);
      //      Serial.print("Input Recieved: ");
      //      Serial.print(strVal, HEX);
      Serial.print("\t User Response Time: ");
      Serial.println(usrReactionTime);
      setDisplay(strVal);
    }
  }
}


void initReset(void) {
  setDisplay(1);
  digitalWrite(8, HIGH);
  delay(500);
  digitalWrite(8, LOW);
  delay(500);
  wdt_reset();
}

//    asm volatile ("  jmp 0");
//}
/*The interrupt service routine for the WDT when WDIE is enabled
  This ISR is required inorder for the WDT interrupt to function
  Correctly.*/
ISR (WDT_vect) {
  initReset();
}
/* The Function setDsiplay() updates the Hexadecimal values being displayed on both
   the 7-Segment Display & Serial Monitor */
void setDisplay(int ledDispCnt) {
  // Ensures data is within the displayable range 0-15
  int sevenSegDisp[] = {11, 10, 9, 8, 7, 6, 5, 4, 3};
  boolean onOff[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  switch (ledDispCnt) {
    case 0:  //  Pin config required to display  to display "0"
      onOff[4] = 1;
      onOff[5] = 1;
      onOff[0] = 1;
      break;
    case 1:  //  Pin config required to display "1"
      onOff[1] = 1;
      onOff[3] = 1;
      onOff[4] = 1;
      onOff[5] = 1;
      onOff[7] = 1;
      onOff[8] = 1;
      onOff[0] = 1;
      break;
    case 2:  //  Pin config required to display "2"
      onOff[3] = 1;
      onOff[5] = 1;
      onOff[6] = 1;
      onOff[0] = 1;
      break;
    case 3:  //  Pin config required to display "3"
      onOff[3] = 1;
      onOff[5] = 1;
      onOff[7] = 1;
      onOff[0] = 1;
      break;
    case 4:  // Pin config required to display "4"
      onOff[1] = 1;
      onOff[5] = 1;
      onOff[7] = 1;
      onOff[8] = 1;
      onOff[0] = 1;
      break;
    case 5:  // Pin config required to display "5"
      onOff[2] = 1;
      onOff[5] = 1;
      onOff[7] = 1;
      onOff[0] = 1;
      break;
    case 6:  // Pin config required to display "6"
      onOff[2] = 1;
      onOff[5] = 1;
      onOff[0] = 1;
      break;
    case 7:  //  Pin config required to display "7"
      onOff[3] = 1;
      onOff[4] = 1;
      onOff[5] = 1;
      onOff[7] = 1;
      onOff[8] = 1;
      onOff[0] = 1;
      break;
    case 8:  //  Pin config required to display "8"
      onOff[5] = 1;
      onOff[0] = 1;
      break;
    case 9:  //  Pin config required to display "9"
      onOff[5] = 1;
      onOff[7] = 1;
      onOff[0] = 1;
      break;
    case 10: //  Pin config required to display uppercase "A."
      onOff[8] = 1;
      onOff[0] = 1;
      break;
    case 11: //  Pin config required to display uppercase "B."
      onOff[0] = 1;
      break;
    case 12: //  Pin config required to display uppercase "C."
      onOff[2] = 1;
      onOff[4] = 1;
      onOff[6] = 1;
      onOff[0] = 1;
      break;
    case 13: //  Pin config required to display uppercase "D."
      onOff[4] = 1;
      //      onOff[5] = 1;
      onOff[0] = 1;
      break;
    case 14: //  Pin config required to display uppercase "E."
      onOff[2] = 1;
      onOff[6] = 1;
      onOff[0] = 1;
      break;
    case 15: //  Pin config required to display uppercase "F."
      onOff[2] = 1;
      onOff[6] = 1;
      onOff[8] = 1;
      onOff[0] = 1;
      break;
    case 16:
      onOff[0] = 1;
      onOff[1] = 1;
      onOff[2] = 1;
      onOff[3] = 1;
      onOff[5] = 1;
      onOff[6] = 1;
      onOff[7] = 1;
      break;

    default:  //  The defualt case simply turns all LED's off
      // All stay low
      onOff[0] = 0;
      break;
  }
  /* For-Loop updates the 7 segment display pins state with the
     control array onOff defined by the specified case */
  for (int idx = 9; idx > 0; idx--) {
    digitalWrite(sevenSegDisp[idx - 1], onOff[(9 - idx)]);
  }
  return;
}
