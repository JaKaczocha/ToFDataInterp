#include "userInterface.h"
#include <stdbool.h>
#include <stdio.h>

#include "lcd.h"


uint8_t updateMode(uint8_t * const mode, bool* const nextMode, const uint16_t modeCounter) {
    *mode += *nextMode;
    *nextMode = 0;
    if(*mode >= modeCounter) {
        *mode = 0;
    }
}

uint8_t updateValue(const uint8_t mode, int8_t * const changeDirection,int16_t * const colorMode,uint16_t * 
    const minValue, uint16_t * const maxValue, uint8_t * const valueJump, const uint16_t colorModeCounter, const uint16_t modeCounter) {
	if(mode == 0) {
		*changeDirection = 0;
		return 0;
	}

    if(changeDirection) {
        switch(mode) {
            case 1: //draw option
                *colorMode += *changeDirection;
                if(*colorMode < 0) {
                   *colorMode = colorModeCounter - 1;
                } else if ( *colorMode >= colorModeCounter) {
                    *colorMode = 0;
                }
                break;
            case 2: //min value option ..
                *minValue += (*changeDirection) * (*valueJump);
                if(*minValue >= *maxValue) {
                    *minValue = 1;
                }
                break;
            case 3: // max value option
                *maxValue += (*changeDirection) * (*valueJump);
                if(*maxValue > 4000 || *maxValue <= *minValue) {
                    *maxValue = 4000;
                }
                break;
            case 4: // value jump option
                *valueJump += *changeDirection;
                break;
        }
        *changeDirection = 0;
    }
}

uint8_t displayInterface(char* const buff,const char* const colorModeName, const uint16_t minValue, const uint16_t maxValue, const uint8_t valueJump, const uint8_t mode) {

	sprintf(buff, "        SETTINGS    ");
	LCD_Puts(10,5, buff, 0xffff);
	LCD_Draw_Line(10, 18, LCD_WIDTH - 10, 18, 0xffff);
	LCD_Puts(10,25,colorModeName,0xffff);
    sprintf(buff, "minDistance:  %05d", minValue);
    LCD_Puts(10,45,buff,0xffff);
    sprintf(buff, "maxDistance:  %05d", maxValue);
    LCD_Puts(10,65,buff,0xffff);
    sprintf(buff, "valueJump:     %03d", valueJump);
    LCD_Puts(10,85,buff,0xffff);
    sprintf(buff, ">");
    LCD_Puts(1, 25 + 20*(mode-1), buff,0xffff);
}
