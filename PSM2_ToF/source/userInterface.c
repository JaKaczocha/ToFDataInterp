#include "userInterface.h"
#include <stdbool.h>
#include <stdio.h>

#include "lcd.h"

struct Settings {
	int16_t settingCounter; // pref const
	int16_t colorModeCounter; // pref const
	int16_t colorMode;
	uint16_t minValue;
	uint16_t maxValue;
	uint16_t freq;
};

void interfaceActivity(volatile struct Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation, VL53L5CX_Configuration * const Dev ) {
	while(1) {

		switch(*rotation) {
		case 0: // colorMode
			if(*clicked == 2) {

				updateColorMode(settings, clicked, rotation);
				*clicked = 1;
			}
			break;
		case 1: // minValue
			if(*clicked == 2) {

				updateMinValue(settings, clicked, rotation);
				*clicked = 1;
			}
			break;
		case 2: // maxValue
			if(*clicked == 2) {

				updateMaxValue(settings, clicked, rotation);
				*clicked = 1;
			}
			break;
		case 3: // Frequency
			if(*clicked == 2) {

				updateFreq(settings, clicked, rotation);
				//vl53l5cx_set_ranging_frequency_hz(Dev, settings->freq);
				*clicked = 1;
			}
			break;

		case 4: // return
			if(*clicked == 2) {

				*clicked = 0;

				return;
			}
			break;

		}
		if(*rotation < 0) {
			*rotation = settings->settingCounter - 1;
		}
		*rotation = *rotation % settings->settingCounter;
		displaySettings(settings,*rotation,-1,-1,false);
	}

}

void updateMaxValue(volatile struct  Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation) {
	int16_t rotationTmp = *rotation;
	uint16_t clickedTmp = *clicked;

	*clicked = 0;
	*rotation = 0;

	while(true) { // TODO algorithm
		switch(*clicked) {
		case 0: //1000
			if(*rotation > 0) {
				settings->maxValue = settings->maxValue + 1000 <= 4000 ? settings->maxValue + 1000 : settings->maxValue;
			}
			else if( *rotation < 0) {
				settings->maxValue = settings->maxValue - 1000 > settings->minValue ? settings->maxValue - 1000 : settings->maxValue;
			}
			break;
		case 1: //0100
			if(*rotation > 0) {
				settings->maxValue = settings->maxValue + 100 <= 4000 ? settings->maxValue + 100 : settings->maxValue;
			}
			else if( *rotation < 0) {
				settings->maxValue = settings->maxValue - 100 > settings->minValue ? settings->maxValue - 100 : settings->maxValue;
			}
			break;
		case 2: //0010
			if(*rotation > 0) {
				settings->maxValue = settings->maxValue + 10 <= 4000 ? settings->maxValue + 10 : settings->maxValue;
			}
			else if( *rotation < 0) {
				settings->maxValue = settings->maxValue - 10 > settings->minValue ? settings->maxValue - 10 : settings->maxValue;
			}
			break;
		case 3: //0001
			if(*rotation > 0) {
				settings->maxValue = settings->maxValue + 1 <= 4000 ? settings->maxValue + 1 : settings->maxValue;
			}
			else if( *rotation < 0) {
				settings->maxValue = settings->maxValue - 1 > settings->minValue ? settings->maxValue - 1 : settings->maxValue;
			}
			break;
		case 4:
			*rotation = rotationTmp;
			*clicked = clickedTmp;
			return;
		}
		*rotation = 0;
		displaySettings(settings,rotationTmp,-1,*clicked,true);
	}
}

void updateMinValue(volatile struct Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation) {
	int16_t rotationTmp = *rotation;
	uint16_t clickedTmp = *clicked;

	*clicked = 0;
	*rotation = 0;

	while(true) { // TODO algorithm
		switch(*clicked) {
		case 0: //1000
			if(*rotation > 0) {
				settings->minValue = settings->minValue + 1000 < settings->maxValue ? settings->minValue + 1000 : settings->minValue;
			}
			else if( *rotation < 0) {
				settings->minValue = settings->minValue - 1000 >= 1 ? settings->minValue - 1000 : settings->minValue;
			}
			break;
		case 1: //0100
			if(*rotation > 0) {
				settings->minValue = settings->minValue + 100 < settings->maxValue ? settings->minValue + 100 : settings->minValue;
			}
			else if( *rotation < 0) {
				settings->minValue = settings->minValue - 100 >= 1 ? settings->minValue - 100 : settings->minValue;
			}
			break;
		case 2: //0010
			if(*rotation > 0) {
				settings->minValue = settings->minValue + 10 < settings->maxValue ? settings->minValue + 10 : settings->minValue;
			}
			else if( *rotation < 0) {
				settings->minValue = settings->minValue - 10 >= 1 ? settings->minValue - 10 : settings->minValue;
			}
			break;
		case 3: //0001
			if(*rotation > 0) {
				settings->minValue = settings->minValue + 1 < settings->maxValue ? settings->minValue + 1 : settings->minValue;
			}
			else if( *rotation < 0) {
				settings->minValue = settings->minValue - 1 >= 1 ? settings->minValue - 1 : settings->minValue;
			}
			break;
		case 4:
			*rotation = rotationTmp;
			*clicked = clickedTmp;
			return;
		}
		*rotation = 0;
		displaySettings(settings,rotationTmp,*clicked,-1,true);
	}
}

