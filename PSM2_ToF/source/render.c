#include "interpolation.h"
#include "colorConverter.h"
#include "lcd.h"

struct Matrix {
    uint16_t* array;
    uint16_t width;
    uint16_t height;
};

volatile void drawGreyBilinear(const struct Matrix src,struct Matrix bilinearTmp, struct Matrix dst,const uint16_t minValue,const  uint16_t maxValue)
{
	bilinear(bilinearTmp.array, bilinearTmp.width, bilinearTmp.height, src.array, src.width, src.height);

	for(int j=0; j<bilinearTmp.height; j++)
		{
			for(int i=0; i < bilinearTmp.width; i++)
			{
				bilinearTmp.array[j*bilinearTmp.height+i] = convertToGreyscale(bilinearTmp.array[j*bilinearTmp.height+i],maxValue);
			}
		}

	nearestNeighbor(dst.array, dst.width, dst.height, bilinearTmp.array, bilinearTmp.width,bilinearTmp.height);
    LCD_Set_Icon(0, 0, dst.width, dst.height, dst.array);
}

volatile void drawGreyNearest(const struct Matrix src, struct Matrix nearestTmp,struct Matrix dst,const uint16_t minValue, const uint16_t maxValue)
{
	for(int j=0; j<src.height; j++)
		{
			for(int i=0; i<src.width; i++)
			{
				nearestTmp.array[j*src.height+i] = convertToGreyscale(src.array[j*src.height+i],maxValue);
			}
		}
	nearestNeighbor(dst.array, dst.width, dst.height, nearestTmp.array, src.width, src.height);
    LCD_Set_Icon(0, 0, dst.width, dst.height, dst.array);
}

volatile void drawColorBilinear( const struct Matrix src,struct Matrix bilinearTmp, struct Matrix dst,const uint16_t minValue, const uint16_t maxValue)
{
	bilinear(bilinearTmp.array, bilinearTmp.width, bilinearTmp.height, src.array, src.width, src.height);

	for(int j=0; j<bilinearTmp.height; j++)
		{
			for(int i=0; i < bilinearTmp.width; i++)
			{
				bilinearTmp.array[j*bilinearTmp.height+i] = convertToColor(bilinearTmp.array[j*bilinearTmp.height+i],maxValue);
			}
		}

	nearestNeighbor(dst.array, dst.width, dst.height, bilinearTmp.array, bilinearTmp.width, bilinearTmp.height);
    LCD_Set_Icon(0, 0, dst.width, dst.height, dst.array);
}

volatile void drawColorNearest(const struct Matrix src, struct Matrix nearestTmp,struct Matrix dst,const uint16_t minValue,const  uint16_t maxValue)
{
	for(int j=0; j<src.height; j++)
		{
			for(int i=0; i<src.width; i++)
			{
				nearestTmp.array[j*src.height+i] = convertToColor(src.array[j*src.height+i],maxValue);
			}
		}
	nearestNeighbor(dst.array, dst.width, dst.height, nearestTmp.array,src.width, src.height);
    LCD_Set_Icon(0, 0, dst.width, dst.height, dst.array);
}
