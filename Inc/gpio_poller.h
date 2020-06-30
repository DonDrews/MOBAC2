#ifndef GPIO_POLLER_H
#define GPIO_POLLER_H

#define NUM_BUTTONS 16

#include "stm32f0xx_hal.h"

typedef struct
{
	GPIO_TypeDef* port;
	uint16_t pin;
	uint8_t keycode;
} button_def;

typedef struct
{
	uint32_t log;
	uint32_t state;
} button_state;

enum button_names
{
	ITEM1 = 0,
	ITEM2,
	ITEM3,
	SUMM1,
	SUMM2,
	WARD,
	RECALL,
	CAMLOCK,
	Q,
	W,
	E,
	R,
	SHOP,
	QUICKCAST,
	R_CLICK,
	L_CLICK,
};

extern const button_def definitions[NUM_BUTTONS];

button_state states[NUM_BUTTONS];

void io_init();

#endif