void updateColorMode(volatile struct Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation) {
	int16_t rotationTmp = *rotation;
	uint16_t clickedTmp = *clicked;

	*clicked = 0;
	*rotation = 0;


	while(true) { // TODO algorithm
		switch(*clicked) {
		case 0: //1000
			if(*rotation > 0) {
				settings->colorMode = (settings->colorMode + 1) % settings->colorModeCounter;
			}
			else if(*rotation < 0) {
				settings->colorMode = (settings->colorMode - 1) > 0 ? settings->colorMode - 1 : settings->colorModeCounter - 1;
			}
			*rotation = 0;

			break;
		case 1:
			*rotation = rotationTmp;
			*clicked = clickedTmp;
			return;
		}
		*rotation = 0;
		displaySettings(settings,rotationTmp,-1,-1,true);
	}
}

void updateFreq(volatile struct  Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation) {
	int16_t rotationTmp = *rotation;
	uint16_t clickedTmp = *clicked;

	*clicked = 0;
	*rotation = 0;

	while(true) { // TODO algorithm
		switch(*clicked) {
		case 0: //10
			if(*rotation > 0) {
				settings->freq = settings->freq + 10 <= 60 ? settings->freq + 10 : settings->freq;
			}
			else if( *rotation < 0) {
				settings->freq = settings->freq - 10 > 0 ? settings->freq - 10 : settings->freq;
			}
			break;
		case 1: //01
			if(*rotation > 0) {
				settings->freq = settings->freq + 1 <= 60 ? settings->freq + 1 : settings->freq;
			}
			else if( *rotation < 0) {
				settings->freq = settings->freq - 1 > 0 ? settings->freq - 1 : settings->freq;
			}
			break;
		case 2:
			*rotation = rotationTmp;
			*clicked = clickedTmp;
			return;
		}
		*rotation = 0;
		displaySettings(settings,rotationTmp,-1,*clicked,true);
	}
}


void displaySettings(volatile struct Settings* const settings, uint8_t choosenSetting, uint8_t updateMin,uint8_t updateMax,bool selected) {
	char buffor[30];
	uint16_t color = 0xFFFF;

	LCD_Clear(0x0000);
	switch(settings->colorMode) {
	case 0:
		sprintf(buffor, "  mode: Color Bilinear");
		break;
	case 1:
		sprintf(buffor, "  mode: Grey Bilinear");
		break;
	case 2:
		sprintf(buffor, "  mode: Color Nearest");
		break;
	case 3:
		sprintf(buffor, "  mode: Grey Nearest");
		break;
	case 4:
		sprintf(buffor, "  mode: Color Bicubic");
		break;
	case 5:
		sprintf(buffor, "  mode: Grey Bicubic");
	}
	if(choosenSetting == 0) {
		buffor[0] = '>';
	}
	LCD_Puts(10, 10, buffor, (choosenSetting == 0 && selected) ? 0xffe0 : color);

	sprintf(buffor, "  min: %04d", settings->minValue);
	if(choosenSetting == 1) {
		buffor[0] = '>';
	}
	LCD_Puts(10, 30, buffor, (choosenSetting == 1 && selected) ? 0xffe0 : color);
	if(choosenSetting == 1) {
		sprintf(buffor, "                "   );
		buffor[7+updateMin] = '_';
		LCD_Puts(10, 22, buffor, 0xffff);
		LCD_Puts(10, 32, buffor, 0xffff);
	}


	sprintf(buffor, "  max: %04d", settings->maxValue);
	if(choosenSetting == 2) {
		buffor[0] = '>';
	}
	LCD_Puts(10, 50, buffor, (choosenSetting == 2 && selected) ? 0xffe0 : color);
	if(choosenSetting == 2) {
			sprintf(buffor, "                "   );
			buffor[7+updateMax] = '_';
			LCD_Puts(10, 42, buffor, 0xffff);
			LCD_Puts(10, 52, buffor, 0xffff);
	}

	sprintf(buffor, "  freq: %02d", settings->freq);
	if(choosenSetting == 3) {
		buffor[0] = '>';
	}
	LCD_Puts(10, 70, buffor, (choosenSetting == 3 && selected) ? 0xffe0 : color);
	if(choosenSetting == 3) {
			sprintf(buffor, "                "   );
			buffor[8+updateMax] = '_';
			LCD_Puts(10, 62, buffor, 0xffff);
			LCD_Puts(10, 72, buffor, 0xffff);
	}


	sprintf(buffor, "		RETURN		");
	if(choosenSetting == 4) {
		buffor[0] = '>';
	}
	LCD_Puts(10, 90, buffor, (choosenSetting == 4 && selected) ? 0xffe0 : color);

	LCD_GramRefresh();
}
