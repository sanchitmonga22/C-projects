#ifndef __STM32L476G_DISCOVERY_inputHandler_H
#define __STM32L476G_DISCOVERY_inputHandler_H
#include "stm32l476xx.h"
#include <stdbool.h>

void handler(char* str);
void handleBackSpace(char* str, int i);
void setFlash(int color);
void checkFlashing(int a);
bool isGreenFlashing(int a);
bool isRedFlashing(int a);
void wait(void);
#endif
