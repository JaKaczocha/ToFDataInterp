#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
/*
#define CLAMP(x, low, high) ((x) > (high) ? (high) : ((x) < (low) ? (low) : (x)))

#define OBJECT_THRESHOLD 600
#define OBJECT_COLOR 63488
#define BG_COLOR 31

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

void bicubicResize(uint16_t input[8][8], uint16_t output[80][64]) {
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

void detectObjects(uint16_t matrix[8][8]) {
    // Object detection
    uint16_t newMatrix[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Check the neighbors
            bool isObject = false;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (i + di >= 0 && i + di < 8 && j + dj >= 0 && j + dj < 8 && abs((int)matrix[i][j] - (int)matrix[i + di][j + dj]) >= OBJECT_THRESHOLD) {
                        printf("i: %d, j: %d, di: %d, dj: %d, matrix[i][j]: %d, matrix[i + di][j + dj]: %d\n", i, j, di, dj, matrix[i][j], matrix[i + di][j + dj]);
                        isObject = true;
                        break;
                    }
                }
                if (isObject) {
                    break;
                }
            }

            if (!isObject) {
                printf("i: %d, j: %d\n", i, j);
                // If the difference is greater than or equal to the threshold, mark this pixel as part of an object
                newMatrix[i][j] = OBJECT_COLOR;
            } else {
                // If the pixel is part of the same object or the background, set its color to the background color
                newMatrix[i][j] = BG_COLOR;
            }
        }
    }

    // Copy newMatrix to matrix
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            matrix[i][j] = newMatrix[i][j];
        }
    }
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
    int screenSizeWidth = 16;
    int screenSizeHeight = 16;
    
    uint8_t r, g, b;
    //uint16_t pixelMatrix[8][8] = {0};
    uint16_t greyscaleMatrix[8][8] = {0};
    uint16_t colorMatrix[8][8] = {0};
    uint16_t detectedMatrix[8][8] = {0};
    uint16_t outputMatrix[80][64] = {0};

    

    /*uint16_t pixelMatrix[8][8] = {
        { 4000, 4000, 4000, 4000, 4000, 4000, 0, 0, },
        { 4000, 1000, 1000, 4000, 4000, 1000, 1000, 0, },
        { 4000, 1000, 1000, 4000, 0, 1000, 1000, 0, },
        { 4000, 4000, 4000, 4000, 0, 0, 0, 0, },
        { 4000, 1000, 0, 0, 0, 0, 1000, 0, },
        { 0, 1000, 1000, 0, 0, 1000, 1000, 0, },
        { 0, 1000, 1000, 1000, 1000, 1000, 1000, 0, },
        { 0, 0, 0, 0, 0, 0, 0, 0, }
    };*/
/*
    uint16_t pixelMatrix[8][8] = {
        { 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, },
        { 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, },
        { 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, },
        { 3000, 3000, 432, 456, 415, 3000, 3000, 3000, },
        { 3000, 3000, 455, 444, 423, 3000, 3000, 3000, },
        { 3000, 3000, 412, 487, 461, 3000, 3000, 3000, },
        { 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, },
        { 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, }
    };

    

for(int k = 0; k < 1; k++) {
    //simulateToF(pixelMatrix);
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            colorMatrix[i][j] = convertToColorRGB(pixelMatrix[i][j], 1, 2000);
        }
    }

    detectObjects(pixelMatrix);

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            rgb565_to_rgb(pixelMatrix[i][j], &r, &g, &b);
            printf("\033[38;2;%d;%d;%dm%d\033[0m ", r, g, b, pixelMatrix[i][j]);
        }
        printf("\n");
    }
}


    return 0;
}
*/
