#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> 
#include <stdlib.h>
#include <string.h>

char d_1[]  = "10000";
char d_2[]  = "10100";
int value;

int main(void) {

    d_1;
    printf("String value = %s, Int value = %d\n", d_1, value);
    strcpy(d_1,d_2);
    value = atoi(d_1);
    printf("String value = %s, Int value = %d\n", d_1, value);
    
    printf("total_data_count的值：%d\n", value);
    
	return 0;
}
