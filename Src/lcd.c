#include "lcd.h"

static void LCD_inst4(uint8_t rs, uint8_t rw, uint8_t data);

static inline void LCD_RS(uint8_t v);
static inline void LCD_RW(uint8_t v);
static inline void LCD_E(uint8_t v);
static inline void LCD_DATA(uint8_t v);



static inline void 
LCD_RS(uint8_t v)
{
  HAL_GPIO_WritePin(GPIOA, LCD_RS_Pin, (v)? GPIO_PIN_SET:GPIO_PIN_RESET);
}

static inline void 
LCD_RW(uint8_t v)
{
}

static inline void 
LCD_E(uint8_t v)
{
  HAL_GPIO_WritePin(GPIOA, LCD_E_Pin, (v)? GPIO_PIN_SET:GPIO_PIN_RESET);
}

static inline void 
LCD_DATA(uint8_t v)
{
  HAL_GPIO_WritePin(GPIOA, LCD_DB7_Pin, (v & 0x8)? GPIO_PIN_SET:GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, LCD_DB6_Pin, (v & 0x4)? GPIO_PIN_SET:GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, LCD_DB5_Pin, (v & 0x2)? GPIO_PIN_SET:GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, LCD_DB4_Pin, (v & 0x1)? GPIO_PIN_SET:GPIO_PIN_RESET);
}

static void 
LCD_inst4(uint8_t rs, uint8_t rw, uint8_t data)
{
  LCD_RS(rs);
  LCD_RW(rw);

  LCD_E(1);
  HAL_Delay(1);
  LCD_DATA(data);
  HAL_Delay(1);
  LCD_E(0);
}


void
LCD_Init() 
{
  HAL_Delay(30);                // (1)

  LCD_inst4(0, 0, 0x03);        // Function set
  HAL_Delay(4);
  LCD_inst4(0, 0, 0x03);
  HAL_Delay(1);
  LCD_inst4(0, 0, 0x03);

  LCD_inst4(0, 0, 0x02); // to 4bit mode
  
  LCD_inst4(0, 0, 0x02); // Function set
  LCD_inst4(0, 0, 0x08);  

  LCD_inst4(0, 0, 0x00); // Display on
  LCD_inst4(0, 0, 0x0C);  

  LCD_inst4(0, 0, 0x00); // Entry mode set
  LCD_inst4(0, 0, 0x06);  

  LCD_cls();
}

void LCD_cls()
{
  LCD_inst4(0, 0, 0x00);
  LCD_inst4(0, 0, 0x01);  
}

void LCD_locate(uint8_t row, uint8_t col)
{
  // TODO IMPLEMENT THIS
  uint8_t value = 0x80;

  if (row) {
    value |= 0x40;
  }

  value |= col; // TODO : colの上限

  // DDRAM Address Set
  LCD_inst4(0, 0, value >> 4);
  LCD_inst4(0, 0, value);  
}

void LCD_putc(uint8_t v)
{
  // TODO IMPLEMENT THIS
  LCD_inst4(1, 0, v >> 4);
  LCD_inst4(1, 0, v);  
}



