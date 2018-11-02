


#include "SSD1306_Atmega128.h"

u8g2_t u8g2;
//u8g2_t u8g2_ks0108;

int main(void)
{
	volatile int i=0,j=0;
	
	DDRD=0x88;
	PORTD=0x70;
	
	init_ssd1306();
	//u8g2_Setup_ks0108_128x64_f(&u8g2_ks0108,U8G2_R0,u8x8_byte_ks0108,ks0108_gpio_init)
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_hw_i2c, gpio_and_delay_atmega128);
	u8g2_SetFont(&u8g2,u8g2_font_ncenB08_tf);
	u8g2_ClearBuffer(&u8g2);
	u8g2_DrawStr(&u8g2,0,30,"Ready To Go!!");
	u8g2_SendBuffer(&u8g2);
    while (1)
    {
	    switch(PIND&0x70)
	    {
		    case 0x60:
		    PORTD|=(1<<7);
			if(i<64) i+=2;
			else i=0;
			u8g2_ClearBuffer(&u8g2);
			u8g2_DrawFrame(&u8g2,0,0,128,64);
			u8g2_DrawStr(&u8g2,j,i,"Hi");
			u8g2_SendBuffer(&u8g2);
		    _delay_ms(50);
		    break;
			
			case 0x50:
			PORTD|=(1<<7);
			if(j<128) j+=2;
			else j=0;
			u8g2_ClearBuffer(&u8g2);
			u8g2_DrawFrame(&u8g2,0,0,128,64);
			u8g2_DrawStr(&u8g2,j,i,"Hi");
			u8g2_SendBuffer(&u8g2);
		    _delay_ms(50);
			break;
			
		    default:
		    PORTD&=~(1<<7);
		    _delay_ms(50);
		    break;
	    }
    }
}
