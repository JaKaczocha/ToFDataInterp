#include "interpolation.h"
#include "colorConverter.h"
#include "lcd.h"


struct Matrix {
    uint16_t* array;
    uint16_t width;
    uint16_t height;
};


volatile void drawGreyBicubic(const struct Matrix src, struct Matrix bicubicTmp,struct  Matrix dst,const uint16_t minValue,const  uint16_t maxValue) {

	uint16_t srcCpy[src.width * src.height];
	memcpy(srcCpy, src.array,  sizeof(uint16_t) * src.width * src.height);

	bicubic(bicubicTmp.array, bicubicTmp.width, bicubicTmp.height, srcCpy, src.width, src.height);

	for(int j=0; j<bicubicTmp.height; j++)
	{
		for(int i=0; i < bicubicTmp.width; i++)
		{
			bicubicTmp.array[j*bicubicTmp.width+i] = convertToGreyscale(bicubicTmp.array[j*bicubicTmp.width+i],minValue, maxValue);
		}
	}

	nearestNeighbor(dst.array, dst.width, dst.height, bicubicTmp.array, bicubicTmp.width,bicubicTmp.height);
	LCD_Set_Icon(0, 0, dst.width, dst.height, dst.array);
}

volatile void drawGreyBilinear(const struct Matrix src,struct Matrix bilinearTmp, struct Matrix dst,const uint16_t minValue,const  uint16_t maxValue)
{
	uint16_t srcCpy[src.width * src.height];
	memcpy(srcCpy, src.array, sizeof(uint16_t) * src.width * src.height);

	bilinear(bilinearTmp.array, bilinearTmp.width, bilinearTmp.height, srcCpy, src.width, src.height);

	for(int j=0; j<bilinearTmp.height; j++)
		{
			for(int i=0; i < bilinearTmp.width; i++)
			{
				bilinearTmp.array[j*bilinearTmp.width+i] = convertToGreyscale(bilinearTmp.array[j*bilinearTmp.width+i],minValue, maxValue);
			}
		}

	nearestNeighbor(dst.array, dst.width, dst.height, bilinearTmp.array, bilinearTmp.width,bilinearTmp.height);
    LCD_Set_Icon(0, 0, dst.width, dst.height, dst.array);
}

volatile void drawGreyNearest(const struct Matrix src, struct Matrix nearestTmp,struct Matrix dst,const uint16_t minValue, const uint16_t maxValue)
{
	uint16_t srcCpy[src.width * src.height];
	memcpy(srcCpy, src.array, sizeof(uint16_t) * src.width * src.height);

	for(int j=0; j<src.height; j++)
		{
			for(int i=0; i<src.width; i++)
			{
				nearestTmp.array[j*src.height+i] = convertToGreyscale(srcCpy[j*src.height+i],minValue, maxValue);
			}
		}
	nearestNeighbor(dst.array, dst.width, dst.height, nearestTmp.array, src.width, src.height);
    LCD_Set_Icon(0, 0, dst.width, dst.height, dst.array);
}

volatile void drawColorBicubic( const struct Matrix src,struct Matrix bicubicTmp, struct Matrix dst,const uint16_t minValue, const uint16_t maxValue)
{
	uint16_t srcCpy[src.width * src.height];
	memcpy(srcCpy, src.array, sizeof(uint16_t) * src.width * src.height);

	bicubic(bicubicTmp.array, bicubicTmp.width, bicubicTmp.height, srcCpy, src.width, src.height);

	for(int j=0; j<bicubicTmp.height; j++)
		{
			for(int i=0; i < bicubicTmp.width; i++)
			{
				bicubicTmp.array[j*bicubicTmp.width+i] = convertToColorRGB(bicubicTmp.array[j*bicubicTmp.width+i],minValue, maxValue);
			}
		}

	nearestNeighbor(dst.array, dst.width, dst.height, bicubicTmp.array, bicubicTmp.width, bicubicTmp.height);
    LCD_Set_Icon(0, 0, dst.width, dst.height, dst.array);
}

volatile void drawColorBilinear( const struct Matrix src,struct Matrix bilinearTmp, struct Matrix dst,const uint16_t minValue, const uint16_t maxValue)
{
	uint16_t srcCpy[src.width * src.height];
	memcpy(srcCpy, src.array, sizeof(uint16_t) * src.width * src.height);

	bilinear(bilinearTmp.array, bilinearTmp.width, bilinearTmp.height, srcCpy, src.width, src.height);

	for(int j=0; j<bilinearTmp.height; j++)
		{
			for(int i=0; i < bilinearTmp.width; i++)
			{
				bilinearTmp.array[j*bilinearTmp.width+i] = convertToColorRGB(bilinearTmp.array[j*bilinearTmp.width+i],minValue,maxValue);
			}
		}

	nearestNeighbor(dst.array, dst.width, dst.height, bilinearTmp.array, bilinearTmp.width, bilinearTmp.height);
    LCD_Set_Icon(0, 0, dst.width, dst.height, dst.array);
}

volatile void drawColorNearest(const struct Matrix src, struct Matrix nearestTmp,struct Matrix dst,const uint16_t minValue,const  uint16_t maxValue)
{
	uint16_t srcCpy[src.width * src.height];
	memcpy(srcCpy, src.array, sizeof(uint16_t) * src.width * src.height);

	for(int j=0; j<src.height; j++)
		{
			for(int i=0; i<src.width; i++)
			{
				nearestTmp.array[j*src.height+i] = convertToColorRGB(srcCpy[j*src.height+i],minValue, maxValue);
			}
		}
	nearestNeighbor(dst.array, dst.width, dst.height, nearestTmp.array,src.width, src.height);
    LCD_Set_Icon(0, 0, dst.width, dst.height, dst.array);
}
