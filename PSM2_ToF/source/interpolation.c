#include "interpolation.h"

int nearestNeighbor(uint16_t dest[], uint16_t destWidth, uint16_t destHeight, const uint16_t src[], const uint16_t srcWidth, const uint16_t srcHeight)
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





void bilinear(uint16_t dest[], uint16_t destWidth, uint16_t destHeight,const uint16_t src[],const  uint16_t srcWidth,const  uint16_t srcHeight) {
    float x_ratio = ((float)(srcWidth - 1)) / destWidth;
    float y_ratio = ((float)(srcHeight - 1)) / destHeight;
    float x_diff, y_diff;
    int offset = 0;

    for (int y = 0; y < destHeight; y++) {
        for (int x = 0; x < destWidth; x++) {
            int x_src = (int)(x_ratio * x);
            int y_src = (int)(y_ratio * y);
            x_diff = (x_ratio * x) - x_src;
            y_diff = (y_ratio * y) - y_src;
            int index = y_src * srcWidth + x_src;
            uint16_t a = src[index];
            uint16_t b = src[index + 1];
            uint16_t c = src[index + srcWidth];
            uint16_t d = src[index + srcWidth + 1];

            // Interpolacja biliniowa
            uint16_t interpolated_value = (uint16_t)(a * (1 - x_diff) * (1 - y_diff) + b * x_diff * (1 - y_diff) + c * y_diff * (1 - x_diff) + d * x_diff * y_diff);

            dest[offset++] = interpolated_value;
        }
    }
}
