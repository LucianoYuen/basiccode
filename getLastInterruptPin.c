#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> //uint8_t

#define MCP23017_INT_ERR 255 //!< Interrupt error

uint8_t getLastInterruptPin();

int main(void) {

	//printf("regAddr的值：%d\n", X2);
	uint8_t A = getLastInterruptPin();
	
	printf("A的值：%d\n", A);
	
	while(0)
	{
	
	}
	return 0;
}

uint8_t bitForPin(uint8_t pin) 
{ 
  return pin % 8; 
}

uint8_t bitWrite(char x, char n, char value){
{
   if (value)
      x |= (1 << n);
   else
      x &= ~(1 << n);
}
return x;
}

char bitRead(char x, char n) {
   return (x & (1 << n)) ? 1 : 0;
}

uint8_t getLastInterruptPin() {
	
  uint8_t intf;
  // try port A
  intf = 0;
  for (int i = 0; i < 8; i++)
    if (bitRead(intf, i))
    
        return i;
    
  // try port B
  intf = 0;
  for (int i = 0; i < 8; i++)
    if (bitRead(intf, i))
    
        return i + 8;
    

  return MCP23017_INT_ERR;
}
