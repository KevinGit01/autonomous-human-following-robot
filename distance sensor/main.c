#include "NU32.h"
#include "i2c_master_noint.h"
#include <stdio.h>
//#include "rangeSensor.h"
//#include <stdio.h>

#define MAX_MESSAGE_LENGTH 200
#define slaveAddr 0x4C

int main(void) {
  char message[MAX_MESSAGE_LENGTH];
  unsigned short distance = 0;
  unsigned char status = 0;
  rangeInit();
  NU32_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {




  //  distance = readRange();
    distance = readRange();
    sprintf(message,"distance: %d",distance);
    NU32_WriteUART3(message);                     // send message back
    NU32_WriteUART3("\r\n");
    distance = getID();
    sprintf(message,"distance: %d",distance);
    NU32_WriteUART3(message);                     // send message back
    NU32_WriteUART3("\r\n");
  }
  return 0;
}
