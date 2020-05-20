#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "inputHandler.h"
#include "clock.h"

// Sanchit Monga

// different strings to be compared so that the input can be checked
char* rOn ="RON\r";
char* rOff="ROFF\r";
char* gOn="GON\r";
char* gOff="GOFF\r";
char* rFlash="RFLASH\r";
char* gFlash="GFLASH\r";
char* flashOff="FLASHOFF\r";
int flagRedFlash=0;
int flagGreenFlash=0;
int countSecs=0;

// Messages to be printed when an event occurs
char invalid[]="Invalid command\r\n";
char RON[]="Red LED is on\r\n";
char GON[]="Green LED is on\r\n";
char ROFF[]="RED LED is off\r\n";
char GOFF[]="Green LED is off\r\n";
char RFLASH[]="Red LED is flashing\r\n";
char GFLASH[]="Green LED is flashing\r\n";
char FLASHOFF[]="Flash off\r\n";


// Handling the input when the backspace is pressed
void handleBackSpace(char* str,int i){
	i--;
	str[i]='\0';
	int spaces=40;
	char input[spaces];
	// going to the left most point in the buffer
	USART_Write(USART2, (uint8_t *)"\r",1);
	
	// adding bunch of spaces to push back the previous command
	int k;
	for(k=0;k<spaces;k++){
		input[k]=' ';
	}
	USART_Write(USART2, (uint8_t *)input, strlen(input));
	// writing the original string back to the buffer
	USART_Write(USART2, (uint8_t *)"\r",1);
	USART_Write(USART2, (uint8_t *)str,strlen(str));
}

void setFlash(int color){
	if(color==1){					// if the red light is flashing
		Red_LED_Toggle();														
	}
	else if(color==0){		// if the green light is flashing
		Green_LED_Toggle();															// using the red led toggle
	}
	else{					// if both the lights are flashing
		Red_LED_Toggle();														
		Green_LED_Toggle();															// using the red led toggle
	}
}

bool isRedFlashing(int a){
	return flagRedFlash==1;
}

bool isGreenFlashing(int a){
	return flagGreenFlash==1;
}

void checkFlashing(int a){
	countSecs+=1;
	if(countSecs>100){
		if(isGreenFlashing(0)){
			setFlash(0);
		}
		if(isRedFlashing(0)){
			setFlash(1);
		}
		countSecs=0;
	}
}

void setFlashOff(){
	USART_Write(USART2, (uint8_t *)FLASHOFF, strlen(FLASHOFF));
		if(flagRedFlash){
			Red_LED_Off();
			flagRedFlash=0;
		}
		if(flagGreenFlash){
			Green_LED_Off();	
			flagGreenFlash=0;
		}
}

int compare(char *inp, char *str){
	int flagCheck=0;
	int i=strlen(str);
	for(int j=0;j<i;j++){
		if(inp[j]!=str[j]){
			flagCheck=1;
			break;
		}
	}
	return flagCheck;
}

// handling the input when the enter key is pressed
void handler(char* str){
	if(compare(str,rOn)==0){
		USART_Write(USART2, (uint8_t *)RON, strlen(RON));
		flagGreenFlash=0;
		Red_LED_On();
	}
	else if(compare(str,rOff)==0){
		USART_Write(USART2, (uint8_t *)ROFF, strlen(ROFF));
		flagRedFlash=0;
		Red_LED_Off();
	}
	else if(compare(str,gOn)==0){
		USART_Write(USART2, (uint8_t *)GON, strlen(GON));
		flagGreenFlash=0;
		Green_LED_On();
	}
	else if(compare(str,gOff)==0){
		USART_Write(USART2, (uint8_t *)GOFF, strlen(GOFF));
		flagGreenFlash=0;
		Green_LED_Off();
	}
	else if(compare(str,rFlash)==0){	// if the command is RFLASH
		USART_Write(USART2, (uint8_t *)RFLASH, strlen(RFLASH));
		flagRedFlash=1;																// making the flag true
	}
	else if(compare(str,gFlash)==0){		// if the command is GFLASH
		USART_Write(USART2, (uint8_t *)GFLASH, strlen(GFLASH));
		flagGreenFlash=1;																// making the flag true
	}
	else if(compare(str,flashOff)==0){
		setFlashOff();
	}
	else{
		USART_Write(USART2, (uint8_t *)invalid, strlen(invalid));
	}
}


