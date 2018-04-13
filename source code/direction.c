#include "direction.h"
#include <xc.h>

void dir(){

}

void pwmInit(){

      OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
      OC1CONbits.OCTSEL = 1;   // Use Timer3 for comparison
      OC1RS = 2000;             // duty cycle = OC1RS/(PR3+1) = 50%
      OC1R = 1000;              // initialize before turning OC1 on; afterward it is read-only
      OC1CONbits.ON = 1;       // turn on OC1

      T3CONbits.TCKPS = 0;     // Timer3 prescaler N=1 (1:1)
      PR3 = 3999;              // period = (PR3+1) * N * 12.5 ns = 50 us, 20 kHz
      TMR3 = 0;                // initial TMR3 count is 0
      T3CONbits.ON = 1;        // turn on Timer3

// motor direction control bits
      TRISBbits.TRISB10 = 0;
      TRISBbits.TRISB11 = 0;
      TRISBbits.TRISB12 = 0;
      TRISBbits.TRISB13 = 0;
// motors rotate counter clockwise by default
//
      LATBbits.LATB10 = 1;
      LATBbits.LATB11 = 1;
      LATBbits.LATB12 = 1;
      LATBbits.LATB13 = 1;
}
