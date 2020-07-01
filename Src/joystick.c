#include "joystick.h"
#include "stdlib.h"

uint8_t rel_enabled = 0;

uint8_t last_x = CENTER;
uint8_t last_y = CENTER;

struct {
	int8_t x_offset;
	int8_t y_offset;
} calibration;

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

	calibration.x_offset = -x;
	calibration.y_offset = -y;
}

void start_rel()
{
	rel_enabled = 1;

	//reset to center of screen
	last_x = CENTER;
	last_y = CENTER;
}

void end_rel()
{
	rel_enabled = 0;
}

//gets the logical value of the cursor based
//on the joystick
void get_value(uint8_t* x, uint8_t* y)
{
	int16_t x_l, y_l;

	uint16_t spl_x, spl_y;
	get_sample(&spl_x, &spl_y);

	//switch to 8bit
	spl_x = spl_x >> 4;
	spl_y = spl_y >> 4;

	//apply calibrated offset
	int16_t real_x = spl_x + calibration.x_offset;
	int16_t real_y = spl_y + calibration.y_offset;

	//nullify if below threshold
	if(real_x > CENTER - MOVE_THRESHOLD && real_x < CENTER + MOVE_THRESHOLD)
	{
		real_x = 0;
	}
	if(real_y > CENTER - MOVE_THRESHOLD && real_y < CENTER + MOVE_THRESHOLD)
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
	if(x_l < 0)
		x_l = 0;

	if(x_l > 255)
		x_l = 255;

	if(y_l < 0)
		y_l = 0;

	if(y_l > 255)
		y_l = 255;

	last_x = x_l;
	last_y = y_l;

	x = (uint8_t)x_l;
	y = (uint8_t)y_l;
}

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
