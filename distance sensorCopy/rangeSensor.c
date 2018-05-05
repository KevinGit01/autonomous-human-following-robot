#include "rangeSensor.h"

#define slaveAddr 0x4C
void rangeInit(void){

    i2c_master_setup();

    /* pmu on
    i2c_master_start();                   // start
    i2c_master_send(slaveAddr<<1|0);       // OP + W: R/W = 0 = write
    i2c_master_send(0x14);                // range sensor addr
    i2c_master_send(0x0600);                //active mode
    i2c_master_stop();
    */

    //go to stand by
    i2c_master_start();
    i2c_master_send(slaveAddr<<1|0);
    i2c_master_send(0x04);
    i2c_master_send(0x90);
    i2c_master_stop();

    i2c_master_start();
    i2c_master_send(slaveAddr<<1|0);
    i2c_master_send(0x1C);
    i2c_master_send(0x65);                
    i2c_master_stop();

  /*  i2c_master_start();                   // start
    i2c_master_send(slaveAddr<<1|0);       // OP + W: R/W = 0 = write
    i2c_master_send(0x04);                // ADDR
    i2c_master_send(0x81);                 //single measurement
    i2c_master_stop();
*/

    i2c_master_start();                   // start
    i2c_master_send(slaveAddr<<1|0);       // OP + W: R/W = 0 = write
    i2c_master_send(0x1C);                // ADDR
    i2c_master_send(0x65);                 //single measurement
    i2c_master_stop();

}


unsigned int getID(void){
  unsigned int id;
  i2c_master_start(); // make the start bit
  i2c_master_send(slaveAddr<<1|0); // write the address, shifted left by 1, or'ed with a 0 to indicate writing
  i2c_master_send(0x28); // the register to read from
  i2c_master_stop(); // make the stop bit
  i2c_master_start(); // make the start bit
  i2c_master_send(slaveAddr<<1|1);
  unsigned char LSB = i2c_master_recv(); // save the value returned
  i2c_master_ack(0); // make the ack so the slave knows we got it
  unsigned char MSB = i2c_master_recv();
  i2c_master_ack(1);
  i2c_master_stop(); // make the stop bit
  id = MSB << 8| LSB;
  return id;
}

unsigned int readRange(void){
    unsigned int distance;
    i2c_master_start(); // make the start bit
    i2c_master_send(slaveAddr<<1|0); // write the address, shifted left by 1, or'ed with a 0 to indicate writing
    i2c_master_send(0x08); // the register to read from
    i2c_master_stop(); // make the stop bit
    i2c_master_start(); // make the start bit
    i2c_master_send(slaveAddr<<1|1);
    unsigned char LSB = i2c_master_recv(); // save the value returned
    i2c_master_ack(0); // make the ack so the slave knows we got it
    unsigned char MSB = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop(); // make the stop bit

    distance = MSB << 8 | LSB;
    distance >>= 2;
    distance &= 0x07FF;
    return distance;
}
