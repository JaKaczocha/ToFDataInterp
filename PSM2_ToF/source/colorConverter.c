#include "colorConverter.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>


uint16_t convertToGreyscale(const uint16_t value, const uint16_t minValue, const uint16_t maxValue) {
    uint16_t r, g, b;

    // Ensure that the value is within the specified range
    uint16_t cappedValue = value;
    if (cappedValue < minValue) {
        cappedValue = minValue;
    } else if (cappedValue > maxValue) {
    	cappedValue = maxValue;
    }

    // Scale the grayscale value to 0-31 based on minValue and maxValue
    uint16_t scaledValue = (int)(((float)(cappedValue - minValue) / (maxValue - minValue)) * 31 + 0.5);

    // Map the grayscale value to RGB.
    // Values below minValue should be black (0, 0, 0) and values above maxValue should be white (31, 31, 31).
    if (value < minValue) {
        r = g = b = 0; // Black
    } else if (value > maxValue) {
        r = g = b = 31; // White
        g = (g << 1) + 1;
    } else {
        r = g = b = scaledValue;
        g = (g << 1) + 1; // Adjust green component
    }

    // Combine the red, green, and blue values into a uint16_t color value
    return (uint16_t)((r << 11) | (g << 5) | b);
}

uint16_t convertToColorRBTest(const uint16_t value, const uint16_t minCap, const uint16_t maxCap) {
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

