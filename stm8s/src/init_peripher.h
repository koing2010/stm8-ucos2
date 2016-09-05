/************************************************************************************

File_name:      init_peripher.h
Description:    the header file of  init_peripher_c .

************************************************************************************/
#ifndef     __INIT_PERIPHER_H__
#define     __INIT_PERIPHER_H__

/*==================================================================================
@ Include files
*/
#include "iostm8s207c8.h"
#include <intrinsics.h>

/*==================================================================================
@ Typedefs
*/
typedef unsigned char   uchar;
//typedef unsigned char   u8;
//typedef unsigned int   u16;

/*==================================================================================
@ Constants and defines
*/
#define ENABLE_UART2_IRQ            UART2_CR2 = 0x2c //允许接收，发送，开接收中断
#define DISABLE_UART2_IRQ           UART2_CR2=0x0c   //关闭接受中断
#define ENABLE_TIM2_IRQ             TIM2_IER=0x01    // 使能中断
#define DISABLE_TIM2_IRQ            TIM2_IER=0x00    // 禁止中断

#define DISABLE_TIM4                TIM4_CR1=0x00  //停止 TIM4
#define ENABLE_TIM4                 TIM4_CR1=0x01  //启动 TIM4

#define DISABLE_TIM1_PWM      TIM1_CR1 &= 0xFE//;TIM1_CCMR1_OC1M = 0x05
#define ENABLE_TIM1_PWM       TIM1_CR1 |= 0x01;TIM1_CCMR1_OC1M = 0x06
#define Clear_Wait_Dog        IWDG_KR=0xAA

#define ALARM_INDICATOR       PA_ODR_ODR6  //警示
#define RUNNING_INDICATOR     PD_ODR_ODR3  //运行
#define U1_STATUS_INDICATOR   PC_ODR_ODR1
#define U2_STATUS_INDICATOR   PC_ODR_ODR2
#define U3_STATUS_INDICATOR   PC_ODR_ODR3
#define U4_STATUS_INDICATOR   PC_ODR_ODR4
#define REPAIR_CHECK          PB_IDR_IDR6  //维修按键输入检测

#define UO1_CHECK             PB_IDR_IDR6 //四输出状态监测
#define UO2_CHECK             PB_IDR_IDR5
#define UO3_CHECK             PE_IDR_IDR5
#define UO4_CHECK             PE_IDR_IDR6

#define U1_ON                 PE_ODR_ODR0 //四路开启继电器
#define U2_ON                 PD_ODR_ODR1
#define U3_ON                 PG_ODR_ODR3
#define U4_ON                 PE_ODR_ODR3

#define U1_OFF                PC_ODR_ODR5 //四路关闭继电器
#define U2_OFF                PC_ODR_ODR6
#define U3_OFF                PC_ODR_ODR7
#define U4_OFF                PG_ODR_ODR0

#define OVER_CURRENT_1        PB_IDR_IDR2
#define OVER_CURRENT_2        PB_IDR_IDR1
#define OVER_CURRENT_3        PB_IDR_IDR0
#define OVER_CURRENT_4        PE_IDR_IDR7

#define ENABLE_485TX          PD_ODR_ODR7 = 1
#define ENABLE_485RX          PD_ODR_ODR7 = 0


void Delay_Ms(u16 z);
void IWDG_Init(void);               // init wait dog
void All_Init(void);                // init MCU peripher
void UART1_SendByte(u8 ByteData);   //send a bytes
u8   EEPROM_ReadByte(u16 EEPROM_Add);
void EEPROM_WriteByte(u8 EEPROM_Data,u16 EEPROM_Add);
void SendFrame(u8 *data,u8 Length);
u16 ModBus_CRC16(uchar *puchMsg,uchar crc_count);



#endif
/*@*****************************end of file**************************************@*/


