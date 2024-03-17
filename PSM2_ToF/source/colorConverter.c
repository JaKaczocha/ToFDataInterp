#include <stdio.h>
#include <math.h>
#include <stdint.h>

int counter = 1;
int old_min = 1;
int old_max = 4000;
int new_min  = 0;
int new_max = 255;

uint16_t simulateToF(uint16_t matrix[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            matrix[i][j] = counter;
            counter++;
            if (counter > 4000) {
                counter = 1;
            }
        }
    }
    return 0;
}

uint16_t convertToGreyscale(uint16_t value) {
    uint16_t r, g, b;

    // Scale the grayscale value to 0-31
    uint16_t scaledValue = round((value / 4000.0) * 31);

    // Map the grayscale value to RGB. The closer to 4000, the closer to white (31, 31, 31).
    r = g = b = scaledValue;

    // Combine the red, green and blue values into a uint16_t color value
    return (uint16_t)((r << 11) | (g << 5) | b);
}

uint16_t convertToColor(uint16_t value) {
    uint16_t r, g, b;

    if (value <= 2000) {
        // Map to red. The closer to 2000, the less intense the red.
        r = 31;
        g = 0;
        b = 31 - round((value / 2000.0) * 31); // Scale down to 0-31
    } else {
        // Map to blue. The closer to 4000, the more intense the blue.
        r = 31 - round(((value - 2000) / 2000.0) * 31); // Scale down to 0-31
        g = 0;
        b = 31;
    }

    // Combine the red, green and blue values into a uint16_t color value
    return (uint16_t)((r << 11) | (g << 5) | b);
}

int main() {
    for(int i = 0; i < 64; i++) {

    
    
    //while(1) {
        uint16_t pixelMatrix[8][8] = {0};
        uint16_t greyscaleMatrix[8][8] = {0};
        uint16_t colorMatrix[8][8] = {0};

        simulateToF(pixelMatrix);
        //convertToGreyscale(pixelMatrix);
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                greyscaleMatrix[i][j] = convertToGreyscale(pixelMatrix[i][j]);
                printf("%d ", greyscaleMatrix[i][j]);
                //colorMatrix[i][j] = convertToColor(pixelMatrix[i][j]);
                //printf("%d ", colorMatrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    //}
    
    return 0;
}