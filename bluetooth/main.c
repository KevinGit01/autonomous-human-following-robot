#include "NU32.h"
#include "bluetooth.h"
#include <stdio.h>


#define BUF_SIZE 200
#define NU32_SYS_FREQ 80000000ul
#define MAX_MESSAGE_LENGTH 10


int main(){

  NU32_LED1 = 1;
  NU32_LED2 = 1;

  btInit();

  while(1){

    cmd();



    }

  return 0;
}
