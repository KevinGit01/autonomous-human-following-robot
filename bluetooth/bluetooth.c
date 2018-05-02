#include "bluetooth.h"
#include <xc.h>
#include "NU32.h"

void btInit(void){

  U1MODEbits.BRGH = 0;
//  U3BRG = (float)((NU32_SYS_FREQ / 38400) / 16) - 1;
  U1BRG = 520;

  // configure TX & RX pins
  U1STAbits.UTXEN = 1;
  U1STAbits.URXEN = 1;
// turn on UART1
  U1MODEbits.ON = 1;
  TRISBbits.TRISB0 = 0;
  LATBbits.LATB0 = 0;

}

void cmd(void){
    unsigned char data = 0;
  if(U1STAbits.URXDA) { // poll to see if there is data to read in RX FIFO
      data = U1RXREG;
    //  NU32_LED1 = 0;
      if(data == 'w'){
      NU32_LED2 = 0;
      }else if(data == 'a'){
        LATBbits.LATB0 = 1;
      }else if (data == 's') {
        NU32_LED2 = 1;
        NU32_LED1 = 1;
      }else {
      LATBbits.LATB0 = 0;
      NU32_LED2 = 1;
      NU32_LED1 = 1;
      }

  }
}
