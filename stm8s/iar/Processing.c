/**********************************************************************************

File_name:      Processing.c
Version:		    0.0
Revised:        $Date:2015-8-31 to   ; $
Description:    the main file of this project.
Notes:          This version targets the stm32
Editor:		      Mr.Kong

**********************************************************************************/

/*================================================================================
@ Include files
*/
#include "Processing.h"
#include "includes.h"

/*================================================================================
@ Global variable
*/
#define  SHORT_DELAY_TICKS  OS_TICKS_PER_SEC/100
extern SYSTEM  systemInfo;
/*================================================================================
@ All functions  as follow
*/
void ProcessingBus485Task( void * pdata )
{
  INT8U *err;
    while(1)
   {
       OSTimeDly(SHORT_DELAY_TICKS*3);
       U2_STATUS_INDICATOR = 1;
       OSTimeDly(SHORT_DELAY_TICKS*2);
       U2_STATUS_INDICATOR = 0;

       OSSemPend(systemInfo.SemFrameStart,0,err);
       if(err == OS_NO_ERR)
       {
//         OSSemPend(systemInfo.SemFrameEnd,3,err);
//         if(err == OS_NO_ERR)
//         {}
//         else if(OS_TIMEOUT)
//         {
//
//         }


       }else
       {

       }
   }

}


/*@*****************************end of file*************************************@*/