

#define  OS_CPU_GLOBALS
#include "includes.h"

INT8U __zero_in_ram__=0;

/********************************************************************************************************
  Local variables ¾Ö²¿±äÁ¿
********************************************************************************************************/
#if OS_TMR_EN > 0
    static INT16U OSTmrCtr;
#endif

#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
    void OSInitHookBegin (void)
    {
        #if OS_TMR_EN > 0
            OSTmrCtr = 0;
        #endif
    }
#endif


#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
    void OSInitHookEnd (void)
    {
    }
#endif


#if OS_CPU_HOOKS_EN > 0
    void OSTaskCreateHook (OS_TCB  *ptcb)
    {
        (void)ptcb;                                                     /*  Prevent compiler warning    */
                                                                        /*  ·ÀÖ¹±àÒë¾¯¸æ                */
    }
#endif


#if OS_CPU_HOOKS_EN > 0
    void  OSTaskDelHook (OS_TCB  *ptcb)
    {
        (void)ptcb;                                                     /*  Prevent compiler warning    */
                                                                        /*  ·ÀÖ¹±àÒë¾¯¸æ                */
    }
#endif


#if OS_CPU_HOOKS_EN > 0 && OS_VERSION >= 251
    void OSTaskIdleHook (void)
    {
    }
#endif


#if OS_CPU_HOOKS_EN > 0
    void OSTaskStatHook (void)
    {
    }
#endif



//                            ?b3:?b2:?b1             X           Y          ?b5:?b4
OS_STK  *OSTaskStkInit (void (*task)(void *pd), void *p_arg, OS_STK *ptos, INT16U opt)
{
    INT8U  *psoft_stk;
    INT32U  tmp;

    (void)opt;

    psoft_stk     = (INT8U *)ptos;

    tmp           = (INT32U)task;

    *psoft_stk--  = (INT8U)(tmp & 0xFF);       //PCL
    tmp         >>= 8;

    *psoft_stk--  = (INT8U)(tmp & 0xFF);       //PCH
    tmp         >>= 8;

    *psoft_stk--  = (INT8U)(tmp & 0xFF);       //PCE
    tmp         >>= 8;

    *psoft_stk--  = (INT8U)0x01;               //YL
    *psoft_stk--  = (INT8U)0x02;               //YH

    *psoft_stk--  = ((INT16U)p_arg)&0XFF;       //XL
    *psoft_stk--  = (((INT16U)p_arg)>>8)&0XFF;  //XH

    *psoft_stk--  = (INT8U)0x05;                //A
    *psoft_stk--  = (INT8U)0x20;                //CC

    *psoft_stk--  = (INT8U)0x00;                //?B0
    *psoft_stk--  = (INT8U)0x01;                //?B0
    *psoft_stk--  = (INT8U)0x02;                //?B0
    *psoft_stk--  = (INT8U)0x03;                //?B0
    *psoft_stk--  = (INT8U)0x04;                //?B0
    *psoft_stk--  = (INT8U)0x05;                //?B0
    *psoft_stk--  = (INT8U)0x06;                //?B0
    *psoft_stk--  = (INT8U)0x07;                //?B0

    *psoft_stk--  = (INT8U)0x08;                //?B0
    *psoft_stk--  = (INT8U)0x09;                //?B0
    *psoft_stk--  = (INT8U)0x0a;                //?B0
    *psoft_stk--  = (INT8U)0x0b;                //?B0
    *psoft_stk--  = (INT8U)0x0c;                //?B0
    *psoft_stk--  = (INT8U)0x0d;                //?B0
    *psoft_stk--  = (INT8U)0x0e;                //?B0
    *psoft_stk--  = (INT8U)0x0f;                //?B0

    return ((OS_STK *)psoft_stk);
}




void OSTaskSwHook (void)
{

}

#if (OS_CPU_HOOKS_EN > 0) && (OS_VERSION > 203)
    void OSTCBInitHook (OS_TCB  *ptcb)
    {
        (void)ptcb;                                                     /*  Prevent compiler warning    */
                                                                        /*  ·ÀÖ¹±àÒë¾¯¸æ                */
    }
#endif

#if ((OS_CPU_HOOKS_EN > 0) && (OS_TIME_TICK_HOOK_EN > 0)) || (OS_VERSION < 283)
    void OSTimeTickHook (void)
    {
        #if OS_TMR_EN > 0
            OSTmrCtr++;
            if (OSTmrCtr >= (OS_TICKS_PER_SEC / OS_TMR_CFG_TICKS_PER_SEC)) {
                OSTmrCtr = 0;
                OSTmrSignal();
	    }
        #endif
    }
#endif

