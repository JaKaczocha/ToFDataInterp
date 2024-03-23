#ifndef RENDER_H_
#define RENDER_H_

struct Matrix;

volatile void drawGreyBilinear(const struct Matrix src, struct Matrix bilinearTmp,struct  Matrix dst,const uint16_t minValue,const  uint16_t maxValue);

volatile void drawGreyNearest(const struct Matrix src, struct Matrix nearestTmp, struct Matrix dst,const uint16_t minValue,const  uint16_t maxValue);

volatile void drawColorBilinear(const struct Matrix src, struct Matrix bilinearTmp,struct  Matrix dst,const uint16_t minValue, const uint16_t maxValue);

volatile void drawColorNearest(const struct Matrix src, struct Matrix nearestTmp,struct Matrix dst,const uint16_t minValue, const uint16_t maxValue);


#endif /* RENDER_H_ */
