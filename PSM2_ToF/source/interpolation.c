/*
 * interpolation.c
 *
 *  Created on: 15 mar 2024
 *      Author: User
 */
#include "interpolation.h"

int nearestNeighbor(uint16_t dest[], const uint16_t destWidth, const uint16_t destHeight, const uint16_t src[],const uint16_t srcWidth, const uint16_t srcHeight)
{

    const int Xscale = destWidth / srcWidth;
    const int Yscale = destHeight / srcHeight;

    for(int ySrc = 0; ySrc < srcHeight; ySrc++) {
        for(int xSrc = 0; xSrc < srcWidth; xSrc++) {

            for(int i = 0; i < Yscale; i++) {
                for(int j = 0; j < Xscale; j++) {

                    dest[(ySrc * Yscale + i)*destWidth+(xSrc * Xscale + j)] = src[ySrc*srcWidth + xSrc];
                }
            }
        }
    }

    return 0;
}



uint16_t calcBilinear(uint16_t p00, uint16_t p01, uint16_t p10, uint16_t p11,double y_ratio, double x_ratio) {


}

void bilinear(uint16_t dest[],uint16_t destWidth,uint16_t destHeight, const uint16_t src[],uint16_t srcWidth,uint16_t srcHeight) {

    uint16_t p00=0,p01 = 0,p10 = 0,p11 = 0;
    float gx = 0.0, gy = 0.0;
    int xIndex, yIndex;
    float xRatio, yRatio;
    for(int y = 0; y < destHeight; y++) {
        for(int x = 0; x < destWidth; x++) {
            gx = (x*(srcWidth - 1.0)) / (destWidth - 1.0);
            gy = (y*(srcHeight - 1.0)) / (destHeight - 1.0);

            xIndex = (int)gx;
            yIndex = (int)gy;

            xRatio = gx - xIndex;
            yRatio = gy - yIndex;

            p00 = src[yIndex*srcWidth + xIndex];
            p01 = src[yIndex*srcWidth + xIndex + 1];
            p10 = src[(yIndex + 1)*srcWidth + xIndex];
            p11 = src[(yIndex + 1)*srcWidth + xIndex + 1];

            dest[y * destWidth + x] = calcBilinear(p00,p01,p10,p11,yRatio,xRatio);
        }
    }
}