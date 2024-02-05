/*
 * timer.h
 *
 *  Created on: Feb 2, 2024
 *      Author: Marko Topalovic
 */

#ifndef LIB_PERIPHERY_TIMER_TIMER_H_
#define LIB_PERIPHERY_TIMER_TIMER_H_

#include "stm32f4xx.h"
#include <stdint.h>

//Function prototypes
void timer_init(void);
void timers_irq_init(void);
uint8_t isTimeFlag95s();
uint8_t isTimeFlag100s();
uint32_t getSysTime();
void setTimeOut(uint32_t delay);
uint8_t isTimeOut();

#endif /* LIB_PERIPHERY_TIMER_TIMER_H_ */
