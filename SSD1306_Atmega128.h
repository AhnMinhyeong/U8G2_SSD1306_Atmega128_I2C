

#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "u8g2.h"
#define OLED_ADDR (0x3d<<1)

void init_ssd1306(void);
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t gpio_and_delay_atmega128(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

