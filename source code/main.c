#include "NU32.h"              // constants, functions for startup and UART
#include "direction.h"
#include "bluetooth.h"
#include "rangeSensor.h"



#define MAX_MESSAGE_LENGTH 200

void __ISR(_UART_1_VECTOR, IPL1SOFT) IntUart1Handler(void) {
  //  TRISBbits.TRISB0 = 0;
  //  LATBbits.LATB0 ^= 1;
  //the serial com port has to end without line end
    cmd();
    IFS0bits.U1RXIF = 0;
}


int main(void) {
  NU32_Startup();   // cache on, interrupts on, LED/button init, UART init
  NU32_LED1 = 1;
  NU32_LED2 = 1;
  __builtin_disable_interrupts();
  pwmInit();
  btInit();
  rangeInit();
  __builtin_enable_interrupts();

  while(1){
	
    unsigned short distance;
    distance = readRange();
    if(distance <= 200 ){
      speed(0);
    }else{
      if(robotStatus == 'w'){
        dir(0);
        speed(v);
      }else if(robotStatus == 'a'){
        dir(2);
      }else if (robotStatus == 's') {
        dir(1);
        speed(v);
      }else if(robotStatus == 'd'){
        dir(3);
      }else if (robotStatus == 'j') {
        speed(v);
      }else if (robotStatus == 'l') {
        speed(v);
      }else if (robotStatus == 'q') {
        dir(4);
      }else if (robotStatus == 'e') {
        dir(5);
      }else{
        speed(0);
      }
    }

  }

  return 0;

}
