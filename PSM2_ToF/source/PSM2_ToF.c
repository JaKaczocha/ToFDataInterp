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
const uint16_t modeCounter = 4;

uint16_t pixelArr[64];

uint16_t  interpArr[64*64];
uint16_t  interpArr128[128*128];

volatile int IntCount;
uint8_t p_data_ready;
VL53L5CX_Configuration 	Dev;
VL53L5CX_ResultsData 	Results;
uint8_t resolution, isAlive;
uint16_t idx;
volatile uint16_t colorMode = 0;



//INTERPOLACJA LINOWA ŻEBY ZWIEKSZYC ROZDZIELCZOSC!!!!!!!!!11!1


void delay_ms(uint32_t delay)
{
	for(volatile int j=delay*100000; j > 0;j--);
}

void cbToF_Ready(pint_pin_int_t pintr, uint32_t pmatch_status) {

	status = vl53l5cx_get_resolution(&Dev, &resolution);
	status = vl53l5cx_get_ranging_data(&Dev, &Results);

	for(int j = 0; j < resolution/8;j++) {
		for(int i = 0; i < resolution/8;i++) {
			pixelArr[j*8+i] = Results.distance_mm[(VL53L5CX_NB_TARGET_PER_ZONE * i)+(8*j)];
			//PRINTF("%4d ", Results.distance_mm[(VL53L5CX_NB_TARGET_PER_ZONE * i)+(8*j)]);
			//PRINTF("%4d ", pixelArr[j][i]);
		}
		//PRINTF("\r\n");
	}
	//PRINTF("--------------------------------------\r\n");
}

void detectedSIA(pint_pin_int_t pintr, uint32_t pmatch_status) {
	//colorMode = ++colorMode % modeCounter;
}
/* INT_2 callback function for the PINT component */
void detectedSIB(pint_pin_int_t pintr, uint32_t pmatch_status) {
	//colorMode = --colorMode % modeCounter;
}
/* INT_3 callback function for the PINT component */
void detectedSW(pint_pin_int_t pintr, uint32_t pmatch_status) {
	colorMode = ++colorMode % modeCounter;
}


volatile void drawGreyBilinear( uint16_t maxValue)
{

	bilinear(interpArr, 64, 64, pixelArr, 8, 8);

	for(int j=0; j<64; j++)
		{
			for(int i=0; i < 64; i++)
			{
				interpArr[j*64+i] = convertToGreyscale(interpArr[j*64+i],maxValue);
			}
		}

	nearestNeighbor(interpArr128, 128, 128, interpArr, 64, 64);
	LCD_Set_Icon(0, 0, 128, 128, interpArr128);

}

volatile void drawGreyNearest(uint16_t maxValue)
{
	for(int j=0; j<8; j++)
		{
			for(int i=0; i<8; i++)
			{
				interpArr[j*8+i] = convertToGreyscale(pixelArr[j*8+i],maxValue);
			}
		}
	nearestNeighbor(interpArr128, 128, 128, interpArr, 8, 8);
	LCD_Set_Icon(0, 0, 128, 128, interpArr128);

}

volatile void drawColorBilinear( uint16_t maxValue)
{

	bilinear(interpArr, 64, 64, pixelArr, 8, 8);

	for(int j=0; j<64; j++)
		{
			for(int i=0; i < 64; i++)
			{
				interpArr[j*64+i] = convertToColor(interpArr[j*64+i],maxValue);
			}
		}

	nearestNeighbor(interpArr128, 128, 128, interpArr, 64, 64);
	LCD_Set_Icon(0, 0, 128, 128, interpArr128);

}

volatile void drawColorNearest(uint16_t maxValue)
{
	for(int j=0; j<8; j++)
		{
			for(int i=0; i<8; i++)
			{
				interpArr[j*8+i] = convertToColor(pixelArr[j*8+i],maxValue);
			}
		}
	nearestNeighbor(interpArr128, 128, 128, interpArr, 8, 8);
	LCD_Set_Icon(0, 0, 128, 128, interpArr128);

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

	LCD_Init(FLEXCOMM3_PERIPHERAL);
	LCD_Puts(10, 30, "Before vl53l5cx_is_alive...", 0x0000);
	PRINTF("Before vl53l5cx_is_alive...");
	LCD_GramRefresh();


	status = vl53l5cx_is_alive(&Dev, &isAlive);


	if(!isAlive && status==0) {

		LCD_Clear(0xffffff);
		LCD_Puts(10, 30, "NOT ALIVE...", 0x0000);



		PRINTF("VL53L5CXV0 not detected at requested address (0x%x)\r\n", Dev.platform.address);
		return 1;
	} else {


		PRINTF("VL53L5CXV0 is Alive at address (0x%x)\r\n", Dev.platform.address);
	}



	LCD_Clear(0xffffff);
	LCD_Puts(10, 30, "Connecting to vl5315cx...", 0x0000);
	PRINTF("Connecting to vl5315cx...");
	LCD_GramRefresh();


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



	while(1) {
		//LCD_Clear(0x0000);

		switch(colorMode)
		{
			case 0:
				drawColorBilinear(4000);
				break;
			case 1:
				drawGreyBilinear(4000);
				break;
			case 2:
				drawColorNearest(4000);
				break;
			case 3:
				drawGreyNearest(4000);
				break;
			default:
				drawColorBilinear(4000);
				break;
		}


		PRINTF("colorMode %d\r\n", colorMode);
		LCD_GramRefresh();


	}
	return 0 ;
}
