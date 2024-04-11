#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define OBJECT_COLOR 63488
#define BG_COLOR 31

void detectAndColorObjects(uint16_t matrix[8][8]) {
    uint16_t newMatrix[8][8];
    uint32_t sum = 0;

    // Calculate the average value of the matrix
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sum += matrix[i][j];
        }
    }
    uint16_t average = sum / 64;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // If the pixel value is less than the average, mark it as part of an object
            if (matrix[i][j] < average) {
                newMatrix[i][j] = OBJECT_COLOR;
            } else {
                newMatrix[i][j] = BG_COLOR;
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            matrix[i][j] = newMatrix[i][j];
        }
    }
}
/*
int main() {
    uint16_t pixelMatrix[8][8] = {
        { 2123, 2200, 4000, 4000, 4000, 4000, 4000, 4000 },
        { 2111, 2000, 4000, 4000, 4000, 4000, 4000, 4000 },
        { 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000 },
        { 4000, 4000, 432, 456, 415, 4000, 4000, 4000 },
        { 4000, 4000, 455, 444, 423, 4000, 4000, 4000 },
        { 4000, 4000, 412, 487, 461, 4000, 4000, 4000 },
        { 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000 },
        { 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000 }
    };

    detectAndColorObjects(pixelMatrix);

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            printf("%d ", pixelMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}*/
