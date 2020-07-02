#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "stm32f0xx_hal.h"

#define MOVE_THRESHOLD 5
#define REL_SPEED_DIVIDER 3
#define MAX_CURSOR_SPEED 10

void joystick_init();
void set_calibration_point();
void set_rel(uint8_t state);
uint8_t get_rel();
void get_value(int8_t* x, int8_t* y);

#endif
