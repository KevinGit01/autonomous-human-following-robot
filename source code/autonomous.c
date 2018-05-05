#include "autonomous.h"
#include "direction.h"
#include "NU32.h"

void autonomous(void){
    unsigned short distance;
    distance = readRange();
    if(distance <= 400 ){
      dir(4);
      _CP0_SET_COUNT(0);
      while(_CP0_GET_COUNT() < 8000000) { ; } // delay 10ms

      if(readRange() > distance){
        dir(4);
      }else{
        while(readRange() <= 400){
        dir(5);
        }
      }

    }else{
      dir(0); //default foward
      speed(v);
      }
}
