#include "rangeSensor.h"
#include "NU32.h"

void i2cWrite2Byte(unsigned char registerAddr, unsigned short value){
  i2c_master_start();
  i2c_master_send(RFD77402_ADDR<<1|0);
  i2c_master_send(value & 0xFF);
  i2c_master_send(value >> 8);
  i2c_master_stop();
}

unsigned char i2cRead1Byte (unsigned char registerAddr){
  unsigned char data;
  i2c_master_start(); // make the start bit
  i2c_master_send(RFD77402_ADDR<<1|0); // write the address, shifted left by 1, or'ed with a 0 to indicate writing
  i2c_master_send(registerAddr); // the register to read from
  i2c_master_stop(); // make the stop bit
  i2c_master_start(); // make the start bit
  i2c_master_send(RFD77402_ADDR<<1|1);
  data = i2c_master_recv(); // save the value returned
  i2c_master_ack(1);
  i2c_master_stop(); // make the stop bit
  return data;
}

void i2cWrite(unsigned char registerAddr, unsigned char value){
  i2c_master_start();
  i2c_master_send(RFD77402_ADDR<<1|0);
  i2c_master_send(registerAddr);
  i2c_master_send(value);
  i2c_master_stop();
}


unsigned int i2cRead(unsigned char registerAddr){
  unsigned int data;
  i2c_master_start(); // make the start bit
  i2c_master_send(RFD77402_ADDR<<1|0); // write the address, shifted left by 1, or'ed with a 0 to indicate writing
  i2c_master_send(registerAddr); // the register to read from
  i2c_master_stop(); // make the stop bit
  i2c_master_start(); // make the start bit
  i2c_master_send(RFD77402_ADDR<<1|1);
  unsigned char LSB = i2c_master_recv(); // save the value returned
  i2c_master_ack(0); // make the ack so the slave knows we got it
  unsigned char MSB = i2c_master_recv();
  i2c_master_ack(1);
  i2c_master_stop(); // make the stop bit
  data = MSB << 8| LSB;
  return data;
}


unsigned int getID(void){
  unsigned int id;
  id = i2cRead(RFD77402_MOD_CHIP_ID);
  return id;
}


void rangeInit(void){
    i2c_master_setup();
    getID();
    i2cWrite(RFD77402_COMMAND,0x90); //go to stand by
    uint8_t setting = i2cRead1Byte(RFD77402_ICSR);
    setting &= 0b11110000; //clears writable bits
    setting |= INT_CLR_REG | INT_CLR | INT_PIN_TYPE | INT_LOHI; //change bits to enable interrupt
    i2cWrite(RFD77402_ICSR, setting);
    setting = i2cRead1Byte(RFD77402_INTERRUPTS);
    setting &= 0b00000000; //Clears bits
    setting |= INTSRC_DATA | INTSRC_M2H | INTSRC_H2M | INTSRC_RST; //Enables interrupt when data is ready
    i2cWrite(RFD77402_INTERRUPTS, setting);

    i2cWrite(RFD77402_CONFIGURE_I2C, 0x65); //0b.0110.0101 = Address increment, auto increment, host debug, MCPU debug

    //Set initialization - Magic from datasheet. Write 0x05 to 0x15 location.
    i2cWrite2Byte(RFD77402_CONFIGURE_PMU, 0x0500); //0b.0000.0101.0000.0000 //Patch_code_id_en, Patch_mem_en

    //go to off mode
    i2cWrite(RFD77402_COMMAND, 0x91);
  //  _CP0_SET_COUNT(0);
  //  while(_CP0_GET_COUNT() < 400000) { ; } // delay 10ms
    //check if it's in off mode?
    i2cWrite2Byte(RFD77402_CONFIGURE_PMU, 0x0600);
    //go to on mode
    i2cWrite(RFD77402_COMMAND, 0x92);

    //set peak
    unsigned char userPeak = 0x0E;
    uint16_t configValuePeak = i2cRead(RFD77402_CONFIGURE_A); //Read
    configValuePeak &= ~0xF000;// Zero out the peak configuration bits
    configValuePeak |= (uint16_t)userPeak << 12; //Mask in user's settings
    i2cWrite2Byte(RFD77402_CONFIGURE_A, configValuePeak); //Write in this new value
    //set threshold
    unsigned char userThres = 0x01;
    uint16_t configValueThres = i2cRead(RFD77402_CONFIGURE_A); //Read
    configValueThres &= ~0x0F00;// Zero out the threshold configuration bits
    configValueThres |= userThres << 8; //Mask in user's settings
    i2cWrite2Byte(RFD77402_CONFIGURE_A, configValueThres); //Write in this new value

    i2cWrite2Byte(RFD77402_CONFIGURE_B, 0x10FF); //Set valid pixel. Set MSP430 default config.
    i2cWrite2Byte(RFD77402_CONFIGURE_HW_0, 0x07D0); //Set saturation threshold = 2,000.
    i2cWrite2Byte(RFD77402_CONFIGURE_HW_1, 0x5008); //Frequecy = 5. Low level threshold = 8.
    i2cWrite2Byte(RFD77402_CONFIGURE_HW_2, 0xA041); //Integration time = 10 * (6500-20)/15)+20 = 4.340ms. Plus reserved magic.
    i2cWrite2Byte(RFD77402_CONFIGURE_HW_3, 0x45D4); //Enable harmonic cancellation. Enable auto adjust of integration time. Plus reserved magic.

    //go to stand by
    i2cWrite(RFD77402_COMMAND,0x90); //go to stand by

    //go to stand by
    i2cWrite(RFD77402_COMMAND,0x90); //go to stand by
    i2cWrite2Byte(RFD77402_CONFIGURE_PMU, 0x0500);

    //go to off mode
    i2cWrite(RFD77402_COMMAND,0x91);
    i2cWrite2Byte(RFD77402_CONFIGURE_PMU, 0x0600); //MCPU_Init_state, Patch_mem_en
    i2cWrite(RFD77402_COMMAND, 0x92 );

}




unsigned short readRange(void){
    unsigned short distance;
    uint8_t x = 0;
    i2cWrite(RFD77402_COMMAND,0x81);

    //Read ICSR Register - Check to see if measurement data is ready
  for (x ; x < 10 ; x++)
  {
    if ( (i2cRead(RFD77402_ICSR) & (1 << 4)) != 0){
      distance = i2cRead(RFD77402_RESULT);
      distance = (distance >> 2) & 0x07FF;
      return distance;
    } //Data is ready!
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT() < 400000) { ; } // delay 10ms
   //Suggested timeout for status checks from datasheet
  }

  return 0xff;
}
