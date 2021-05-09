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

int Read_Keypad = 1;
int Disp_pos = 0;
int line = 0;


int main(void) {
	
do{	
	Buffer.notepad[line] = Read_Keypad;
	printf("Buffer.notepad[line]：%d\n", Buffer.notepad[line]);
	Read_Keypad++;
	line++;
	Disp_pos++;

	if(Disp_pos == 8)
	{
	Disp_pos = 0;
	}

}while(Disp_pos);

	if((Buffer.notepad[0] == 1) && (Buffer.notepad[1] == 1) && (Buffer.notepad[2] == 3))
	{
	printf("test OK!\n");
	}

}
