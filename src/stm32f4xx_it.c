/* stm32f4xx_it.c */
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "nmea.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

void USART2_IRQHandler(void);
void TIM2_IRQHandler(void);
void DMA1_Stream5_IRQHandler(void);

extern void delay_ms(uint32_t ms);
uint16_t temp;
extern char usart_buffer[MAX_STRLEN];
static __IO uint32_t TimingDelay;

void SysTick_Handler(void)
{
	//SysTick->CTRL = 0x07;
	TimingDelay--;
    //TimingDelay_Decrement();
}

void USART2_IRQHandler(void)
	{	
		temp = USART2->SR;
		temp = USART2->DR;
		
		if ((USART2 ->	SR &	USART_SR_RXNE) == 0)
		{
			char t = USART2->DR; // the character from the USART1 data register is saved in t
				}
	}

void TIM2_IRQHandler(void)
{
	if ( TIM2->SR & TIM_SR_UIF )
	{
	GPIOD->ODR |= GPIO_ODR_ODR_12;
	delay_ms(50);
	GPIOD->ODR &= ~GPIO_ODR_ODR_12;	
	Read_USART();
	TIM2->SR &= ~TIM_SR_UIF;
	}
}

void DMA1_Stream5_IRQHandler(void)
{
	if (DMA1 -> HISR & DMA_HISR_HTIF5)
	{
		DMA1 -> HIFCR |= DMA_HIFCR_CHTIF5;	
	}
	if (DMA1 -> HISR & DMA_HISR_TCIF5)
	{
		// clear DMA1 interrupt pending bit
		DMA1 -> HIFCR |= DMA_HIFCR_CTCIF5 | DMA_HIFCR_CHTIF5;
	}
	NVIC->ICPR[0] |=(1<<7);
}
