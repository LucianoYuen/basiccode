#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> 
#include <stdlib.h>
#include <string.h>

char d_1[6]  = "12346";

char d_2[]  = "10100";

int value;

int main(void) {

    printf("total_data_count的值：%d\n", d_1[6]);
    
    printf("total_data_count的值：%d\n", d_1[5]);    
    
	printf("total_data_count的值：%d\n", d_1[4]);  
    
    printf("total_data_count的值：%d\n", d_1[3]); 
    
    printf("total_data_count的值：%d\n", d_1[2]);  
    
    printf("total_data_count的值：%d\n", d_1[1]);
    
    printf("total_data_count的值：%d\n", d_1[0]);
    
    printf("String value = %s, Int value = %d\n", d_2, value);
    
    strcpy(d_2,d_1);
    
    value = atoi(d_2);
    
    printf("String value = %s, Int value = %d\n", d_2, value);
    
    printf("total_data_count的值：%d\n", value);
    
	return 0;
}
