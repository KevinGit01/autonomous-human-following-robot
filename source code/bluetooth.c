#include "bluetooth.h"
#include <xc.h>
#include "NU32.h"
#include "direction.h"

void btInit(void){

  U1MODEbits.BRGH = 0;
//  U3BRG = (float)((NU32_SYS_FREQ / 38400) / 16) - 1;
  U1BRG = 520;

  // configure TX & RX pins
  U1STAbits.UTXEN = 1;
  U1STAbits.URXEN = 1;
// turn on UART1
  U1MODEbits.ON = 1;

}

void cmd(void){
  unsigned char data = 0;
  if(U1STAbits.URXDA) { // poll to see if there is data to read in RX FIFO
      data = U1RXREG;
    //  NU32_LED1 = 0;
      if(data == 'w'){
        dir(0);
        speed(55);
      }else if(data == 'a'){
        dir(2);
        speed(55);
      }else if (data == 's') {
        dir(1);
        speed(55);
      }else if(data == 'd'){
        dir(3);
        speed(55);
      }else{
        speed(0);
      }
  }
}
