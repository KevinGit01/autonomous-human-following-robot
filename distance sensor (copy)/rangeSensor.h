#ifndef RANGESENSOR_H__
#define RANGESENSOR_H__


#define RFD77402_ADDR 0x4C //7-bit unshifted default I2C Address

#define RFD77402_ADDR 0x4C //7-bit unshifted default I2C Address

//Register addresses
#define RFD77402_ICSR 0x00
#define RFD77402_INTERRUPTS 0x02
#define RFD77402_COMMAND 0x04
#define RFD77402_DEVICE_STATUS 0x06
#define RFD77402_RESULT 0x08
#define RFD77402_RESULT_CONFIDENCE 0x0A
#define RFD77402_CONFIGURE_A 0x0C
#define RFD77402_CONFIGURE_B 0x0E
#define RFD77402_HOST_TO_MCPU_MAILBOX 0x10
#define RFD77402_MCPU_TO_HOST_MAILBOX 0x12
#define RFD77402_CONFIGURE_PMU 0x14
#define RFD77402_CONFIGURE_I2C 0x1C
#define RFD77402_CONFIGURE_HW_0 0x20
#define RFD77402_CONFIGURE_HW_1 0x22
#define RFD77402_CONFIGURE_HW_2 0x24
#define RFD77402_CONFIGURE_HW_3 0x26
#define RFD77402_MOD_CHIP_ID 0x28

#define RFD77402_MODE_MEASUREMENT 0x01
#define RFD77402_MODE_STANDBY 0x10
#define RFD77402_MODE_OFF 0x11
#define RFD77402_MODE_ON 0x12

#define CODE_VALID_DATA 0x00
#define CODE_FAILED_PIXELS 0x01
#define CODE_FAILED_SIGNAL 0x02
#define CODE_FAILED_SATURATED 0x03
#define CODE_FAILED_NOT_NEW 0x04
#define CODE_FAILED_TIMEOUT 0x05

#define I2C_SPEED_STANDARD        100000
#define I2C_SPEED_FAST            400000

#define INT_CLR_REG 1 //tells which register read clears the interrupt (Default: 1, Result Register)
#define INT_CLR 0 << 1 //tells whether or not to clear when register is read (Default: 0, cleared upon register read)
#define INT_PIN_TYPE 1 << 2 //tells whether int is push-pull or open drain (Default: 1, push-pull)
#define INT_LOHI 0 << 3 //tells whether the interrupt is active low or high (Default: 0, active low)

//Setting any of the following bits to 1 enables an interrupt when that event occurs
#define INTSRC_DATA 1 //Interrupt fires with newly available data
#define INTSRC_M2H 0 << 1//Interrupt fires with newly available data in M2H mailbox register
#define INTSRC_H2M 0 << 2//Interrupt fires when H2M register is read
#define INTSRC_RST 0 << 3 //Interrupt fires when HW reset occurs


void rangeInit(void);
unsigned short readRange(void);

#endif
