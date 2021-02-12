#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> //uint8_t

#define byte uint8_t

#define LOCATION_I2C_ADDRESS 0x01 
#define I2C_ADDRESS_DEFAULT 75
#define I2C_ADDRESS_JUMPER 74


struct memoryMap {
  byte id;              // Reg: 0x00 - Default I2C Address
  byte firmwareMajor;   // Reg: 0x01 - Firmware Number
  byte firmwareMinor;   // Reg: 0x02 - Firmware Number
  byte X_MSB;           // Reg: 0x03 - Current Joystick Horizontal Position (MSB)
  byte X_LSB;           // Reg: 0x04 - Current Joystick Horizontal Position (LSB)
  byte Y_MSB;           // Reg: 0x05 - Current Joystick Vertical Position (MSB)
  byte Y_LSB;           // Reg: 0x06 - Current Joystick Vertical Position (LSB)
  byte Button_State;    // Reg: 0x07 - Current Button State (clears Reg 0x08)
  byte Button_Status;   // Reg: 0x08 - Indicator for if button was pressed since last
                        //             read of button state (Reg 0x07). Clears after read.
  byte i2cLock;         // Reg: 0x09 - Must be changed to 0x13 before I2C address can be changed.
  byte i2cAddress;      // Reg: 0x0A - Set I2C New Address (re-writable). Clears i2cLock.
};

volatile struct memoryMap registerMap = {
  .id = I2C_ADDRESS_DEFAULT, //Default I2C Address (0x20)
  .firmwareMajor = 0x02, //Firmware version. Helpful for tech support.
  .firmwareMinor = 0x06,
  .X_MSB = 0,
  .X_LSB = 0,
  .Y_MSB = 0,
  .Y_LSB = 0,
  .Button_State = 0x00,
  .Button_Status = 0x00,
  .i2cLock = 0x00,
  .i2cAddress = I2C_ADDRESS_DEFAULT,
};

//This defines which of the registers are read-only (0) vs read-write (1)
struct memoryMap protectionMap = {
  .id = 0x00,
  .firmwareMajor = 0x00,
  .firmwareMinor = 0x00,
  .X_MSB = 0x00,
  .X_LSB = 0x00,
  .Y_MSB = 0x00,
  .Y_LSB = 0x00,
  .Button_State = 0x00,
  .Button_Status = 0x01,
  .i2cLock = 0xFF,
  .i2cAddress = 0xFF,
};



uint8_t EEPROM_Buffer[2] =
{
    0x10, //EEPROM_Buffer[0]
    0x20  //EEPROM_Buffer[1]
};

//Cast 32bit address of the object registerMap with uint8_t so we can increment the pointer
uint8_t *registerPointer = (uint8_t *)&registerMap;
uint8_t *protectionPointer = (uint8_t *)&protectionMap;

volatile byte registerNumber; //Gets set when user writes an address. We then serve the spot the user requested.

int main(void) {
	
	printf("EEPROM_Buffer的值：%lu\n", sizeof(EEPROM_Buffer));
	
	printf("EEPROM_Buffer[0]的值：%d\n", EEPROM_Buffer[0]);
	
	printf("EEPROM_Buffer[1]的值：%d\n", EEPROM_Buffer[1]);
	
	int x = 0;
	
	int temp = 0x07;
	
	registerNumber = 0x08;
	
	*(registerPointer + registerNumber + x) &= ~*(protectionPointer + registerNumber + x); //Clear this register if needed
	
    *(registerPointer + registerNumber + x) |= temp & *(protectionPointer + registerNumber + x); //Or in the user's request (clensed against protection bits)
	
	printf("EEPROM_Buffer[1]的值：%d\n", registerNumber);
	
	printf("EEPROM_Buffer[1]的值：%d\n", *(registerPointer + registerNumber + x));
	
	printf("EEPROM_Buffer[1]的值：%d\n", *(protectionPointer + registerNumber + x));
	
	return 0;
}
