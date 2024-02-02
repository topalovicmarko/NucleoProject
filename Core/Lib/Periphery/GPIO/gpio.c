/*
 * gpio.c
 *
 *  Created on: Jan 28, 2024
 *      Author: Marko Topalovic
 */

#include "gpio.h"

static void init_port_a(void);
static void init_port_c(void);

void gpio_init(void) {
	init_port_a();
	init_port_c();
}

static void init_port_a(void) {

	const uint8_t pin_5 = 5;	//LED PA5 - Green
	const uint8_t pin_6 = 6;	//External diode on pin PA13

	RCC->AHB1ENR |= (0b1 << 0);  //Enable peripheries GPIOA ENABLE

	GPIOA->MODER |= (0b01 << 2 * pin_5);	//Output mode
	GPIOA->OTYPER &= ~(0b1 << pin_5);		//Output push-pull
	GPIOA->ODR |= (0b1 << pin_5);			//Output data

	GPIOA->MODER |= (0b01 << 2 * pin_6);	//Output mode
	GPIOA->OTYPER &= ~(0b1 << pin_6);		//Output push-pull
	GPIOA->ODR |= (0b0 << pin_6);			//Output data

}

static void init_port_c(void) {

	const uint8_t pin_13 = 13;	//PC13 USER (Blue) button

	RCC->AHB1ENR |= (0b1 << 2);	//Enable peripheries GPIOC ENABLE

	GPIOC->MODER |= (0b00 << 2 * pin_13);	//Input mode
	GPIOC->PUPDR |= (0b01 << 2 * pin_13);	//Pull-up

}
