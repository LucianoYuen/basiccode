#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> //uint8_t
 
#define byte uint8_t

#define EEPROM2_READ 0x03  // read data from memory
#define EEPROM2_WREN 0x06  // set the write enable latch
#define EEPROM2_WRITE 0x02 // write data to memory array
#define EEPROM2_RDSR 0x05  // read STATUS register

#define EEPROM2_ADDRBYTES 3
uint8_t addressBuffer[EEPROM2_ADDRBYTES];

void addressAssign(uint8_t *addressBuffer, unsigned long byteAddr);

int main(void) {

addressAssign(addressBuffer,0x10AB01);

return 0;
}

void addressAssign(uint8_t *addressBuffer, unsigned long byteAddr) //(addressBuffer = 3, byteAddr = 0x10AB01);
{
	int           i       = 0;
	int           j       = EEPROM2_ADDRBYTES - 1;
	unsigned long address = byteAddr;

	while (address > 0) {
		addressBuffer[j - i] = address & 0xFF;
    
		printf("i的值：%d\n", address & 0xFF);
    
		printf("i的值：%d\n", i);
		
		printf("addressBuffer的值：%d\n", addressBuffer[i]);
		
		i++;
		
		printf("address的值：%d\n", address);
		
		address >>= 8;
		
		printf("address的值：%d\n", address);
	}
}
