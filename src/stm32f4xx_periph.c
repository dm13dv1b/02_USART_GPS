/* stm32f4xx_periph.c */
#include "stm32f4xx.h"
#include "stm32f4xx_periph.h"
#define MAX_STRLEN 256

char usart_buffer[MAX_STRLEN];

void USART2_INIT(void);
void TIM2_Init(void);
void DMA1_Init(void);

void TIM2_Init(void)
{
		//LED init PD12
			GPIOD	->	MODER			|=	(1<<24);						//PD12 = output
			GPIOD ->	OTYPER		&=	(1<<12);						//Output Push/pull
			GPIOD ->	OSPEEDR		&=	~(3<<24);						//50Mhz fast speed
			GPIOD ->	OSPEEDR		|=	(2<<24);		
			GPIOD ->	PUPDR			&=	~(3<<24);						//PD12 pull up
			GPIOD	->	PUPDR			|=	(1<<24);
		//LED init PD12

		//LED init PD13
			GPIOD	->	MODER			|=	(1<<26);						//PD13 = output
			GPIOD ->	OTYPER		&=	(1<<13);						//Output Push/pull
			GPIOD ->	OSPEEDR		&=	~(3<<26);						//50Mhz fast speed
			GPIOD ->	OSPEEDR		|=	(2<<26);		
			GPIOD ->	PUPDR			&=	~(3<<26);						//PD13 pull up
			GPIOD	->	PUPDR			|=	(1<<26);
		//LED init PD13

		//LED init PD14
			GPIOD	->	MODER			|=	(1<<28);						//PD14 = output
			GPIOD ->	OTYPER		&=	(1<<14);						//Output Push/pull
			GPIOD ->	OSPEEDR		&=	~(3<<28);						//50Mhz fast speed
			GPIOD ->	OSPEEDR		|=	(2<<28);		
			GPIOD ->	PUPDR			&=	~(3<<28);						//PD14 pull up
			GPIOD	->	PUPDR			|=	(1<<28);
		//LED init PD14

		//LED init PD14
			GPIOD	->	MODER			|=	(1<<30);						//PD14 = output
			GPIOD ->	OTYPER		&=	(1<<15);						//Output Push/pull
			GPIOD ->	OSPEEDR		|=	(2<<30);						//50Mhz fast speed
			GPIOD ->	PUPDR			|=	(1<<30);						//PD14 pull up
		//LED init PD14
		
	TIM2->CR1 &= ~TIM_CR1_CEN;
	prescaler = SystemCoreClock/2;
	prescaler /=Timer_Frequency;
	prescaler -=1;
	TIM2	->	PSC			=		Timer_Frequency-1;
	TIM2	->	ARR			=		prescaler;
	NVIC_EnableIRQ(TIM2_IRQn);
	TIM2->DIER |= TIM_DIER_UIE;
	TIM2->CR1 |= TIM_CR1_CEN;
}

void USART2_INIT(void)
{
	BaudRate = 38400;
	GPIOA	->	MODER 		|=	GPIO_MODER_MODER3_1;		// RX PD6 to alternate function output push-pull at 50 MHz 0x10
	GPIOA	->	MODER 		|=	GPIO_MODER_MODER2_1;		// TX PD5 to alternate function output push-pull at 50 MHz 0x10
	GPIOA ->	OSPEEDR		|=  GPIO_OSPEEDER_OSPEEDR3_0 | GPIO_OSPEEDER_OSPEEDR3_1;		//50Mhz fast speed
	GPIOA ->	OSPEEDR		|=	GPIO_OSPEEDER_OSPEEDR2_0 | GPIO_OSPEEDER_OSPEEDR2_1;
	GPIOA ->	PUPDR			|=  GPIO_PUPDR_PUPDR2_0;
	GPIOA	->	AFR[0]		|=	(7<<8);
	GPIOA	->	AFR[0]		|=	(7<<12);
	BRR = (SystemCoreClock/4) / (BaudRate*16);
	USART2 ->	BRR = (68 << 4 ) + 0x06; //38400br
	USART2 -> CR1 |= USART_CR1_UE | USART_CR1_RE | USART_CR1_TE;
	USART2 -> CR3 |= USART_CR3_DMAR;
}

void DMA1_Init(void)
{
	RCC -> AHB1ENR |= RCC_AHB1ENR_DMA1EN;				// Enable DMA1 clcok
	DMA1_Stream5 -> CR &= ~DMA_SxCR_EN;					// disable Stream6
	DMA1_Stream5 -> PAR = (uint32_t)&USART2->DR;							// from periph port register
	DMA1_Stream5 -> M0AR = (uint32_t) &usart_buffer;					// write to memory
	DMA1_Stream5 -> NDTR = 256;									// number of data items
	DMA1_Stream5 -> CR |= DMA_SxCR_MINC;				// memory increment
	DMA1_Stream5 -> CR |= DMA_SxCR_CHSEL_2;		// select chanel0
	DMA1_Stream5 -> CR &= ~DMA_SxCR_MSIZE_0;			// half-word (16bit) memory data size
	DMA1_Stream5 -> CR &= ~DMA_SxCR_PSIZE_0;			// half-word (16bit) peripherial data size
	DMA1_Stream5 -> CR |= DMA_SxCR_TCIE;				// transaction complete interrupt
	DMA1_Stream5 -> CR |= DMA_SxCR_CIRC;				// non enable continous mode
	DMA1_Stream5 -> CR |= DMA_SxCR_EN;					// enable Stream6
	NVIC_EnableIRQ(DMA1_Stream5_IRQn);					// enable IRQ	
}
