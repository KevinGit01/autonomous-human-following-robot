#include "NU32.h"              // constants, functions for startup and UART

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
  __builtin_enable_interrupts();

  return 0;
}
