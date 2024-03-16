/*
 * interpolation.h
 *
 *  Created on: 15 mar 2024
 *      Author: User
 */

#ifndef INTERPOLATION_H_
#define INTERPOLATION_H_

#include <stdint.h>

int nearestNeighbor(uint16_t dest[128][128], const uint16_t destWidth, const uint16_t destHeight, const uint16_t src[8][8],const uint16_t srcWidth, const uint16_t srcHeight);
uint16_t calcBilinear(uint16_t p00, uint16_t p01, uint16_t p10, uint16_t p11,double y_ratio, double x_ratio);
void bilinear(uint16_t dest[128][128], const uint16_t src[8][8]);

#endif /* INTERPOLATION_H_ */
