/* stm32f4xx_periph.c */
#include "stm32f4xx.h"

static unsigned int BaudRate;
static unsigned int BRR;
static uint32_t Timer_Frequency = 42000;
static uint32_t prescaler;

void USART1_INIT(void);
void USART2_INIT(void);
void TIM2_Init(void);
