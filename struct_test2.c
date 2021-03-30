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

 printf("cmdfifo的值：%d\n", (&host));
 printf("cmdfifo的值：%d\n", (phost));
  printf("cmdfifo的值：%d\n", (*phost));
  printf("cmdfifo的值：%d\n", (host));  
  
 
 return 0;
}

void Gpu_Hal_Updatecmdfifo (Gpu_Hal_Context_t *host, uint32_t count)
{
  host->cmd_fifo_wp  = (host->cmd_fifo_wp + count);
  
  printf("cmdfifo的值：%d\n", (host ->cmd_fifo_wp));
}  
 
 
void Gpu_Hal_Open (Gpu_Hal_Context_t *host)
{
  /* initialize the context valriables */
  host->cmd_fifo_wp = host->dl_buff_wp = 0;
}
