#include "stm32f4xx.h"

void RCC_Init(void);

void RCC_Init(void)
{
	RCC 	->	APB1ENR = RCC_APB1ENR_USART2EN | RCC_APB1ENR_TIM2EN;
	RCC		->	AHB1ENR		|=	RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIODEN; 		// Enable PORTD
}
