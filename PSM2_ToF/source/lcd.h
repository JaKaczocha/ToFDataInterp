/*
 * lcd.h
 *
 *  Created on: 12 gru 2021
 *      Author: daniel
 */

#ifndef LCD_H_
#define LCD_H_

#include <math.h>
#include "fsl_spi.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

#define LCD_WIDTH  160
#define LCD_HEIGHT 128

#define LCD_RST_0 GPIO_PinWrite(BOARD_INITPMODPINS_LCD_RST_GPIO, BOARD_INITPMODPINS_LCD_RST_PORT, BOARD_INITPMODPINS_LCD_RST_PIN, 0)
#define LCD_RST_1 GPIO_PinWrite(BOARD_INITPMODPINS_LCD_RST_GPIO, BOARD_INITPMODPINS_LCD_RST_PORT, BOARD_INITPMODPINS_LCD_RST_PIN, 1)

#define LCD_DC_0 GPIO_PinWrite(BOARD_INITPMODPINS_LCD_DC_GPIO, BOARD_INITPMODPINS_LCD_DC_PORT, BOARD_INITPMODPINS_LCD_DC_PIN, 0)
#define LCD_DC_1 GPIO_PinWrite(BOARD_INITPMODPINS_LCD_DC_GPIO, BOARD_INITPMODPINS_LCD_DC_PORT, BOARD_INITPMODPINS_LCD_DC_PIN, 1)

#define PI	3.14159265358979f

void LCD_Init(SPI_Type *base);
void LCD_GramRefresh (void);

void LCD_Clear(uint16_t color);
void LCD_Set_Bitmap(uint16_t *data);
void LCD_Set_Icon(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *data);
void LCD_Draw_Point(uint16_t x, uint16_t y, uint16_t color);
uint16_t LCD_Get_Point(uint16_t x, uint16_t y);
void LCD_Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_Draw_DotLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_Draw_Rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_Draw_FillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_Draw_Circle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color);
void LCD_Draw_Arc(uint16_t x, uint16_t y, uint16_t radius, uint16_t angle1, uint16_t angle2,  uint16_t color);
void LCD_Puts(uint16_t x, uint16_t y, char *text, uint16_t color);

void LCD_7seg(uint16_t x, uint16_t y, int32_t value, int8_t digits, uint16_t color);
void LCD_7dot(uint16_t x, uint16_t y, uint16_t color);

#endif /* LCD_H_ */
