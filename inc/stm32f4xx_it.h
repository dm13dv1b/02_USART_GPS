/* stm32f4xx_it.h */
#include "stm32f4xx.h"

#define MAX_STRLEN 256

extern char received_string[MAX_STRLEN+1];
extern char received_buff[MAX_STRLEN+1];

void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
