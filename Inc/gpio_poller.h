#ifndef GPIO_POLLER_H
#define GPIO_POLLER_H

#define NUM_BUTTONS 16

#include "stm32f0xx_hal.h"

typedef struct
{
	GPIO_TypeDef* port;
	uint16_t pin;
	uint8_t keycode;
	uint8_t quickcasted;
} button_def;

typedef struct
{
	uint8_t log;
	volatile uint8_t state;
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

//flag set by timer interrupt
//lets main method know when to sample
extern uint8_t next_sample;

void io_init();

button_state* get_states();
void toggle_quickcast();
uint8_t get_autoclick();
void debounce_sample();

#endif
