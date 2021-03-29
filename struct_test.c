#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> //uint8_t

#define RAM_CMD              3178496UL

typedef struct {
  uint16_t cmd_fifo_wp; /* coprocessor fifo write pointer */
  uint16_t dl_buff_wp;  /* display command memory write pointer */
}Gpu_Hal_Context_t;

Gpu_Hal_Context_t host, *phost;

int main(void) {
	
 phost = &host;

 Gpu_Hal_Updatecmdfifo (phost, 4);
 
 Gpu_Hal_Updatecmdfifo (phost, 4);
 
 Gpu_Hal_Open (phost);
 
 Gpu_Hal_Updatecmdfifo (phost, 8);
 
 Gpu_Hal_Updatecmdfifo (phost, 16);
 
 Gpu_Hal_StartCmdTransfer(phost);
 
 printf("cmdfifo的值：%d\n", (phost->cmd_fifo_wp));
 
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
  

void Gpu_Hal_StartCmdTransfer (Gpu_Hal_Context_t  *host)
{
  host->cmd_fifo_wp + RAM_CMD;
} 
