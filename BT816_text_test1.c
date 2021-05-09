#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINES   7
#define LINE_STARTPOS	1
#define LINE_ENDPOS	7

struct Notepad_buffer {
	char *temp;
	char notepad[MAX_LINES];
}Buffer;

int Read_Keypad = 0;
int Disp_pos = 0;
int line = 0;
int key = 0;

int main(void) {
	
do{	
	key = Read_Keypad;
	if(key != 255)
	{
	Buffer.notepad[line] = Read_Keypad;
	printf("Buffer.notepad[line]：%d\n", Buffer.notepad[line]);
	Read_Keypad++;
	line++;
	Disp_pos++;
	}
	
	if(Disp_pos == 8)
	{
		if((Buffer.notepad[0] == 0) && (Buffer.notepad[1] == 1) && (Buffer.notepad[2] == 2))
		{
		printf("test OK!\n");
		}
	Disp_pos = 0;
	}

}while(Disp_pos);
}
