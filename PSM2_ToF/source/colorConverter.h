/*
 * colorConverter.h
 *
 *  Created on: 18 mar 2024
 *      Author: User
 */

#ifndef COLORCONVERTER_H_
#define COLORCONVERTER_H_

#include <stdint.h>

uint16_t convertToGreyscale(const uint16_t value,const float maxValue);
uint16_t convertToColor(const uint16_t value,const float maxValue);

#endif /* COLORCONVERTER_H_ */
