#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "inputHandler.h"
#include "clock.h"

//@author: Sanchit Monga

char RxComByte = 0;
uint8_t buffer[BufferSize];
char str[] = "Give LED control Panel enter the commands:\r\n";

int main(void){
	
	char rxByte;// character to store input from the console
	int i=0; // integer to keep track of the index of the character entered in the console
	int flag=0;	// checking if we need to reset the array after it has been compared
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	UART2_Init();
	USART_Write(USART2, (uint8_t *)str, strlen(str)); // displaying the initial message
	
	SysTick_Initialize(800000);
	char *input=(char *)malloc(10*sizeof(char)); // array to store input from the console
	while (1){
		rxByte = USART_Read(USART2); // reading the input from the console
		
		Delay(1);
		
		checkFlashing(0);             // function that is continuously checking flashing
		if(rxByte==0){								// if there is no input
			continue;
		}
		USART_Write(USART2, (uint8_t *)&rxByte, 1); // displaying the characters as the user types
		input[i]=rxByte; // storing the character in the input array
		if(input[i]=='\r'){    // checking if the user pressed the enter key
			USART_Write(USART2, (uint8_t *)"\r\n", 2);  
			handler(input);				// calling the function in the inputHandler class to handle the input from here
			flag=1;								//the flag means that the string has to be reset
		}
		else if(rxByte==127 || rxByte==8){	// if the user pressed backspace
			handleBackSpace(input,i);	// calling the function in the inputHandler class to handle the backspace
			if(i==0){
				input[0]='\0';
				continue;
			}
			i--;
			continue;
		}
		i++;   // incrementing the counter to the next index
		if(i>10 || flag==1){		// checking if the string has to be reset
			input[0]='\0';				// emptying the array
			flag=0;
			i=0;
		}
	}
}
