/*
 * timer.c
 *
 *  Created on: Feb 2, 2024
 *      Author: Marko Topalovic
 */

#include "timer.h"

//Function prototypes
static void init_timer2(void);
static void init_timer2_irq();

void timer_init(void) {

	init_timer2();
}

static void init_timer2(void) {

	RCC->APB1ENR |= (0b1 << 0);	//TIM2 clock enable

	TIM2->CR1 |= (0b1 << 0);

	TIM2->CR1 |= (0b1 << 2);
	TIM2->EGR |= (0b1 << 0);

	// APB1 currently 84 MHz -> desired 1 MHz
	TIM2->PSC = 84 - 1;
	// 1 MHz currently -> desired 1 KHz
	TIM2->ARR = 1000 -1; // -> 1 ms

	while (!(TIM2->SR & (0b01 << 0))) {
			__NOP();
		}

}

void timers_irq_init(void){

	init_timer2_irq();

}

static void init_timer2_irq(){

	NVIC->ISER[0] |= (1 << 28);

}

void TIM2_IRQHandler(){

	//What we want to be executed


}
