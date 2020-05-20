#ifndef __STM32L476G_DISCOVERY_clock_H
#define __STM32L476G_DISCOVERY_clock_H
#include "stm32l476xx.h"
#include <stdbool.h>

void SysTick_Initialize (uint32_t ticks);
void Delay (uint32_t nTime);
void SysTick_Handler (void);

#endif
