/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    PSM2_ToF.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
#include "lcd.h"

#include "vl53l5cx_api.h"
#include "platform.h"

#include "colorConverter.h"
#include "interpolation.h"

int status;

int pixelArr[8][8];
int greyPixelArr[8][8];

volatile int IntCount;
uint8_t p_data_ready;
VL53L5CX_Configuration 	Dev;
VL53L5CX_ResultsData 	Results;
uint8_t resolution, isAlive;
uint16_t idx;
uint16_t new_min = 0;
uint16_t new_max = 255;
uint16_t old_min = 1;
uint16_t old_max = 4000;

//INTERPOLACJA LINOWA ŻEBY ZWIEKSZYC ROZDZIELCZOSC!!!!!!!!!11!1


void delay_ms(uint32_t delay)
{
	for(volatile int j=delay*100000; j > 0;j--);
}

int convertToGrayScale(int pixel)
{
	pixel = ((pixel - old_min)/ (old_max - old_min)) * (new_max - new_min) + new_min;
	return pixel;
}

void cbToF_Ready(pint_pin_int_t pintr, uint32_t pmatch_status) {

	status = vl53l5cx_get_resolution(&Dev, &resolution);
	status = vl53l5cx_get_ranging_data(&Dev, &Results);

	for(int j = 0; j < resolution/8;j++) {
		for(int i = 0; i < resolution/8;i++) {


			pixelArr[j][i] = Results.distance_mm[(VL53L5CX_NB_TARGET_PER_ZONE * i)+(8*j)];
			//PRINTF("%4d ", Results.distance_mm[(VL53L5CX_NB_TARGET_PER_ZONE * i)+(8*j)]);


			//PRINTF("%4d ", pixelArr[j][i]);
		}
		//PRINTF("\r\n");
	}

	//PRINTF("--------------------------------------\r\n");
}

volatile void drawPixels(uint16_t width, uint16_t height, uint8_t x, uint8_t y)
{

	for(int i=0; i<width; i++)
	{
		for(int j=0; j<height; j++)
		{
			greyPixelArr[j][i] = convertToGrayScale(pixelArr[j][i]);
			LCD_Draw_FillRect(x*i, y*j, x*(i+1), y*(j+1), greyPixelArr[j][i]);
		}
	}

	for(int j = 0; j < width;j++) {
			for(int i = 0; i < height;i++) {
				//PRINTF("%4d ", Results.distance_mm[(VL53L5CX_NB_TARGET_PER_ZONE * i)+(8*j)]);
				PRINTF("%4d ", greyPixelArr[j][i]);
			}
			PRINTF("\r\n");
		}
	PRINTF("--------------------------------------\r\n");

}

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	PRINTF("Run\n\r");

	Dev.platform.i2c = FLEXCOMM4_PERIPHERAL;
	Dev.platform.address = 0x29;

	GPIO_PinWrite(BOARD_TOFCAMPINS_TRST_GPIO, BOARD_TOFCAMPINS_TRST_PORT, BOARD_TOFCAMPINS_TRST_PIN, 0);
	delay_ms(20);

	GPIO_PinWrite(BOARD_TOFCAMPINS_TLPn_GPIO, BOARD_TOFCAMPINS_TLPn_PORT, BOARD_TOFCAMPINS_TLPn_PIN, 0);
	delay_ms(20);

	GPIO_PinWrite(BOARD_TOFCAMPINS_TLPn_GPIO, BOARD_TOFCAMPINS_TLPn_PORT, BOARD_TOFCAMPINS_TLPn_PIN, 1);
	delay_ms(20);

	status = vl53l5cx_is_alive(&Dev, &isAlive);


	if(!isAlive && status==0) {

		PRINTF("VL53L5CXV0 not detected at requested address (0x%x)\r\n", Dev.platform.address);
		return 1;
	} else {

		PRINTF("VL53L5CXV0 is Alive at address (0x%x)\r\n", Dev.platform.address);
	}


	//PRINTF("Sensor initializing, please wait few seconds...\r\n");
	status = vl53l5cx_init(&Dev);
	status = vl53l5cx_set_resolution(&Dev, VL53L5CX_RESOLUTION_8X8);
	status = vl53l5cx_set_ranging_frequency_hz(&Dev, 60);				         // Set 60 Hz ranging frequency
	PRINTF("Status %d\r\n", status);
	status = vl53l5cx_set_ranging_mode(&Dev, VL53L5CX_RANGING_MODE_CONTINUOUS);  // Set mode continuous

	PRINTF("Ranging starts\r\n");
	status = vl53l5cx_start_ranging(&Dev);
	/* USER CODE END 2 */
	PINT_EnableCallbackByIndex(PINT_PERIPHERAL, kPINT_PinInt0);

	LCD_Init(FLEXCOMM3_PERIPHERAL);

	while(1) {
		LCD_Clear(0x0000);


		drawPixels(8, 8, 20, 16);

		LCD_GramRefresh();


	}
	return 0 ;
}
