/**********************************************************************************

File_name:      CollectEnergy.c
Version:		    1.0
Revised:        $Date:2015-10-27 to   ; $
Description:    the main file of this project.
Notes:          This version targets the stm32
Editor:		      Mr.Kong

**********************************************************************************/

/*================================================================================
@ Include files
*/
#include "objectDef.h"
#include "CollectEnergy.h"
#include "includes.h"
#include "init_peripher.h"
/*================================================================================
@ Global variable
*/

/*================================================================================
@ All functions  as follow
*/
extern OS_EVENT *MutexSlaver;
extern SLAVERS slavers[4];
extern SYSTEM  systemInfo;

const u8 slaver[4][5] =
{
  {0x83, 0x03, 0x01, 0x41, 0x18},
  {0x84, 0x03, 0x01, 0xF0, 0xD9},
  {0x85, 0x03, 0x01, 0xA1, 0x19},
  {0x86, 0x03, 0x01, 0x51, 0x19}

};

void SendUART1Frame(const u8 *pBuf)
{
  u8 i = 5;
  for(;i>0;i--)
  {
    UART1_SendByte(*pBuf);
    pBuf++;
  }
}
/*********************************************************************************
Function:     EnergyCollectTask
Description:  .
Input:        None
Output:       None
Return:       don't care.
Others:
*********************************************************************************/
void EnergyCollectTask(void * pdata)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
  OS_CPU_SR  cpu_sr;
#endif
  INT8U* err;
  OSTimeDly(200);
  while(1)
  {
    u8  i = 0;
    for(;i<4;i++)
    {

      //      if(slavers[i].salverStorage.hasMeter == TRUE)
      //      {
      systemInfo.UART1TxAddress = slaver[i][0];
      OS_ENTER_CRITICAL();
      systemInfo.UART1RxCount = 0;
      OS_EXIT_CRITICAL();
      SendUART1Frame(&slaver[i][0]);

      U3_STATUS_INDICATOR =  1;
      OSSemPend(systemInfo.SemUART1,100ul,err);



      if(*err == OS_NO_ERR)
      {
        OS_ENTER_CRITICAL();
        u16 CRCData =ModBus_CRC16(systemInfo.UART1RxBuf, 17);
        if(CRCData == (systemInfo.UART1RxBuf[17] | systemInfo.UART1RxBuf[18]<<8))
        {
          OS_EXIT_CRITICAL();
          OSMutexPend(MutexSlaver,0,err);
          OS_ENTER_CRITICAL();
          slavers[i].energyMeter.voltage     = systemInfo.UART1RxBuf[4] | systemInfo.UART1RxBuf[3] << 8;
          slavers[i].energyMeter.current     = systemInfo.UART1RxBuf[6] | systemInfo.UART1RxBuf[5] << 8;
          slavers[i].energyMeter.power       = systemInfo.UART1RxBuf[8] | systemInfo.UART1RxBuf[7] << 8;
          slavers[i].energyMeter.totalEnergy = systemInfo.UART1RxBuf[9] << 24 | systemInfo.UART1RxBuf[10] << 16 \
            |systemInfo.UART1RxBuf[11] << 8 | systemInfo.UART1RxBuf[12];

          slavers[i].energyMeter.factor      = systemInfo.UART1RxBuf[13];
          slavers[i].energyMeter.frequency   = systemInfo.UART1RxBuf[15] | systemInfo.UART1RxBuf[14] << 8;


          slavers[i].energyMeter.energyErr = 0;//clear erro flag.
           OS_EXIT_CRITICAL();
          U3_STATUS_INDICATOR =  0 ;
          OSMutexPost(MutexSlaver);
        }else
        {
        OS_EXIT_CRITICAL();
        }

      }
      else
      {
        OSMutexPend(MutexSlaver,0,err);
        if(slavers[i].energyMeter.energyErr < 4)
        {
          slavers[i].energyMeter.energyErr ++;
        }
        OSMutexPost(MutexSlaver);
      }
      OSTimeDly(150);//delay 1.5secound

    }
    // }

  }
}





/*@*****************************end of file*************************************@*/