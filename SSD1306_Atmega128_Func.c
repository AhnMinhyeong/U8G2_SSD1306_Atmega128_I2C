

#include "SSD1306_Atmega128.h"

void init_ssd1306(void)
{
	char data[25];
	
	data[0]=0xae;
	data[1]=0x00;
	data[2]=0x10;
	data[3]=0x40;
	data[4]=0xb0;
	data[5]=0x81;
	data[6]=0xff;
	data[7]=0xa1;
	data[8]=0xa6;
	data[9]=0xc9;
	data[10]=0xa8;
	data[11]=0x3f;
	data[12]=0xd3;
	data[13]=0x00;
	data[14]=0xd5;
	data[15]=0x80;
	data[16]=0xd9;
	data[17]=0xf1;
	data[18]=0xda;
	data[19]=0x12;
	data[20]=0xdb;
	data[21]=0x40;
	data[22]=0x8d;
	data[23]=0x14;
	data[24]=0xaf;
	i2c_initialize();

	_delay_ms(100);
	PORTD&=~(1<<3);
	_delay_ms(1);
	PORTD|=(1<<3);

	for(int i=0;i<25;i++)
	{
		i2c_Start(OLED_ADDR);
		i2c_write(0x00);
		i2c_write(data[i]);
		i2c_Stop();
	}
}

uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	uint8_t *data;

	switch(msg)
	{
		case U8X8_MSG_BYTE_SEND:
		data = (uint8_t *)arg_ptr;
		while( arg_int > 0 )
		{
			i2c_write(*data);
			data++;
			arg_int--;
		}
		
		break;
		
		case U8X8_MSG_BYTE_INIT:
		i2c_initialize();
		break;
		case U8X8_MSG_BYTE_SET_DC:
		break;
		case U8X8_MSG_BYTE_START_TRANSFER:
		if(u8x8->display_info->i2c_bus_clock_100kHz >= 4)
		{
			TWBR=0x12;
		}
		i2c_Start(OLED_ADDR);
		//i2c_write_byte(u8x8_GetI2CAddress(u8x8));
		//i2c_write_byte(u8x8, 0x078);
		break;
		case U8X8_MSG_BYTE_END_TRANSFER:
		i2c_Stop();
		break;
		default:
		return 0;
	}
	return 1;
}

uint8_t gpio_and_delay_atmega128(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	switch(msg)
	{
		case U8X8_MSG_GPIO_AND_DELAY_INIT:	// called once during init phase of u8g2/u8x8
		
		break;							// can be used to setup pins
		case U8X8_MSG_DELAY_NANO:			// delay arg_int * 1 nano second
		break;
		case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
		_delay_us(0.1);
		break;
		case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
		_delay_us(10);
		break;
		case U8X8_MSG_DELAY_MILLI:			// delay arg_int * 1 milli second
		_delay_ms(arg_int);
		break;

	}
	return 1;
}