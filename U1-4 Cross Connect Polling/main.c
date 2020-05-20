/*
 * main.c: UART Cross-Connect main method for program. Initializes USART1 and
 * UART4, sets up the joystick to accept input, and then tests communication
 * between the two U[S]ART interfaces by passing a byte between them.
 * 
 * Written by Joshua Morrison (jmm4077@rit.edu)
 * CMPE-240-01 (Fall 2018), Prof. Larry Kiser
 * 
 * Last Edited: 11/05/2018, 1:21pm
 * Updated L. Kiser 11/07/2018 refactoring and added delays
 * 
 *
 * Sanchit Monga
 */

#include <stdlib.h>
#include <string.h>

#include "stm32l476xx.h"
#include "LED.h"
#include "SysClock.h"
#include "UART.h"
#include "uart_crosspolling.h"


static void system_setup( void )
{
    System_Clock_Init();
    LED_Init();
    UART2_Init();
    
    // Setup, then initialize, USART1, UART4, and the joystick
    setup_gpio_usart1();
    setup_gpio_uart4_and_joystick();
    USART_Init(USART1);
    USART_Init(UART4);
}

int main( void )
{
		system_setup() ;
		uart_crosspolling() ;
}

