/**********************************************************************************************************
 * [FILE NAME]      :           NVIC.h                                                                    *
 * [DESCRIPTION]    :           Header file for the ARM Cortex M4 NVIC_driver                             *
 * [DATE CREATED]   :           JUL 27, 2024                                                              *
 * [AURTHOR]        :           Alaa Mekawi                                                               *
 *********************************************************************************************************/
#ifndef NVIC_H_
#define NVIC_H_
/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "std_types.h"
#include "tm4c123gh6pm_registers.h"
/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/
#define NVIC_PRI_REG_COUNT 35

#define MEM_FAULT_PRIORITY_MASK              0x000000E0
#define MEM_FAULT_PRIORITY_BITS_POS          5

#define BUS_FAULT_PRIORITY_MASK              0x0000E000
#define BUS_FAULT_PRIORITY_BITS_POS          13

#define USAGE_FAULT_PRIORITY_MASK            0x00E00000
#define USAGE_FAULT_PRIORITY_BITS_POS        21

#define SVC_PRIORITY_MASK                    0xE0000000
#define SVC_PRIORITY_BITS_POS                29

#define DEBUG_MONITOR_PRIORITY_MASK          0x000000E0
#define DEBUG_MONITOR_PRIORITY_BITS_POS      5

#define PENDSV_PRIORITY_MASK                 0x00E00000
#define PENDSV_PRIORITY_BITS_POS             21

#define SYSTICK_PRIORITY_MASK                0xE0000000
#define SYSTICK_PRIORITY_BITS_POS            29

#define MEM_FAULT_ENABLE_MASK                0x00010000
#define BUS_FAULT_ENABLE_MASK                0x00020000
#define USAGE_FAULT_ENABLE_MASK              0x00040000
#define PENDSV_PEND_BIT_MASK                 0x10000000
#define PENDSV_UNPEND_BIT_MASK               0x08000000

/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm(" CPSID F ")

/*******************************************************************************
 *                           Data Types Declarations                           *
 *******************************************************************************/
typedef uint8 NVIC_IRQType;

typedef uint8 NVIC_IRQPriorityType;

typedef enum
{
    EXCEPTION_RESET_TYPE,
    EXCEPTION_NMI_TYPE,
    EXCEPTION_HARD_FAULT_TYPE,
    EXCEPTION_MEM_FAULT_TYPE,
    EXCEPTION_BUS_FAULT_TYPE,
    EXCEPTION_USAGE_FAULT_TYPE,
    EXCEPTION_SVC_TYPE,
    EXCEPTION_DEBUG_MONITOR_TYPE,
    EXCEPTION_PEND_SV_TYPE,
    EXCEPTION_SYSTICK_TYPE
}NVIC_ExceptionType;

typedef uint8 NVIC_ExceptionPriorityType;

/*******************************************************************************
 *                      Functions Prototypes - IRQ'S Functions                 *
 *******************************************************************************/
/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num);

/*********************************************************************
 * Service Name: NVIC_DisableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Disable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num);

/*********************************************************************
 * Service Name: NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 *                , IRQ_Priority - Priority of the IRQ
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Disable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority);


/*******************************************************************************
 *                      Functions Prototypes - Exceptions Functions            *
 *******************************************************************************/

/*********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the Exception from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:  Function to enable specific ARM system or fault exceptions.
**********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num);

/*********************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the Exception from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:  Function to Disable specific ARM system or fault exceptions.
**********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num);

/*********************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the Exception from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:  Function to set the priority value for specific ARM system or fault exceptions.
**********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType
                               Exception_Num, NVIC_ExceptionPriorityType Exception_Priority);
/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/

#endif /* NVIC_H_ */
