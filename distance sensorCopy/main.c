#include "NU32.h"
#include <stdio.h>
#define MAX_MESSAGE_LENGTH 200

int main(void) {
  char message[MAX_MESSAGE_LENGTH];
  int distance = 6;
  NU32_Startup(); // cache on, interrupts on, LED/button init, UART init

  while (1) {
    distance = readRange();
    sprintf(message,"distance: %d",distance);
    NU32_WriteUART3(message);                     // send message back
    NU32_WriteUART3("\r\n");

  }
  return 0;
}
