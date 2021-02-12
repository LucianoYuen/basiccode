#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> //uint8_t
 
#define byte uint8_t
 
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
 
#define TXBUFFERSIZE	(COUNTOF(aTxBuffer) - 1)
 
uint8_t aTxBuffer[] = " ****I2C_TwoBoards communication based on Polling****  ****I2C_TwoBoards communication based on Polling****  ****I2C_TwoBoards communication based on Polling**** ";

int main(void) {
 
	printf("TXBUFFERSIZE的值：%d\n", TXBUFFERSIZE);
 
	return 0;
}









