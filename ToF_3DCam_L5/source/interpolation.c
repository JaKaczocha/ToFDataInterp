/*
 * interpolation.c
 *
 *  Created on: 15 mar 2024
 *      Author: User
 */
#include "interpolation.h"

int nearestNeighbor(uint16_t dest[128][128], const uint16_t destWidth, const uint16_t destHeight, const uint16_t src[8][8],const uint16_t srcWidth, const uint16_t srcHeight)
{
    if(destWidth < srcWidth || destHeight < srcHeight) {
        return 1;
    }

    const int Xscale = destWidth / srcWidth;
    const int Yscale = destHeight / srcHeight;

    for(int ySrc = 0; ySrc < srcHeight; ySrc++) {
        for(int xSrc = 0; xSrc < srcWidth; xSrc++) {

            for(int i = 0; i < Yscale; i++) {
                for(int j = 0; j < Xscale; j++) {

                    dest[ySrc * Yscale + i][xSrc * Xscale + j] = src[ySrc][xSrc];
                }
            }

        }
    }

    return 0;
}


// Interpolacja metoda bilinearna dla pikseli RGB565
uint16_t calcBilinear(uint16_t p00, uint16_t p01, uint16_t p10, uint16_t p11,double y_ratio, double x_ratio) {
    // Rozkładanie pikseli RGB565 na składowe koloru
    uint8_t r00 = (p00 >> 11) & 0x1F;
    uint8_t r01 = (p01 >> 11) & 0x1F;
    uint8_t r10 = (p10 >> 11) & 0x1F;
    uint8_t r11 = (p11 >> 11) & 0x1F;

    uint8_t g00 = (p00 >> 5) & 0x3F;
    uint8_t g01 = (p01 >> 5) & 0x3F;
    uint8_t g10 = (p10 >> 5) & 0x3F;
    uint8_t g11 = (p11 >> 5) & 0x3F;

    uint8_t b00 = p00  & 0x1F;
    uint8_t b01 = p01  & 0x1F;
    uint8_t b10 = p10  & 0x1F;
    uint8_t b11 = p11  & 0x1F;

    // Interpolacja składowych koloru
    uint8_t r = (uint8_t)(r00 * (1 - x_ratio) * (1 - y_ratio) + r01 * x_ratio * (1 - y_ratio) + r10 * (1 - x_ratio) * y_ratio + r11 * x_ratio * y_ratio);
    uint8_t g = (uint8_t)(g00* (1 - x_ratio) * (1 - y_ratio) + g01 * x_ratio * (1 - y_ratio) + g10 * (1 - x_ratio) * y_ratio + g11 * x_ratio * y_ratio);
    uint8_t b = (uint8_t)(b00 * (1 - x_ratio) * (1 - y_ratio) + b01 * x_ratio * (1 - y_ratio) + b10* (1 - x_ratio) * y_ratio + b11 * x_ratio * y_ratio);

    // Składanie składowych koloru w piksel RGB565
    return (uint16_t)(((r & 0x1F) << 11) | ((g & 0x3F) << 5) | (b & 0x1F));
}

void bilinear(uint16_t dest[128][128], const uint16_t src[8][8]) {

    uint16_t p00=0,p01 = 0,p10 = 0,p11 = 0;
    float gx = 0.0, gy = 0.0;
    int xIndex, yIndex;
    float xRatio, yRatio;
    for(int y = 0; y < 128; y++) {
        for(int x = 0; x < 128; x++) {
            gx = (x*7.0) / (128.0 - 1.0);
            gy = (y*7.0) / (128.0 - 1.0);

            xIndex = (int)gx;
            yIndex = (int)gy;

            xRatio = gx - xIndex;
            yRatio = gy - yIndex;

            p00 = src[yIndex][xIndex];
            p01 = src[yIndex][xIndex + 1];
            p10 = src[yIndex + 1][xIndex];
            p11 = src[yIndex + 1][xIndex + 1];

            dest[y][x] = calcBilinear(p00,p01,p10,p11,yRatio,xRatio);
        }
    }
}
