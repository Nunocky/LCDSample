#ifndef LCD_H
#define LCD_H

#include "stm32l1xx_hal.h"

void LCD_Init();
void LCD_locate(uint8_t row, uint8_t col);
void LCD_putc(uint8_t c);
void LCD_cls();

#endif
