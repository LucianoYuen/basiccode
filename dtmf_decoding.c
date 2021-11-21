#include <stdio.h>
#include <stdint.h>

#define DEV_DTMFDECODER_NIBBLE_MASK                0x0F
#define DEV_DTMFDECODER_NUM_OF_TONES               16

static const uint8_t dev_ascii_matrix[ DEV_DTMFDECODER_NUM_OF_TONES ][ 2 ] =
{
    { 0x01, 0x31 }, // 1
    { 0x02, 0x32 }, // 2
    { 0x03, 0x33 }, // 3
    { 0x04, 0x34 }, // 4
    { 0x05, 0x35 }, // 5
    { 0x06, 0x36 }, // 6
    { 0x07, 0x37 }, // 7
    { 0x08, 0x38 }, // 8
    { 0x09, 0x39 }, // 9
    { 0x0A, 0x30 }, // 0
    { 0x0B, 0x2A }, // *
    { 0x0C, 0x23 }, // #
    { 0x0D, 0x41 }, // A
    { 0x0E, 0x42 }, // B
    { 0x0F, 0x43 }, // C
    { 0x00, 0x44 }, // D
};


int main(void) {
	
	uint8_t tone_bin = 0x10; //接收到的2進制數值
  uint8_t cnt;
  uint8_t decoded_data;
    
	tone_bin &= DEV_DTMFDECODER_NIBBLE_MASK;
	
	printf("tone_bin = %d\n", tone_bin);

	for ( cnt = 0 ; cnt < DEV_DTMFDECODER_NUM_OF_TONES ; cnt++ ) {
		
		printf("cnt = %d\n", cnt);
		
        if ( dev_ascii_matrix[ cnt ][ 0 ] == tone_bin ) {
        	
            decoded_data = dev_ascii_matrix[ cnt ][ 1 ];
            
            printf("decoded_data = %d\n", decoded_data);
            
        }

	}

	printf("decoded_data = %d\n", decoded_data);

	return 0;
}
