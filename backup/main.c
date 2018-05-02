#include "NU32.h"
#include "direction.h"
#include <stdio.h>


#define BUF_SIZE 200
#define NU32_SYS_FREQ 80000000ul
#define MAX_MESSAGE_LENGTH 10


int main(){
  char buffer[BUF_SIZE];

  NU32_Startup();
  NU32_LED1 = 1;
  NU32_LED2 = 1;

  U1MODEbits.BRGH = 0;
//  U3BRG = (float)((NU32_SYS_FREQ / 38400) / 16) - 1;
  U1BRG = 129;

  // configure TX & RX pins
  U1STAbits.UTXEN = 1;
  U1STAbits.URXEN = 1;

// turn on UART1
  U1MODEbits.ON = 1;
  char message[MAX_MESSAGE_LENGTH];

  while(1){
      char data = 0;
      if(U1STAbits.URXDA) { // poll to see if there is data to read in RX FIFO
          data = U1RXREG;
          NU32_LED1 = 0;
          if(data == 0){
          NU32_LED2 = 0;

          }else{
          NU32_LED2 = 1;
        }
      }

      sprintf(message,data);
      NU32_WriteUART3(message);                     // send message back
      NU32_WriteUART3("\r\n");



    }

  return 0;
}
