#include "autonomous.h"


void auto(void){
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
