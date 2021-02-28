#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> //uint8_t

uint8_t bitWrite(char x, char n, char value);

int main(void) {

	uint8_t T = 65;
	
	uint8_t X = bitWrite(T, 0, 0);

	printf("regAddr的值：%d\n", X);
	
	while(0)
	{
	
	}
	return 0;
}

uint8_t bitWrite(char x, char n, char value){
{
   if (value)
      x |= (1 << n);
   else
      x &= ~(1 << n);
}

char bitRead(char x, char n) {
   return (x & (1 << n)) ? 1 : 0;
}
return x;
}
