#ifndef __OS_CPU_A_INC__
#define __OS_CPU_A_INC__
#include "vregs.inc" 

#if __CODE_MODEL__==__SMALL_CODE_MODEL__
#define  CALLX  CALL
#define  RETX   RET
#else   
#define  CALLX  CALLF
#define  RETX   RETF
#endif

SAVE_REGS  MACRO
#if __CODE_MODEL__==__SMALL_CODE_MODEL__
        push  __zero_in_ram__
#endif
        pushw y
        pushw x        
        push  a
        push  cc        
        
        push s:?b0
        push s:?b1

        push s:?b2
        push s:?b3

        push s:?b4
        push s:?b5
        
        push s:?b6
        push s:?b7       
        
        push s:?b8
        push s:?b9

        push s:?b10
        push s:?b11
        
        push s:?b12
        push s:?b13

        push s:?b14
        push s:?b15 
        
        ENDM
        
INT_SAVE_REGS  MACRO        
        push s:?b0
        push s:?b1

        push s:?b2
        push s:?b3

        push s:?b4
        push s:?b5
        
        push s:?b6
        push s:?b7       
        
        push s:?b8
        push s:?b9

        push s:?b10
        push s:?b11
        
        push s:?b12
        push s:?b13

        push s:?b14
        push s:?b15 
        
        ENDM        
        
        
RESTORE_REGS  MACRO     
        pop s:?b15
        pop s:?b14

        pop s:?b13
        pop s:?b12

        pop s:?b11
        pop s:?b10
        
        pop s:?b9
        pop s:?b8      
       
        pop s:?b7
        pop s:?b6

        pop s:?b5
        pop s:?b4
        
        pop s:?b3
        pop s:?b2

        pop s:?b1
        pop s:?b0
                
        pop  cc 
        pop  a
        popw x
        popw y
#if __CODE_MODEL__==__SMALL_CODE_MODEL__
        pop  __zero_in_ram__
#endif          
        ENDM  
        
INT_RESTORE_REGS  MACRO     
        pop s:?b15
        pop s:?b14

        pop s:?b13
        pop s:?b12

        pop s:?b11
        pop s:?b10
        
        pop s:?b9
        pop s:?b8      
       
        pop s:?b7
        pop s:?b6

        pop s:?b5
        pop s:?b4
        
        pop s:?b3
        pop s:?b2

        pop s:?b1
        pop s:?b0
                              
        ENDM  

SAVE_OLD_STK_PTR MACRO                        
        LDW    Y,L:OSTCBCur                         //Y=OSTCBCur
        LDW    X,SP                                 //X=SP
        LDW    (Y),X                                //OSTCBCur->OSTCBStkPtr=SP       
        ENDM
       
LOAD_NEW_STK_PTR MACRO
         LDW    Y,L:OSTCBHighRdy                 //Y=OSTCBHighRdy     
         LDW    Y,(Y)                               //Y= OSTCBHighRdy->OSTCBStkPtr
         LDW    SP, Y         
         ENDM



#endif