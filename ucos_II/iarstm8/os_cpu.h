
/**--------------File Info-------------------------------------------------------------------------------
** File Name:               os_cpu.h
** Last modified Date:      2007.12.12
** Last Version:            1.0
** Description:             Header file of the ported code  移植代码头文件
**
**------------------------------------------------------------------------------------------------------
** Created By:              Mr.kon
** Created date:            2015.10
** Version:                 1.0
** Descriptions:            The original version 初始版本
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*********************************************************************************************************/

#ifndef  __OS_CPU_H
#define  __OS_CPU_H

#ifdef   OS_CPU_GLOBALS
#define  OS_CPU_EXT
#else
#define  OS_CPU_EXT  extern
#endif

/*********************************************************************************************************
  Date types(Compiler specific)  数据类型（和编译器相关）
*********************************************************************************************************/
typedef unsigned char   BOOLEAN;                                        /*  Boolean 布尔变量            */
typedef unsigned char   INT8U;                                          /*  Unsigned  8 bit quantity    */
typedef signed   char   INT8S;                                          /*  Signed    8 bit quantity    */
typedef unsigned short  INT16U;                                         /*  Unsigned 16 bit quantity    */
typedef signed   short  INT16S;                                         /*  Signed   16 bit quantity    */
typedef unsigned long    INT32U;                                         /*  Unsigned 32 bit quantity    */
typedef signed   long    INT32S;                                         /*  Signed   32 bit quantity    */
typedef float           FP32;                                           /*  Single precision floating
                                                                            point                       */
typedef double          FP64;                                           /*  Double precision floating
                                                                            point                       */

typedef unsigned char    OS_STK;                                         /*  Each stack entry is 8-bit
                                                                            wide  堆栈是32位宽度        */
typedef unsigned char    OS_CPU_SR;                                      /*  Define size of CPU status
                                                                            register (PSR = 32 bits)    */
typedef signed char	        int8;
typedef unsigned char		uint8;
typedef signed short		int16;
typedef unsigned short		uint16;
typedef	signed long		int32;
typedef unsigned long		uint32;


/*********************************************************************************************************
  Method of critical section management  临界区管理方法
*********************************************************************************************************/
#define  OS_CRITICAL_METHOD  3


/*********************************************************************************************************
  Other definitions  其他定义
*********************************************************************************************************/
#define  OS_STK_GROWTH        1
#define  OS_TASK_SW()         OSCtxSw()


/*********************************************************************************************************
  Prototypes(see OS_CPU_A.ASM)  原型声明（见OS_CPU_A.ASM）
*********************************************************************************************************/
#if OS_CRITICAL_METHOD == 4
    void OS_ENTER_CRITICAL(void);
    void OS_EXIT_CRITICAL(void);
#endif


#ifndef __always_inline__
#define __always_inline__  _Pragma("inline=forced") inline
#endif

typedef unsigned char critical_flag_t;

 __always_inline__  static  critical_flag_t CriticalEnter(void)
{
	critical_flag_t flags=__get_interrupt_state();
        __disable_interrupt();
        return flags;
}

__always_inline__  static void CriticalExit(critical_flag_t flags)
{
       __set_interrupt_state(flags);
}


 #if OS_CRITICAL_METHOD == 3
#define OS_ENTER_CRITICAL() cpu_sr=CriticalEnter()
#define OS_EXIT_CRITICAL()  CriticalExit(cpu_sr)
#endif



#if __CODE_MODEL__==__SMALL_CODE_MODEL__
void __near_OSCtxSw(void);
void __near_OSIntCtxSw(void);
void __near_OSStartHighRdy(void);
#define OSCtxSw          __near_OSCtxSw
#define OSIntCtxSw       __near_OSIntCtxSw
#define OSStartHighRdy   __near_OSStartHighRdy
#else
void __far_OSCtxSw(void);
void __far_OSIntCtxSw(void);
void __far_OSStartHighRdy(void);
#define OSCtxSw          __far_OSCtxSw
#define OSIntCtxSw       __far_OSIntCtxSw
#define OSStartHighRdy   __far_OSStartHighRdy
#endif


#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
