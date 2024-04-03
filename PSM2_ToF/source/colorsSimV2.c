#include <stdio.h>
#include <math.h>
#include <stdint.h>



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


