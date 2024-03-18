/*
 * interpolation.h
 *
 *  Created on: 15 mar 2024
 *      Author: User
 */

#ifndef INTERPOLATION_H_
#define INTERPOLATION_H_

#include <stdint.h>

int nearestNeighbor(uint16_t dest[], const uint16_t destWidth, const uint16_t destHeight, const uint16_t src[],const uint16_t srcWidth, const uint16_t srcHeight);
uint16_t calcBilinear(uint16_t p00, uint16_t p01, uint16_t p10, uint16_t p11,double y_ratio, double x_ratio);
void bilinear(uint16_t dest[],uint16_t destWidth,uint16_t destHeight, const uint16_t src[],uint16_t srcWidth,uint16_t srcHeight);

#endif /* INTERPOLATION_H_ */
