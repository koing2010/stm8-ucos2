#ifndef __PERIPH_IO_H__
#define __PERIPH_IO_H__
#include "iostm8s207c8.h"
//#include "io_stm8_assign.h"

//STM8_GPIO_ASSIGN_POLARITY(LED_0,D,3,1);  //LED_0:PD3
//STM8_GPIO_ASSIGN_POLARITY(LED_1,D,2,1);  //LED_1:PD2
//STM8_GPIO_ASSIGN_POLARITY(LED_2,D,0,1);  //LED_2:PD0

#define LED_0_ON             PD_ODR_ODR0 = 1
#define LED_0_OFF            PD_ODR_ODR0 = 0

#define LED_1_ON             PD_ODR_ODR3 = 1
#define LED_1_OFF            PD_ODR_ODR3 = 0
#endif