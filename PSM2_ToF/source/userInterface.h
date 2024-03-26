#include <stdint.h>
#include <stdbool.h>

uint8_t updateMode(uint8_t * const mode, bool* const nextMode, const uint16_t modeCounter);
uint8_t updateValue(const uint8_t mode, int8_t * const changeDirection,int16_t * const colorMode,uint16_t * 
    const minValue, uint16_t * const maxValue, uint8_t * const valueJump, const uint16_t colorModeCounter, const uint16_t modeCounter);
uint8_t displayInterface(char* const buff,const char* const colorModeName,const uint16_t minValue, const uint16_t maxValue, const uint8_t valueJump,const uint8_t mode);
