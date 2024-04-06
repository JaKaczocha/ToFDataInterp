/*
 * interpolation.h
 *
 *  Created on: 15 mar 2024
 *      Author: User
 */

#ifndef INTERPOLATION_H_
#define INTERPOLATION_H_

#include <stdint.h>



float CubicHermite(float A, float B, float C, float D, float t);
float bicubicInterpolate(float p[4][4], float x, float y);
void bicubic(uint16_t dest[], const uint16_t destWidth, const uint16_t destHeight, const uint16_t src[], const uint16_t srcWidth, const uint16_t srcHeight);

int nearestNeighbor(uint16_t dest[], uint16_t destWidth, uint16_t destHeight, const uint16_t src[],const uint16_t srcWidth, const uint16_t srcHeight);

void bilinear(uint16_t dest[],uint16_t destWidth,uint16_t destHeight,const uint16_t src[],const uint16_t srcWidth,const uint16_t srcHeight);


#endif /* INTERPOLATION_H_ */
