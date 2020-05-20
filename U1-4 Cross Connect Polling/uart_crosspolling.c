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
#include <stdbool.h>
#include "stm32l476xx.h"
#include "LED.h"
#include "SysClock.h"
#include "UART.h"
#include "uart_crosspolling.h"

void uart_crosspolling( void )
{  
    // End message -- display this by using the USART_Write function to the virtual terminal
    char *msg = "Press down on Joystick to restart tests.\r\n";
		// Add your declarations here
    uint8_t data1= 0x5A;
		uint8_t data2=0x35;
		bool case1=false;
		bool case2=false;
	
    // Loop forever, re-running tests whenever the down button on the joystick
    // is pressed.
    while (1)
		{	
        // Test 1: Write 0x5A from USART1 to UART4. Use the USART_Write function
				// to send a byte on USART1 and use the USART_Read (note that this is non blocking!)
				// to read the byte from UART4.
				// IMPORTANT -- the byte does not arrive instantly at UART4!
        USART_Write(USART1,&data1,1);
				int i;
				for(i=0;i<500;i++){
					uint8_t received=USART_Read(UART4);
					if(received == data1){
						case1=true;
						break;
					}
					else{
						USART_Delay(1000);
					}
				}
        // Test 2: Write 0x35 from UART4 to USART1. Use the same functions as in test 1
				// but for the opposite UARTs.
        USART_Write(UART4, &data2,1);
				for(i=0;i<500;i++){
					uint8_t received2=USART_Read(USART1);
					if(received2 == data2){
						case2=true;
						break;
					}
					else{
						USART_Delay(1000);
					}
				}
				// If both tests passed turn on the green LED.
				// If either or both fail turn on the red LED.
        if( case1 && case2){
					Green_LED_On();
				}
				else{
					Red_LED_On();
				}
				
        // Send the message to the virtual terminal to alert user of the test completion.
        USART_Write(USART2, (uint8_t *)msg, strlen(msg));
				
				// Wait for the joystick down button to be pressed and then wait for
				// it to be released. 
				while((GPIOA->IDR & 0x20) == 0x00){
					USART_Delay(1000);
				}
				while((GPIOA->IDR & 0x20) != 0x00){
					USART_Delay(1000); 
				}
				// Now urn off both LEDs and wait for 500 ms. This provides a visual indication
				// that the test is restarting. Use the USART_Delay function for the delay.
				Green_LED_Off();
				Red_LED_Off();
				USART_Delay(500000); // 500 ms
    }
}

