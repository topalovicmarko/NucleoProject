/*
 * timer.c
 *
 *  Created on: Feb 2, 2024
 *      Author: Marko Topalovic
 */

#include "timer.h"

typedef struct Time_flags{

	uint8_t f1s				 : 1;
	uint8_t f95s 			 : 1;
	uint8_t f100s 			 : 1;
	uint8_t f_time_out_start : 1;
	uint8_t f_time_out 		 : 1;

}TTime_flags;

//Variables
TTime_flags t_flag = {0, 0, 0, 0, 0};
static volatile uint32_t sys_time = 0;
static volatile uint32_t time_out = 0;

//Function prototypes
static void init_timer2(void);
static void init_timer2_irq();

void timer_init(void) {

	init_timer2();
}

void timers_irq_init(void){

	init_timer2_irq();

}

static void init_timer2(void) {

	RCC->APB1ENR |= (0b1 << 0);	//TIM2 clock enable

	TIM2->CR1 |= (0b1 << 2);	//URS - Update request source
	TIM2->CR1 &= ~(0b1 << 1);	//UDIS - Update disable

	TIM2->EGR |= (0b1 << 0);	//UG - Update generation

	// APB1 currently 84 MHz -> desired 1 MHz
	TIM2->PSC = 84 - 1;	//84 MHz / 84 = 1MHz
	// 1 MHz currently -> desired 1 KHz
	TIM2->ARR = 1000 -1; // -> 1 ms		//-1 is put because the timer counts from 0

	TIM2->DIER |= (0b1 << 0); //Update interrupt enable

	TIM2->CR1 |= (0b1 << 0);	//CEN - Counter enabled

	while (!(TIM2->SR & (0b01 << 0))) {
			__NOP();
		}

}

uint8_t isTimeFlag95s(){
	return t_flag.f95s;
}

uint8_t isTimeFlag100s(){
	return t_flag.f100s;
}

uint32_t getSysTime(){
	return sys_time;
}

static void init_timer2_irq(){

	NVIC->ISER[0] |= (1 << 28);	//Permission for global interrupt vector TIM2 (ISER - Interrupt service enable request)

}

void setTimeOut(uint32_t delay){

	if(time_out == 0 && t_flag.f_time_out_start == 0){

		time_out = delay;
		t_flag.f_time_out_start = 1;

	}

}

uint8_t isTimeOut(){
	return t_flag.f_time_out;
}

void TIM2_IRQHandler(){

	if (TIM2->SR & (0b1 << 0))	//We check in the status register whether an interrupt has occurred
	{
		TIM2->SR &= ~(0b1 << 0);	//We can reset that bit to zero only in software

		// What we want to be executed in 1 ms
		sys_time++;	//We increment the sys_time every ms

		if ((sys_time % 1000) == 0)
			t_flag.f1s = 1;

		if ((sys_time % 95000) == 0)
					t_flag.f95s = 1;

		if ((sys_time % 100000) == 0)
					t_flag.f100s = 1;

		if(t_flag.f_time_out_start && time_out != 0){
			time_out--;
			t_flag.f_time_out = 0;
		}
		else if (t_flag.f_time_out_start && (time_out == 0))
		{
			t_flag.f_time_out = 1;
			t_flag.f_time_out_start = 0;
		}

	}

}
