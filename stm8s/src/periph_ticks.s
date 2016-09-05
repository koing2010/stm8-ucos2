#include "os_cpu_a.inc"

        PUBLIC _interrupt_15

        EXTERN OSTaskSwHook
        EXTERN OSRunning
        EXTERN OSTCBHighRdy
        EXTERN OSTCBCur
        EXTERN OSPrioCur
        EXTERN OSPrioHighRdy
        EXTERN OSIntEnter
        EXTERN OSIntExit
        EXTERN OSTimeTick

        SECTION `.far_func.text`:CODE:NOROOT(0)
_interrupt_15:
         SIM
         BRES       0x5302, #0

         INT_SAVE_REGS

         SAVE_OLD_STK_PTR

         CALLX     OSIntEnter
         CALLX     OSTimeTick
         CALLX     OSIntExit

         INT_RESTORE_REGS

         IRET

         END