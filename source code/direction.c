#include "direction.h"
#include <xc.h>
#include "bluetooth.h"

//dir(0) forward
//dir(1) backford
//dir(2) left
//dir(3) right

void dir(int direction){

  switch (direction) {
    case 0://forward
    {
      LATBbits.LATB10 = 0;
      LATBbits.LATB11 = 1;
      LATBbits.LATB12 = 1;
      LATBbits.LATB13 = 0;
      break;
    }

    case 1://backford
    {
      LATBbits.LATB10 = 1;
      LATBbits.LATB11 = 0;
      LATBbits.LATB12 = 0;
      LATBbits.LATB13 = 1;
      break;
    }

    case 2://turn left
    {
      LATBbits.LATB10 = 0;
      LATBbits.LATB11 = 1;
      LATBbits.LATB12 = 1;
      LATBbits.LATB13 = 0;
      vLeft = v;
      vRight = v;
      speedRight(v);
      if(v-50 <= 0){
        vLeft = 0;
      }
      speedLeft(vLeft);
      break;
    }

    case 3://turn right
    {
      LATBbits.LATB10 = 1;
      LATBbits.LATB11 = 0;
      LATBbits.LATB12 = 0;
      LATBbits.LATB13 = 1;
      vLeft = v;
      vRight = v;
      speedLeft(v);
      if(v-50 <= 0){
        vRight = 0;
      }
      speedRight(vRight);
      break;
    }

    case 4://rotate left
    {
      LATBbits.LATB10 = 0;
      LATBbits.LATB11 = 0;
      LATBbits.LATB12 = 0;
      LATBbits.LATB13 = 0;
      vLeft = v;
      vRight = v;
      speedRight(v);
      if(v-50 <= 0){
        vLeft = 0;
      }
      speedLeft(vLeft);
      break;
    }

    case 5://rotate right
    {
      LATBbits.LATB10 = 1;
      LATBbits.LATB11 = 1;
      LATBbits.LATB12 = 1;
      LATBbits.LATB13 = 1;
      vLeft = v;
      vRight = v;
      speedLeft(v);
      if(v-50 <= 0){
        vRight = 0;
      }
      speedRight(vRight);
      break;
    }

    default:{
      LATBbits.LATB10 = 1;
      LATBbits.LATB11 = 1;
      LATBbits.LATB12 = 1;
      LATBbits.LATB13 = 1;

    }

  }
}

void speed(int speed){
    speed = speed*40;
    OC1RS = speed;
    OC2RS = speed;
    }

// motor 1 and 4
void speedLeft(int speed){
    speed = speed*40;
    OC1RS = speed;
    }
// motor 2 and 3
void speedRight(int speed){
    speed = speed*40;
    OC2RS = speed;
    }


int speedUp(int speed){
    speed += 10;
    if(speed >= 100){
      speed = 100;
    }
    return speed;
    }


int speedDown(int speed){
    speed -= 10;
    if(speed <= 0){
      speed = 0;
    }
    return speed;
    }

void pwmInit(){

      //motor 1 and 4 (1 with a black type on it)
      OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
      OC1CONbits.OCTSEL = 1;   // Use Timer3 for comparison
      OC1RS = 0;             // duty cycle = OC1RS/(PR3+1) = 50%
      OC1R = 2000;              // initialize before turning OC1 on; afterward it is read-only
      OC1CONbits.ON = 1;       // turn on OC1

      T3CONbits.TCKPS = 0;     // Timer3 prescaler N=1 (1:1)
      PR3 = 3999;              // period = (PR3+1) * N * 12.5 ns = 50 us, 20 kHz
      TMR3 = 0;                // initial TMR3 count is 0
      T3CONbits.ON = 1;        // turn on Timer3

      //motor 2 and 3
      OC2CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC2CON bits are defaults
      OC2CONbits.OCTSEL = 1;   // Use Timer3 for comparison
      OC2RS = 0;             // duty cycle = OC1RS/(PR3+1) = 50%
      OC2R = 2000;              // initialize before turning OC2 on; afterward it is read-only
      OC2CONbits.ON = 1;       // turn on OC2

      T3CONbits.TCKPS = 0;     // Timer3 prescaler N=1 (1:1)
      PR3 = 3999;              // period = (PR3+1) * N * 12.5 ns = 50 us, 20 kHz
      TMR3 = 0;                // initial TMR3 count is 0
      T3CONbits.ON = 1;

// motor direction control bits
// pin 10 to 13
      TRISBbits.TRISB10 = 0;
      TRISBbits.TRISB11 = 0;
      TRISBbits.TRISB12 = 0;
      TRISBbits.TRISB13 = 0;
// motors rotate counter clockwise by default
//

}
