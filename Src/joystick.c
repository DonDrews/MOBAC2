#include "joystick.h"
#include "stdlib.h"

//relative or absolute positioning for the joystick
volatile uint8_t rel_enabled = 0;

//position of the cursor at the last get_value() call
//used for relative to integrate, and absolute for speed limiting
volatile int8_t last_x = 0;
volatile int8_t last_y = 0;

//record of the analog reading of the
//center position of the joystick at startup
struct {
	uint8_t x_offset;
	uint8_t y_offset;
} calibration;

//finds approximate distance in fixed-point arithmetic
//using alpha-max plus beta-min algorithm
static int16_t distance(int16_t x, int16_t y)
{
	int16_t abs_x = abs(x);
	int16_t abs_y = abs(y);

	int16_t max, min;

	if(abs_x > abs_y)
	{
		max = abs_x;
		min = abs_y;
	}
	else
	{
		max = abs_y;
		min = abs_x;
	}

	return max + (min >> 4) * 3;
}

//gets a direct sample of the joystick analog input, with a blocking sample
static void get_sample(uint16_t* x, uint16_t* y)
{
	//start the conversion
	ADC1->CR |= ADC_CR_ADSTART;

	while((ADC1->ISR & ADC_ISR_EOC) == 0){}

	*x = ADC1->DR;

	while((ADC1->ISR & ADC_ISR_EOC) == 0){}

	*y = ADC1->DR;
}

//initializes various ADC and clock registers for joystick operation
void joystick_init()
{
	//clock
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; /* (1) */
	ADC1->CFGR2 |= ADC_CFGR2_CKMODE_1; // 1/4 speed of PCLK

	//channel
	ADC1->CHSELR = ADC_CHSELR_CHSEL5 | ADC_CHSELR_CHSEL6;
	//28.5 ADC cycles per sample
	ADC1->SMPR |= ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1;

	//enable
	if ((ADC1->ISR & ADC_ISR_ADRDY) != 0) /* (1) */
	{
		ADC1->ISR |= ADC_ISR_ADRDY; /* (2) */
	}
	ADC1->CR |= ADC_CR_ADEN; /* (3) */
	while ((ADC1->ISR & ADC_ISR_ADRDY) == 0) /* (4) */
	{
		/* For robust implementation, add here time-out management */
	}
}

//determines the calibration for centering the joystick
//called on startup
void set_calibration_point()
{
	uint16_t x,y;
	get_sample(&x, &y);

	//switch to 8bit
	x = x >> 4;
	y = y >> 4;

	calibration.x_offset = x;
	calibration.y_offset = y;
}

void set_rel(uint8_t state)
{
	if(state)
	{
		//reset to center of screen
		last_x = 0;
		last_y = 0;
	}

	rel_enabled = state;
}

uint8_t get_rel()
{
	return rel_enabled;
}

//gets the logical value of the cursor based
//on the joystick
void get_value(int8_t* x, int8_t* y)
{
	int16_t x_l, y_l;

	uint16_t spl_x, spl_y;
	get_sample(&spl_x, &spl_y);

	//switch to 8bit
	spl_x = spl_x >> 4;
	spl_y = spl_y >> 4;

	//apply calibrated offset (also centers at zero)
	int16_t real_x = spl_x - calibration.x_offset;
	int16_t real_y = spl_y - calibration.y_offset;

	//nullify if below threshold
	if(real_x > -MOVE_THRESHOLD && real_x < MOVE_THRESHOLD)
	{
		real_x = 0;
	}
	if(real_y > -MOVE_THRESHOLD && real_y < MOVE_THRESHOLD)
	{
		real_y = 0;
	}

	if(!rel_enabled)
	{
		//we are using the standard absolute cursor positioning

		//apply speed limiter
		int16_t diff_x = real_x - last_x;
		int16_t diff_y = real_y - last_y;
		int16_t dist = distance(diff_x, diff_y);

		if(dist <= MAX_CURSOR_SPEED)
		{
			//below limiting speed, use actual position value
			x_l = real_x;
			y_l = real_y;
		}
		else
		{
			//normalize difference to max speed

			//TODO this method might introduce too much inaccuracy,
			//  might need to switch to floating-point
			int16_t ratio = (dist << 3) / MAX_CURSOR_SPEED;
			x_l = last_x + ((diff_x << 3) / ratio);
			y_l = last_y + ((diff_y << 3) / ratio);
		}
	}
	else
	{
		//we are using relative positioning (cursor is integral of joystick)
		x_l = last_x + real_x / REL_SPEED_DIVIDER;
		y_l = last_y + real_y / REL_SPEED_DIVIDER;
	}

	//limit to screen width
	if(x_l < -128)
		x_l = -128;

	if(x_l > 127)
		x_l = 127;

	if(y_l < -128)
		y_l = -128;

	if(y_l > 127)
		y_l = 127;

	last_x = x_l;
	last_y = y_l;

	*x = (int8_t)x_l;
	*y = (int8_t)y_l;
}
