/*
 * colorConverter.h
 *
 *  Created on: 18 mar 2024
 *      Author: User
 */

#ifndef COLORCONVERTER_H_
#define COLORCONVERTER_H_

#include <stdint.h>


uint16_t convertToColor(const uint16_t value,const float maxValue);

uint16_t convertToGreyscale(const uint16_t value, const uint16_t minValue, const uint16_t maxValue);
uint16_t convertToColorRBTest(const uint16_t value, const uint16_t minCap, const uint16_t maxCap);
uint16_t convertToColorRGBTest(const uint16_t value, const uint16_t minCap, const uint16_t maxCap);
uint16_t convertToColorRGB(const uint16_t value, const uint16_t minCap, const uint16_t maxCap);


#endif /* COLORCONVERTER_H_ */
