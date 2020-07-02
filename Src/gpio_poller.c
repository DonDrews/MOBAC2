#include "gpio_poller.h"
#include "joystick.h"

const button_def definitions[NUM_BUTTONS] =
{
	{GPIOA, 0, 0x1e}, //ITEM1 (1)
	{GPIOA, 1, 0x1f}, //ITEM2 (2)
	{GPIOA, 3, 0x20}, //ITEM3 (3)
	{GPIOA, 4, 0x07}, //SUMM1 (D)
	{GPIOA, 7, 0x09}, //SUMM2 (F)
	{GPIOA, 8, 0x21}, //WARD (4)
	{GPIOA, 9, 0x05}, //RECALL (B)
	{GPIOB, 0, 0x1c}, //CAMLOCK (Y)
	{GPIOB, 5, 0x14}, //Q (Q)
	{GPIOB, 6, 0x00}, //W (W) *temp disabled
	{GPIOB, 7, 0x00}, //E (E) *temp disabled
	{GPIOF, 0, 0x15}, //R (R)
	{GPIOF, 1, 0x13}, //SHOP (P)
	{GPIOA, 10, 0x00}, //QUICKCAST (NULL)
	{GPIOB, 1, 0x00}, //R_CLICK (NULL)
	{GPIOB, 4, 0x00} //L_CLICK (NULL)
};

button_state states[NUM_BUTTONS];

uint8_t next_sample = 0;

void io_init()
{
	//enable TIM3 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	//8kHz update for IO sample
	TIM3->PSC = 11;
	TIM3->ARR = 1000;

	//enable interrupt
	TIM3->DIER |= TIM_DIER_UIE;
	TIM3->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM3_IRQn);
	HAL_NVIC_SetPriority(TIM3_IRQn, 3, 0);

	//set all states and logs to default
	for(int i = 0; i < NUM_BUTTONS; i++)
	{
		states[i].log = 0;
		states[i].state = 0;
	}

	//enable all clocks and pins
	RCC->AHBENR |= (RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOFEN);
	for(int i = 0; i < NUM_BUTTONS; i++)
	{
		//enable pull up resistor
		definitions[i].port->PUPDR |= (1 << (definitions[i].pin * 2));
	}
}

//Called at 250us interval
//pushes another entry into the logs of each button, and if sufficient
//condition is met for debounced press, change the state
void TIM3_IRQHandler(void)
{
	if(!(TIM3->SR & TIM_SR_UIF)) // if UIF flag is not set
	{
		return;
	}

	next_sample = 1;

	TIM3->SR &= ~TIM_SR_UIF; // clear UIF flag
}

void debounce_sample()
{
	//push another value to log
	for(int i = 0; i < NUM_BUTTONS; i++)
	{
		uint32_t val = definitions[i].port->IDR & (1 << definitions[i].pin);
		//shift back into the LSB
		val = val >> definitions[i].pin;
		//remove the oldest log value
		states[i].log = states[i].log << 1;
		//add in new value
		states[i].log |= val;

		//check for state change
		if(states[i].log == 0xFF && states[i].state)
		{
			states[i].state = 0;
		}
		else if(states[i].log == 0x00 && !states[i].state)
		{
			states[i].state = 1;

			//special case: if this is the quickcast button,
			//toggle joystick positioning mode
			if(i == QUICKCAST)
			{
				set_rel(!get_rel());
			}
		}
	}

	next_sample = 0;
}

button_state* get_states()
{
	return &states[0];
}
