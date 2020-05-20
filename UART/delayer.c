#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void SysTick_Initialize (uint32_t ticks) {
		SysTick->CTRL = 0; // Disable SysTick
		SysTick->LOAD = ticks - 1; // Set reload register
		// Set interrupt priority of SysTick to least urgency (i.e., largest priority value)
		NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
		SysTick->VAL = 0; // Reset the SysTick counter value
		// Select processor clock: 1 = processor clock; 0 = external clock
		SysTick->CTRL |= 1;
		// Enables SysTick interrupt, 1 = Enable, 0 = Disable
		//SysTick->CTRL |= 1;
		// Enable SysTick
		//SysTick->CTRL |= 1;
}
		
void Delay (uint32_t nTime) {
	// nTime: specifies the delay time length
	int TimeDelay = nTime; // TimeDelay must be declared as volatile
	while(TimeDelay != 0); // Busy wait
}

volatile int32_t TimeDelay;
int main (void) {
	SysTick_Initialize(1000); // Interrupt period = 1000 cycles
	Delay(100); // Delay 100 ticks
}

void SysTick_Handler (void) { // SysTick interrupt service routine
	if (TimeDelay > 0) // Prevent it from being negative
		TimeDelay--; // TimeDelay is a global volatile variable
}