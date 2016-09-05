/**********************************************************************************

File_name:       Model.c
Revised:        $Date:2014-7-  ; $
Editor:		    Mr.Kong

**********************************************************************************/


/*================================================================================
@ Include files
*/
#include "iostm8s207c8.h"
#include "includes.h"
/*================================================================================
@ Global variable
*/
extern OS_EVENT *MutexSlaver;
extern SYSTEM  systemInfo;
/*================================================================================
@ All functions  as follow
*/


/*********************************************************************************
Function:    TIM1_OVR_UIF_IRQHandler
Description:  TIM1_OVR_UIF_IRQHandler

Input:        None
Output:       None
Return:       None
Others:	      None
*********************************************************************************/
#pragma vector = TIM1_OVR_UIF_vector
__interrupt  void TIM1_OVR_UIF_IRQHandler(void)
{
  OSIntEnter();
  TIM1_SR1_UIF = 0;
  OSIntExit();
}
/*********************************************************************************
Function:     UART1_R_OR_IRQHandler
Description:  UART1 have received serial data.

Input:        None
Output:       None
Return:       None
Others:	      None
*********************************************************************************/

#pragma vector = UART1_R_OR_vector
__interrupt  void UART1_R_OR_IRQHandler(void)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
  OS_CPU_SR  cpu_sr;
#endif
   if(UART1_SR_RXNE == 1) //¶ÁÊý¾Ý¼Ä´æÆ÷·Ç¿Õ
   {
     systemInfo.UART1RxBuf[systemInfo.UART1RxCount] = UART1_DR;
     systemInfo.UART1RxCount ++;
     if(systemInfo.UART1RxCount >= 19)
     {
        OSSemPost(systemInfo.SemUART1);
     }
    }
}
/*********************************************************************************
Function:     UART1_R_OR_IRQHandler
Description:  UART1 have received serial data.

Input:        None
Output:       None
Return:       None
Others:	      None
*********************************************************************************/
#pragma vector = UART3_R_OR_vector
__interrupt  void UART3_R_OR_IRQHandler(void)
{
  #if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
  OS_CPU_SR  cpu_sr;
#endif
   if(UART3_SR_RXNE == 1) //¶ÁÊý¾Ý¼Ä´æÆ÷·Ç¿Õ
   {
      u8 data = UART3_DR;
//     systemInfo.UART1RxBuf[systemInfo.UART1RxCount] = UART3_DR;
//     systemInfo.UART1RxCount ++;
//     if(systemInfo.UART1RxCount >= 19)
//     {
//        OSSemPost(systemInfo.SemUART1);
//     }
    }

}

/*********************************************************************************
Function:    TIM4_IRQHandler
Description:  time4 overflow interrupt or updata interrupt.

Input:        None
Output:       None
Return:       None
Others:	      None
*********************************************************************************/
#pragma vector = TIM4_OVR_UIF_vector
__interrupt void TIM4_IRQHandler(void)
{
   //it interrupt once per 4ms.


OSIntEnter();
   TIM4_SR=0x00; // clear flag;
  OSIntExit();


}

/*********************************************************************************
Function:    CLK_SWITCH_IRQHandler
Description:  if system clk was forced to switch to HSI.

Input:        None
Output:       None
Return:       None
Others:	      None
*********************************************************************************/
#pragma vector = CLK_SWITCH_vector
__interrupt void CLK_SWITCH_IRQHandler(void)
{
  OSIntEnter();
   if(CLK_CSSR_CSSD == 1)
   {
     CLK_CSSR_CSSD = 0;
     CLK_CSSR_CSSDIE = 0;
     CLK_CKDIVR = 0x00;

   }

  OSIntExit();

}

/*@*****************************end of file*************************************@*/