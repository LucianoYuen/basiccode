
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> //uint8_t

#define I2C_BUF_LEN (32u)

uint32_t i;
uint32_t error_status = 0;
uint8_t t_cnt;
uint32_t data_index;


int main(void) {
	
	data_index = 0;
	
	uint32_t total_data_count = 64;
	
	while(total_data_count > 0)
	{
	printf("total_data_count的值：%d\n", total_data_count);
	
	t_cnt = (total_data_count > (I2C_BUF_LEN - 2))? (I2C_BUF_LEN - 2) : total_data_count;
	
	printf("t_cnt的值：%d\n", t_cnt);
	
	total_data_count -= t_cnt;
	
	data_index += t_cnt;
	
	}
	return 0;
}
