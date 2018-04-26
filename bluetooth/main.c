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
  U1BRG = 520;

  // configure TX & RX pins
  U1STAbits.UTXEN = 1;
  U1STAbits.URXEN = 1;

// turn on UART1
  U1MODEbits.ON = 1;
  char message[MAX_MESSAGE_LENGTH];
  TRISBbits.TRISB0 = 0;

  while(1){
      unsigned char data = 0;
      if(U1STAbits.URXDA) { // poll to see if there is data to read in RX FIFO
          data = U1RXREG;
        //  NU32_LED1 = 0;
          if(data == 0x0f){
          NU32_LED2 = 0;
          }else if(data == 0xff){
            LATBbits.LATB0 = 1;
          }else {
          LATBbits.LATB0 = 0;
          NU32_LED2 = 1;
          }

          /*else if(data = 0xff){
          NU32_LED1 = 0;
          }else if(data = 0x11){
          NU32_LED1 = 1;
          NU32_LED2 = 1;
        }*/
      }



    }

  return 0;
}
