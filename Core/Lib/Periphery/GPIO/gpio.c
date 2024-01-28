/*
 * gpio.c
 *
 *  Created on: Jan 28, 2024
 *      Author: Marko Topalovic
 */

#include "gpio.h"

static void init_port_a(void);

void gpio_init(void) {
	init_port_a();
}

static void init_port_a(void) {

	const uint8_t pin_a = 5;	//LED PA5 - Green

	RCC->AHB1ENR |= (0b1 << 0);  //Enable peripheries GPIOA ENABLE

	GPIOA->MODER |= (0b01 << 2 * pin_a);	//Output mode
	GPIOA->OTYPER &= ~(0b1 << pin_a);		//Output push-pull
	GPIOA->ODR |= (0b1 << pin_a);			//Output data
}
