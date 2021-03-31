#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> //uint8_t

#define RAM_CMD              3178496UL

typedef struct {
  uint16_t cmd_fifo_wp; /* coprocessor fifo write pointer */
  uint16_t dl_buff_wp;  /* display command memory write pointer */
}Gpu_Hal_Context_t;

Gpu_Hal_Context_t host, *phost;

// host 放struct Gpu_Hal_Context_t 各內數值 (沒有數值)
// *phost 指向struct Gpu_Hal_Context_t 的指標
// phost = &host; 把放struct Gpu_Hal_Context_t 的地址值給phost

int main(void) {
	
 phost = &host;
 
 Gpu_Hal_Updatecmdfifo (&host, 4);
 
 Gpu_Hal_Updatecmdfifo (&host, 8);
 
 Gpu_Hal_Updatecmdfifo (&host, 12);
 
 //printf("cmdfifo的值：%d\n", (&host));
 //printf("cmdfifo的值：%d\n", (phost));
 //printf("cmdfifo的值：%d\n", (*phost));
 //printf("cmdfifo的值：%d\n", (host));  
  
 return 0;
}

void Gpu_Hal_Updatecmdfifo (Gpu_Hal_Context_t *phost, uint32_t count)
{
  Gpu_Hal_Open(phost, count);
}  
 
 
void Gpu_Hal_Open (Gpu_Hal_Context_t *host, uint32_t count)
{
  /* initialize the context valriables */
  //host->cmd_fifo_wp = host->dl_buff_wp = 0;
  host->cmd_fifo_wp  = (host->cmd_fifo_wp + count);
  printf("cmdfifo的值：%d\n", (host ->cmd_fifo_wp));
}
