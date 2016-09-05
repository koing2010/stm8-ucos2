#include "includes.h"


extern OS_EVENT *MutexSlaver;
extern SLAVERS  slavers[4];
extern SYSTEM   systemInfo;


#define  LONG_DELAY_TICKS   OS_TICKS_PER_SEC/10


#define  OS_TASK_PROCESSING_STK_SIZE                            50
#define  OS_TASK_1_STK_SIZE                                     50
#define  OS_TASK_ENERGY_STK_SIZE                                100

#define  OS_TASK_PROCESSING_PRIO                    4
#define  OS_TASK_1_PRIO                             5
#define  OS_TASK_ENERGY_PRIO                        6

OS_STK	TaskProcessingStack[OS_TASK_PROCESSING_STK_SIZE];
OS_STK	Task1Stack[OS_TASK_1_STK_SIZE];
OS_STK	TaskEnergyStack[OS_TASK_ENERGY_STK_SIZE];

OS_EVENT *Sem_0=NULL;
OS_EVENT *Sem_1=NULL;
//OS_EVENT *SemUART1  = NULL;
//OS_EVENT *SemSlaver = NULL;


void task1(void * pdata )
{
  INT8U err;
  while(1)
  {
    OSTimeDly(LONG_DELAY_TICKS);
    //U1_STATUS_INDICATOR  = 1;
    OSTimeDly(LONG_DELAY_TICKS);
    //U1_STATUS_INDICATOR  = 0;

  }
}

int main()
{
  INT8U err;
  __disable_interrupt();


  All_Init();
  OSInit();

  Sem_0 = OSSemCreate (0);
  Sem_1 = OSSemCreate (0);
  systemInfo.SemUART1 = OSSemCreate (0);
  systemInfo.SemFrameEnd = OSSemCreate (0);
  systemInfo.SemFrameStart = OSSemCreate (0);
  MutexSlaver = OSMutexCreate(1, &err);

  OSTaskCreate( ProcessingBus485Task, (void *)OS_TASK_PROCESSING_STK_SIZE,\
    &TaskProcessingStack[OS_TASK_PROCESSING_STK_SIZE-1], OS_TASK_PROCESSING_PRIO );
  OSTaskCreate( task1, (void *)OS_TASK_1_STK_SIZE, &Task1Stack[OS_TASK_1_STK_SIZE-1], OS_TASK_1_PRIO );

  OSTaskCreate( EnergyCollectTask, (void *)OS_TASK_ENERGY_STK_SIZE,\
    &TaskEnergyStack[OS_TASK_ENERGY_STK_SIZE-1], OS_TASK_ENERGY_PRIO );



  __enable_interrupt();
  OSStart();
  return	0;
}

