#include "servo.h"
#include <xc.h>

//define dead end 1 as 157
//define dead end 2 as 781
//0 degree is found as 396


void servoInit(void){
  OC5CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
  OC5CONbits.OCTSEL = 0;   // Use Timer2 for comparison
  OC5RS = 0;             // duty cycle = OC1RS/(PR3+1) = 50%
  OC5R = 0;              // initialize before turning OC1 on; afterward it is read-only
  OC5CONbits.ON = 1;       // turn on OC1

  T2CONbits.TCKPS = 0b111;     // Timer3 prescaler N=1 (1:1)
  PR2 = 6249;              // period = (PR3+1) * N * 12.5 ns = 50 us, 20 kHz
  TMR2 = 0;                // initial TMR3 count is 0
  T2CONbits.ON = 1;

}

void servoPosition(int deg){
    deg = (deg/120.0)*6250;
    OC5RS = deg;
}
