/*
 * gpio.h
 *
 *  Created on: Jan 28, 2024
 *      Author: Marko Topalovic
 */

#ifndef LIB_PERIPHERY_GPIO_GPIO_H_
#define LIB_PERIPHERY_GPIO_GPIO_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include "../TIMER/timer.h"

//Function prototypes
void gpio_init(void);
void external_LED_with_button(void);
void toggling_LED();

#endif /* LIB_PERIPHERY_GPIO_GPIO_H_ */
