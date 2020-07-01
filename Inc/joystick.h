#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "stm32f0xx_hal.h"

#define MOVE_THRESHOLD 5
#define REL_SPEED_DIVIDER 3
#define MAX_CURSOR_SPEED 5
#define CENTER 128

void joystick_init();
void set_calibration_point();
void start_rel();
void end_rel();
void get_value(uint8_t* x, uint8_t* y);

#endif
