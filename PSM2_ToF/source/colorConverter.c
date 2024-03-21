#include "colorConverter.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>


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

uint16_t convertToColor(const uint16_t value,const float maxValue) {
    uint16_t r, g, b;

    // Map to red. The closer to 2000, the less intense the red.
    r = 31 - (int)(((float)value / maxValue) * 31.0f);
    g = 0;
    b = (int)(((float)value / maxValue) * 31.0f);


    // Combine the red, green and blue values into a uint16_t color value
    return (uint16_t)((r << 11) | (g << 5) | b);
}

/*
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
*/
