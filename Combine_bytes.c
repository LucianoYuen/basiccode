#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> //uint8_t
 
#define byte uint8_t

uint8_t buf[12];

int16_t val;

int main(void) {
 
 buf[0] = 0xF0; //11110000
 buf[1] = 0x90; //10010000
 
 printf("buf[0]的值：%d\n", buf[0]);
 
 printf("buf[1]：%d\n", buf[1]);
	
 val = ((int16_t)buf[0] << 4) | (buf[1] >> 4);
 
 printf("buf[0]的值：%d\n", buf[0] << 4);
 printf("buf[1]的值：%d\n", buf[1] >> 4);
 
 printf("val：%d\n", val); //111100001001
 
 return 0;
}
