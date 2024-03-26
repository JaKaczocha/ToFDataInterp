#include <stdio.h>
#include <math.h>
#include <stdint.h>

int counter = 1;
/*
uint16_t simulateToF(uint16_t matrix[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            matrix[i][j] = counter;
            counter=3000;
            //if (counter > 4000) {
            //    counter = 1;
            //}
        }
    }
    return 0;
}

uint16_t convertToGreyscale(const uint16_t value,const float maxValue) {
    uint16_t r, g, b;
    // Scale the grayscale value to 0-31
    uint16_t scaledValue = (int)((value / maxValue) * 31 + 0.5);

    // Map the grayscale value to RGB. The closer to 4000, the closer to white (31, 31, 31).
    r = g = b = scaledValue;
    g = (g << 1) + 1;

    // Combine the red, green and blue values into a uint16_t color value
    return (uint16_t)((r << 11) | (g << 5) | b);
}

uint16_t convertToColorRB(const uint16_t value, const uint16_t minCap, const uint16_t maxCap) {
    uint16_t r, g, b;

    // If the value is below the minCap, treat it as the maxCap.
    // If the value is above the maxCap, also treat it as the maxCap.
    uint16_t cappedValue = (value < minCap || value > maxCap) ? maxCap : value;

    // Map to red. The closer to maxCap, the less intense the red.
    r = 31 - (int)(((float)(cappedValue - minCap) / (maxCap - minCap)) * 31);

    // Set green to 0.
    g = 0;

    // Map to blue. The closer to maxCap, the more intense the blue.
    b = cappedValue == maxCap ? 31 : (int)(((float)(cappedValue - minCap) / (maxCap - minCap)) * 31);

    // Combine the red, green and blue values into a uint16_t color value
    return (uint16_t)((r << 11) | (g << 5) | b);
}

uint16_t convertToColorRGB(const uint16_t value, const uint16_t minCap, const uint16_t maxCap) {
    uint16_t r, g, b;

    // If the value is below the minCap, treat it as the maxCap.
    // If the value is above the maxCap, also treat it as the maxCap.
    uint16_t cappedValue = (value < minCap || value > maxCap) ? maxCap : value;

    // Map to red. The closer to maxCap, the less intense the red.
    r = 31 - (int)(((float)(cappedValue - minCap) / (maxCap - minCap)) * 31);

    // Map to green. The closer to the midpoint, the more intense the green.
    // If the value is below the minCap or above the maxCap, set green to 0.
    g = (value < minCap || value > maxCap) ? 0 : cappedValue == (minCap + maxCap) / 2 ? 63 : 63 - abs((int)(((float)(cappedValue - minCap) / (maxCap - minCap)) * 63 - 31));

    // Map to blue. The closer to maxCap, the more intense the blue.
    b = cappedValue == maxCap ? 31 : (int)(((float)(cappedValue - minCap) / (maxCap - minCap)) * 31);

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
        for(int i = 0; i < 1; i++) {
            for(int j = 0; j < 1; j++) {
                //greyscaleMatrix[i][j] = convertToGreyscale(pixelMatrix[i][j], 4000);
                //printf("%d ", greyscaleMatrix[i][j]);
                colorMatrix[i][j] = convertToColorRGB(pixelMatrix[i][j], 1000, 2000);
                printf("%d ", colorMatrix[i][j]);
            }
            //printf("\n");
        }
        //printf("\n");
    }

    //}
    
    return 0;
}*/
