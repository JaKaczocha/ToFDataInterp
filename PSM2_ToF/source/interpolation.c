#include "interpolation.h"


#define CLAMP(x, low, high) ((x) > (high) ? (high) : ((x) < (low) ? (low) : (x)))

float CubicHermite(float A, float B, float C, float D, float t) {
    float a = -A * 0.5f + (3.0f * B) * 0.5f - (3.0f * C) * 0.5f + D * 0.5f;
    float b = A - (5.0f * B) * 0.5f + 2.0f * C - D * 0.5f;
    float c = -A * 0.5f + C * 0.5f;
    float d = B;

    return a * t * t * t + b * t * t + c * t + d;
}

float bicubicInterpolate(float p[4][4], float x, float y) {
    float arr[4];
    arr[0] = CubicHermite(p[0][0], p[0][1], p[0][2], p[0][3], y);
    arr[1] = CubicHermite(p[1][0], p[1][1], p[1][2], p[1][3], y);
    arr[2] = CubicHermite(p[2][0], p[2][1], p[2][2], p[2][3], y);
    arr[3] = CubicHermite(p[3][0], p[3][1], p[3][2], p[3][3], y);
    return CubicHermite(arr[0], arr[1], arr[2], arr[3], x);
}

void bicubic(uint16_t dest[], const uint16_t destWidth, const uint16_t destHeight, const uint16_t src[], const uint16_t srcWidth, const uint16_t srcHeight) {
    for (int i = 0; i < destHeight; i++) {
        for (int j = 0; j < destWidth; j++) {
            float x = (float)j / (float)destWidth * (float)srcWidth;
            float y = (float)i / (float)destHeight * (float)srcHeight;

            int xInt = (int)x;
            int yInt = (int)y;

            float p[4][4];
            for (int m = -1; m <= 2; m++) {
                for (int n = -1; n <= 2; n++) {
                    int xIndex = xInt + m;
                    int yIndex = yInt + n;
                    xIndex = xIndex < 0 ? 0 : xIndex >= srcWidth ? srcWidth - 1 : xIndex;
                    yIndex = yIndex < 0 ? 0 : yIndex >= srcHeight ? srcHeight - 1 : yIndex;
                    p[m + 1][n + 1] = src[yIndex * srcWidth + xIndex];
                }
            }

            float interpolatedValue = bicubicInterpolate(p, x - xInt, y - yInt);
            interpolatedValue = CLAMP(interpolatedValue, 1.0f, 4000.0f); // Zapewnienie, że wartość mieści się w zakresie uint16_t
            dest[i * destWidth + j] = (uint16_t)interpolatedValue;
        }
    }
}


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
