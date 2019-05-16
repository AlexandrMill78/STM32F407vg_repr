#ifndef MCU_INI_H
#define MCU_INI_H

#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void LEDs_ini(void);  // function prototype 
void Button_ini(void);
void USART2_ini(void);

void Laser_Sensor_ini(void);

#endif
