#ifndef __IO_STM8_ASSIN_H__
#define __IO_STM8_ASSIN_H__

#include "os_cpu.h"

#ifndef __always_inline__
#define __always_inline__  _Pragma("inline=forced") inline
#endif

#ifndef _BV
#define _BV(A)       (1U<<(A))
#endif

#define STM8_GPIO_ASSIGN(A, B, C)\
__always_inline__ static void   GPIO_##A##_Set(void)                                {GPIO##B->ODR |=  _BV( C);}\
__always_inline__ static void   GPIO_##A##_Clr(void)                                {GPIO##B->ODR &= ~_BV( C);}\
__always_inline__ static void   GPIO_##A##_MakeOut(void)                            {GPIO##B->DDR |=  _BV( C);}\
__always_inline__ static void   GPIO_##A##_MakeIn(void)                             {GPIO##B->DDR &= ~_BV( C);}\
__always_inline__ static void   GPIO_##A##_SetCR1(void)                             {GPIO##B->CR1 |=  _BV( C);}\
__always_inline__ static void   GPIO_##A##_ClrCR1(void)                             {GPIO##B->CR1 &= ~_BV( C);}\
__always_inline__ static void   GPIO_##A##_SetCR2(void)                             {GPIO##B->CR2 |=  _BV( C);}\
__always_inline__ static void   GPIO_##A##_ClrCR2(void)                             {GPIO##B->CR2 &= ~_BV( C);}\
__always_inline__ static void   GPIO_##A##_MakeInputFloatingWithoutInterrupt(void)  {GPIO_##A##_MakeIn(); GPIO_##A##_ClrCR1(); GPIO_##A##_ClrCR2();}\
__always_inline__ static void   GPIO_##A##_MakeInputPullupWithoutInterrupt(void)    {GPIO_##A##_MakeIn(); GPIO_##A##_SetCR1(); GPIO_##A##_ClrCR2();}\
__always_inline__ static void   GPIO_##A##_MakeInputFloatingWithInterrupt(void)     {GPIO_##A##_MakeIn(); GPIO_##A##_ClrCR1(); GPIO_##A##_SetCR2();}\
__always_inline__ static void   GPIO_##A##_MakeInputPullupWithInterrupt(void)       {GPIO_##A##_MakeIn(); GPIO_##A##_SetCR1(); GPIO_##A##_SetCR2();}\
__always_inline__ static void   GPIO_##A##_MakeOutputOpenDrainSlow(void)            {GPIO_##A##_MakeOut();GPIO_##A##_ClrCR1(); GPIO_##A##_ClrCR2();}\
__always_inline__ static void   GPIO_##A##_MakeOutputPushPullSlow(void)             {GPIO_##A##_MakeOut();GPIO_##A##_SetCR1(); GPIO_##A##_ClrCR2();}\
__always_inline__ static void   GPIO_##A##_MakeOutputOpenDrainFast(void)            {GPIO_##A##_MakeOut();GPIO_##A##_ClrCR1(); GPIO_##A##_SetCR2();}\
__always_inline__ static void   GPIO_##A##_MakeOutputPushPullFast(void)             {GPIO_##A##_MakeOut();GPIO_##A##_SetCR1(); GPIO_##A##_SetCR2();}\
__always_inline__ static void   GPIO_##A##_Toggle(void)                             {GPIO##B->ODR ^= _BV( C);}\
__always_inline__ static uint8  GPIO_##A##_ReadIn(void)                             {return ((GPIO##B->IDR & _BV( C)) != 0);}\
__always_inline__ static uint8  GPIO_##A##_ReadOut(void)                            {return ((GPIO##B->ODR & _BV( C)) != 0);}\
__always_inline__ static uint8  GPIO_##A##_ReadDir(void)                            {return ((GPIO##B->DDR & _BV( C)) != 0);}\
__always_inline__ static uint8  GPIO_##A##_Read(void)                               {return GPIO_##A##_ReadIn();}\
__always_inline__ static void   GPIO_##A##_Out(uint8 x)                             {(x)?(GPIO_##A##_Set()):(GPIO_##A##_Clr());}\
__always_inline__ static uint8  GPIO_##A##_IsOutHigh(void)                          {return GPIO_##A##_ReadOut();}\
__always_inline__ static uint8  GPIO_##A##_IsOutLow(void)                           {return !GPIO_##A##_ReadOut();}

#define STM8_GPIO_ASSIGN_POLARITY(A, B, C, X) \
STM8_GPIO_ASSIGN(A, B, C)\
__always_inline__ static void   GPIO_##A##_On(void)                                  { (X)?(GPIO_##A##_Set()):(GPIO_##A##_Clr());}\
__always_inline__ static void   GPIO_##A##_Off(void)                                 {(!X)?(GPIO_##A##_Set()):(GPIO_##A##_Clr());}\
__always_inline__ static uint8  GPIO_##A##_IsOn(void)                                {return  (X)?GPIO_##A##_IsOutHigh():GPIO_##A##_IsOutLow();}\
__always_inline__ static uint8  GPIO_##A##_IsOff(void)                               {return (!X)?GPIO_##A##_IsOutHigh():GPIO_##A##_IsOutLow();}

#endif
