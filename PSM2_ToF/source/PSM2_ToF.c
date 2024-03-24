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
#include "render.h"

#define TOF_WIDTH 8
#define TOF_HEIGHT 8

struct Matrix {
    uint16_t* array;
    uint16_t width;
    uint16_t height;
};

int status;
const uint16_t colorModeCounter = 4;
const uint16_t modeCounter = 4;
uint8_t valueJump;
int8_t changeDirection = 0;
uint8_t mode = 0;

volatile bool nextMode = 0;
uint16_t pixelArr[64];

uint16_t  interpArr[64*64];
uint16_t  interpArr128[128*128];
uint16_t minValue = 1, maxValue = 4000;

volatile int IntCount;
uint8_t p_data_ready;
VL53L5CX_Configuration 	Dev;
VL53L5CX_ResultsData 	Results;
uint8_t resolution, isAlive;
volatile int16_t colorMode = 0;
volatile uint16_t bounce = 0;

uint16_t oldVal = 999;
//INTERPOLACJA LINOWA ŻEBY ZWIEKSZYC ROZDZIELCZOSC!!!!!!!!!11!1
void SysTick_Handler(void)
{
	bounce = bounce ? bounce - 1 : 0;
}

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

void detectedENCA(pint_pin_int_t pintr, uint32_t pmatch_status) {
	if(!bounce) {
		bounce = 15;
		if(!GPIO_PinRead(BOARD_INITENCPINS_SIB_GPIO, BOARD_INITENCPINS_SIB_PORT, BOARD_INITENCPINS_SIB_PIN)) {
			++changeDirection;

		} else {
			--changeDirection;
		}

	}
}

void detectedSW(pint_pin_int_t pintr, uint32_t pmatch_status) {
	if(!bounce) {
		bounce = 15;
		nextMode = 1;

	}
}

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

	SysTick_Config(SystemCoreClock / 100U);
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
	LCD_Clear(0xffffff);

	LCD_Puts(10, 30, "Sensor initializing...", 0x0000);
	PRINTF("Sensor initializing, please wait few seconds...\r\n");
	status = vl53l5cx_init(&Dev);
	status = vl53l5cx_set_resolution(&Dev, VL53L5CX_RESOLUTION_8X8);
	status = vl53l5cx_set_ranging_frequency_hz(&Dev, 60);
	LCD_Clear(0xffffff);
	LCD_Puts(10, 30, "Status...", 0x0000);
	PRINTF("Status %d\r\n", status);
	status = vl53l5cx_set_ranging_mode(&Dev, VL53L5CX_RANGING_MODE_CONTINUOUS);  // Set mode continuous
	LCD_Clear(0xffffff);
	LCD_Puts(10, 30, "Ranging starts...", 0x0000);
	PRINTF("Ranging starts\r\n");
	status = vl53l5cx_start_ranging(&Dev);
	/* USER CODE END 2 */
	PINT_EnableCallbackByIndex(PINT_PERIPHERAL, kPINT_PinInt0);
	LCD_Clear(0xffffff);
	LCD_Puts(10, 30, "callback enable...", 0x0000);

	struct Matrix srcMatrix;
	srcMatrix.array = pixelArr;
	srcMatrix.width = TOF_WIDTH;
	srcMatrix.height = TOF_HEIGHT;
	struct Matrix tmpMatrix;

	tmpMatrix.array = interpArr;
	tmpMatrix.width = 64;
	tmpMatrix.height = 64;
	struct Matrix dstMatrix;
	dstMatrix.array = interpArr128;
	dstMatrix.width = 128;
	dstMatrix.height = 128;

	LCD_Clear(0xffffff);
	LCD_Puts(10, 30, "before loop...", 0x0000);
	while(1) {
		switch(colorMode)
		{
		case 0:
			drawColorBilinear(srcMatrix,tmpMatrix,dstMatrix,minValue,maxValue);
			break;
		case 1:
			drawGreyBilinear(srcMatrix,tmpMatrix,dstMatrix,minValue,maxValue);
			break;
		case 2:
			drawColorNearest(srcMatrix,tmpMatrix,dstMatrix,minValue,maxValue);
			break;
		case 3:
			drawGreyNearest(srcMatrix,tmpMatrix,dstMatrix,minValue,maxValue);
			break;
		default:
			drawColorBilinear(srcMatrix,tmpMatrix,dstMatrix,minValue,maxValue);
			break;
		}

		mode += nextMode;
		nextMode = 0;
		if(mode >= modeCounter) {
			mode = 0;
		}
		if(changeDirection) {
			switch(mode) {
				case 0: //draw option
					colorMode += changeDirection;
					if(colorMode < 0) {
						colorMode = colorModeCounter - 1;
					} else if ( colorMode >= colorModeCounter) {
						colorMode = 0;
					}
					break;
				case 1: //min value option ..
					minValue += changeDirection * valueJump;
					if(minValue >= maxValue) {
						minValue = 1;
					}
					break;
				case 2: // max value option
					maxValue += changeDirection * valueJump;
					if(maxValue > 4000 || maxValue <= minValue) {
						maxValue = 4000;
					}
					break;
				case 3: // value jump option
					valueJump += changeDirection;
					break;
			}
			changeDirection = 0;
		}

		LCD_GramRefresh();
	}

	return 0 ;
}
