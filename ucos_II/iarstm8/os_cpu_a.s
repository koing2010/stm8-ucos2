#include "os_cpu_a.inc"

        EXTERN OSTaskSwHook
        EXTERN OSRunning
        EXTERN OSTCBHighRdy
        EXTERN OSTCBCur
        EXTERN OSPrioCur
        EXTERN OSPrioHighRdy
        EXTERN OSIntEnter
        EXTERN OSIntExit
        EXTERN OSTimeTick

        PUBLIC __far_OSStartHighRdy
        PUBLIC __far_OSCtxSw
        PUBLIC __far_OSIntCtxSw

        PUBLIC __near_OSStartHighRdy
        PUBLIC __near_OSCtxSw
        PUBLIC __near_OSIntCtxSw

        EXTERN __zero_in_ram__


        SECTION `.far_func.text`:CODE:ROOT(0)
__far_OSStartHighRdy:
         CALLX	OSTaskSwHook	           //OSTaskSwHook()
	 MOV	L:OSRunning,#1	           //OSRunning=1

         LOAD_NEW_STK_PTR
         RESTORE_REGS
         RETX


        SECTION `.far_func.text`:CODE:ROOT(0)
__far_OSCtxSw:
	SAVE_REGS
        SAVE_OLD_STK_PTR

	CALLX	OSTaskSwHook		      //OSTaskSwHook()

        MOV     L:OSPrioCur,L:OSPrioHighRdy   //OSPrioCur=OSPrioHighRdy
        LDW     X, L:OSTCBHighRdy
        LDW     L:OSTCBCur, X               //OSTCBCur=OSTCBHighRdy

        LOAD_NEW_STK_PTR
        RESTORE_REGS
        RETX


        SECTION `.far_func.text`:CODE:ROOT(0)
__far_OSIntCtxSw:
	CALLX	  OSTaskSwHook			 //OSTaskSwHook()

        MOV    L:OSPrioCur,L:OSPrioHighRdy    //OSPrioCur=OSPrioHighRdy
        LDW    X, L:OSTCBHighRdy
        LDW    L:OSTCBCur, X                  //OSTCBCur=OSTCBHighRdy

        LOAD_NEW_STK_PTR
        INT_RESTORE_REGS

        IRET

        SECTION `.near_func.text`:CODE:ROOT(0)
__near_OSStartHighRdy:
         CALLX	OSTaskSwHook	                 //OSTaskSwHook()
	 MOV	L:OSRunning,#1	                 //OSRunning=1

         LOAD_NEW_STK_PTR
         RESTORE_REGS
         RETX


        SECTION `.near_func.text`:CODE:ROOT(0)
__near_OSCtxSw:
	SAVE_REGS
        SAVE_OLD_STK_PTR

	CALLX	OSTaskSwHook		          //OSTaskSwHook()

        MOV     L:OSPrioCur,L:OSPrioHighRdy       //OSPrioCur=OSPrioHighRdy
        LDW     X, L:OSTCBHighRdy
        LDW     L:OSTCBCur, X                     //OSTCBCur=OSTCBHighRdy

        LOAD_NEW_STK_PTR
        RESTORE_REGS
        RETX


        SECTION `.near_func.text`:CODE:ROOT(0)
__near_OSIntCtxSw:
	CALLX	OSTaskSwHook			   //OSTaskSwHook()

        MOV     L:OSPrioCur,L:OSPrioHighRdy      //OSPrioCur=OSPrioHighRdy
        LDW     X, L:OSTCBHighRdy
        LDW     L:OSTCBCur, X                    //OSTCBCur=OSTCBHighRdy

        LOAD_NEW_STK_PTR
        INT_RESTORE_REGS

        IRET

        END

