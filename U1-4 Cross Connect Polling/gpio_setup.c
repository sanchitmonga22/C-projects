/*
 * gpio_setup.c: UART Cross-Connect main method for program.
 * Initializes USART1 and UART4 and sets up the joystick to accept input.
 * 
 * Written by Joshua Morrison (jmm4077@rit.edu)
 * CMPE-240-01 (Fall 2018), Prof. Larry Kiser
 * 
 * Last Edited: 11/05/2018, 1:21pm
 * Updated L. Kiser 11/07/2018 -- refactored into multiple modules.
 */

#include <stdlib.h>
#include <string.h>

#include "stm32l476xx.h"
#include "LED.h"
#include "SysClock.h"
#include "UART.h"
#include "uart_crosspolling.h"

// Set up GPIO for USART1.
// USART1 uses pins PB6 and PB7.
void setup_gpio_usart1() {
    // Enable GPIO Port B clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    
    GPIOB->MODER &= ~(0xF << 12);  // Clear mode bits for pins 6 and 7
    GPIOB->MODER |= 0xA << 12;     // Alternate Function mode for pins 6 and 7
    
    // Alternate function 7: USART1
    GPIOB->AFR[0] |= 0x77 << 24;
    
    GPIOB->OSPEEDR |= 0xF << 12;   // Set pins 6 and 7 to High speed
    
    GPIOB->PUPDR &= ~(0xF << 12);  // Clear bits for pins 6 and 7
    GPIOB->PUPDR |= 0x5 << 12;     // Set pins 6 and 7 to Pull-up
    
    GPIOB->OTYPER &= ~(0x3 << 6);  // Set pins 6 and 7 to Open Drain
    
    // Enable USART1 clock
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    
    // Select System Clock (SYSCLK) as USART1 clock source
    RCC->CCIPR &= ~RCC_CCIPR_USART1SEL;
    RCC->CCIPR |= RCC_CCIPR_USART1SEL_0;
}


// Set up the GPIO for UART4 and the joystick (they both use GPIO port A).
// UART4 uses pins PA0 and PA1. We will be using pin PA5 (down) for the joystick.
void setup_gpio_uart4_and_joystick() {
    // Enable GPIO Port A clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    
    // Pin PA5 is left in Input mode
    GPIOA->MODER &= ~(0xF | 0x3 << 10);  // Clear mode bits for pins 0, 1, and 5
    GPIOA->MODER |= 0xA;  // Alternate Function mode for pins 0 and 1
    
    // Alternate function 8: UART4
    GPIOA->AFR[0] |= 0x88;
    
    GPIOA->OSPEEDR |= 0xF;  // Set pins 0 and 1 to High speed
    
    GPIOA->PUPDR &= ~(0xF | 0x3 << 10);  // Clear bits for pins 0, 1, and 5
    GPIOA->PUPDR |= (0x5 | 0x2 << 10);   // Set pins 0 and 1 to Pull-up, pin 5 to Pull-down
    
    GPIOA->OTYPER &= ~0x3;  // Set pins 0 and 1 to Open Drain
    
    // Enable UART4 clock
    RCC->APB1ENR1 |= RCC_APB1ENR1_UART4EN;
    
    // Select System Clock (SYSCLK) as UART4 clock source
    RCC->CCIPR &= ~RCC_CCIPR_UART4SEL;
    RCC->CCIPR |= RCC_CCIPR_UART4SEL_0;
}
