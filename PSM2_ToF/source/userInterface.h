#include <stdint.h>
#include <stdbool.h>

#include "vl53l5cx_api.h"
struct Settings;

void interfaceActivity(volatile struct Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation, VL53L5CX_Configuration * const Dev );
void updateMaxValue(volatile struct Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation);
void updateMinValue(volatile struct Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation);
void updateColorMode(volatile struct Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation);
void updateFreq(volatile struct  Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation);
void updateSharpness(volatile struct  Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation);
void displaySettings(volatile struct Settings* const settings, uint8_t choosenSetting, uint8_t updateMin,uint8_t updateMax,bool selected);
