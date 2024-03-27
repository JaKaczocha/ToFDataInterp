#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define CLAMP(x, low, high) ((x) > (high) ? (high) : ((x) < (low) ? (low) : (x)))

double CubicHermite(double A, double B, double C, double D, double t) {
    double a = -A / 2.0 + (3.0 * B) / 2.0 - (3.0 * C) / 2.0 + D / 2.0;
    double b = A - (5.0 * B) / 2.0 + 2.0 * C - D / 2.0;
    double c = -A / 2.0 + C / 2.0;
    double d = B;

    return a * t * t * t + b * t * t + c * t + d;
}

double bicubicInterpolate(double p[4][4], double x, double y) {
    double arr[4];
    arr[0] = CubicHermite(p[0][0], p[0][1], p[0][2], p[0][3], y);
    arr[1] = CubicHermite(p[1][0], p[1][1], p[1][2], p[1][3], y);
    arr[2] = CubicHermite(p[2][0], p[2][1], p[2][2], p[2][3], y);
    arr[3] = CubicHermite(p[3][0], p[3][1], p[3][2], p[3][3], y);
    return CubicHermite(arr[0], arr[1], arr[2], arr[3], x);
}

void bicubicResize(uint16_t input[8][8], uint16_t output[16][16]) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            double x = (double)i / 2;
            double y = (double)j / 2;

            int xInt = (int)x;
            int yInt = (int)y;

            double p[4][4];
            for (int m = -1; m <= 2; m++) {
                for (int n = -1; n <= 2; n++) {
                    int xIndex = xInt + m;
                    int yIndex = yInt + n;
                    xIndex = xIndex < 0 ? 0 : xIndex > 7 ? 7 : xIndex;
                    yIndex = yIndex < 0 ? 0 : yIndex > 7 ? 7 : yIndex;
                    p[m + 1][n + 1] = input[yIndex][xIndex];
                }
            }

            output[i][j] = (uint16_t)CLAMP(bicubicInterpolate(p, x - xInt, y - yInt), 31, 63488);
        }
    }
}


int counter = 1;
uint16_t simulateToF(uint16_t matrix[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            matrix[i][j] = counter;
            //counter=1500;
            counter++;
            if (counter > 4000) {
                counter = 1;
            }
        }
    }
    return 0;
}

uint16_t convertToColorRGB(const uint16_t value, const uint16_t minCap, const uint16_t maxCap) {
    uint16_t r, g, b;
    uint16_t midPoint = minCap + ((maxCap - minCap) / 2);

    // Cap the value at minCap and maxCap
    uint16_t cappedValue = value;
    if (cappedValue < minCap) {
        cappedValue = minCap;
    } else if (cappedValue > maxCap) {
        cappedValue = maxCap;
    }

    if (cappedValue <= midPoint) {
        // Normalize the value to the range [0, 31]
        uint16_t normalizedValue = 31 * (cappedValue - minCap) / (midPoint - minCap);

        r = 31 - normalizedValue;
        g = normalizedValue;
        b = 0;
    } else {
        uint16_t normalizedValue = 31 * (cappedValue - midPoint) / (maxCap - midPoint);

        r = 0;
        g = 31 - normalizedValue;
        b = normalizedValue;
    }

    return (uint16_t)((r << 11) | (g << 5) | b);
}

void rgb565_to_rgb(uint16_t rgb565, uint8_t* r, uint8_t* g, uint8_t* b) {
    *r = ((rgb565 >> 11) & 0x1F) << 3; // Red: bits 15-11
    *g = ((rgb565 >> 5) & 0x3F) << 2;  // Green: bits 10-5
    *b = (rgb565 & 0x1F) << 3;         // Blue: bits 4-0
}


int main() {
    
    uint8_t r, g, b;
    uint16_t pixelMatrix[8][8] = {0};
    uint16_t greyscaleMatrix[8][8] = {0};
    uint16_t colorMatrix[8][8] = {0};
    uint16_t outputMatrix[16][16] = {0};

    

    /*uint16_t pixelMatrix[8][8] = {
        { 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, },
        { 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, },
        { 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, },
        { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, },
        { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, },
        { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, },
        { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, },
        { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, }
    };  */

    

    for(int i = 0; i < 60; i++) {
    //while(1) {
        simulateToF(pixelMatrix);
        //convertToGreyscale(pixelMatrix);
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                //greyscaleMatrix[i][j] = convertToGreyscale(pixelMatrix[i][j], 4000);
                //printf("%d ", greyscaleMatrix[i][j]);
                printf("\033[1;33m%d\033[0m ", pixelMatrix[i][j]);
                colorMatrix[i][j] = convertToColorRGB(pixelMatrix[i][j], 1, 4000);
                bicubicResize(colorMatrix, outputMatrix);
                rgb565_to_rgb(outputMatrix[i][j], &r, &g, &b);
                printf("\033[38;2;%d;%d;%dm%d\033[0m ", r, g, b, outputMatrix[i][j]);
                
                //rgb565_to_rgb(colorMatrix[i][j], &r, &g, &b);
                //printf("\033[38;2;%d;%d;%dm%d\033[0m ", r, g, b, colorMatrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        }

    //}


    return 0;
}
