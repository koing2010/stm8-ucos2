/**********************************************************************************

File_name:      objectDef.c
Version:		    0.0
Revised:        $Date:2015-10-28 to   ; $
Description:    the main file of this project.
Notes:          This version targets the stm32
Editor:		      Mr.Kong

**********************************************************************************/

/*================================================================================
@ Include files
*/
#include "objectDef.h"
/*================================================================================
@ Global variable
*/

OS_EVENT *MutexSlaver;
SLAVERS   slavers[4];
SYSTEM    systemInfo;
