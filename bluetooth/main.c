#include "NU32.h"
#include "direction.h"
#include <stdio.h>


#define BUF_SIZE 200

int main(){
  char buffer[BUF_SIZE];
  NU32_Startup();

  NU32_LED1 = 1;
  NU32_LED2 = 1;

  __builtin_disable_interrupts();
  pwmInit();
  __builtin_enable_interrupts();
  TRISBbits.TRISB1 = 1;
  //dir(1);

  while(1){
    if(PORTBbits.RB1 == 0){
    dir(0);
    }
  }
  return 0;
}
