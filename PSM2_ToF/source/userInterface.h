#include <stdint.h>
#include <stdbool.h>

struct Settings;

void interfaceActivity(volatile struct Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation );
void updateMaxValue(volatile struct Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation);
void updateMinValue(volatile struct Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation);
void updateColorMode(volatile struct Settings* const settings,volatile uint16_t* const clicked,volatile int16_t* const rotation);

void displaySettings(volatile struct Settings* const settings, uint8_t choosenSetting, uint8_t updateMin,uint8_t updateMax,bool selected);
