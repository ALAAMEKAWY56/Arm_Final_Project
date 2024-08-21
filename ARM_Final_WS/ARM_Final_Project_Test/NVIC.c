/**********************************************************************************************************
 * [FILE NAME]      :           NVIC.c                                                                    *
 * [DESCRIPTION]    :           Source file for the ARM Cortex M4 NVIC_driver                             *
 * [DATE CREATED]   :           JUL 27, 2024                                                              *
 * [AURTHOR]        :           Alaa Mekawi                                                               *
 *********************************************************************************************************/
/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "NVIC.h"
/* Array of pointers to NVIC priority registers*/
static volatile uint32 *NVIC_PRIx_REG[NVIC_PRI_REG_COUNT] = {
                                    &NVIC_PRI0_REG,
                                    &NVIC_PRI1_REG,
                                    &NVIC_PRI2_REG,
                                    &NVIC_PRI3_REG,
                                    &NVIC_PRI4_REG,
                                    &NVIC_PRI5_REG,
                                    &NVIC_PRI6_REG,
                                    &NVIC_PRI7_REG,
                                    &NVIC_PRI8_REG,
                                    &NVIC_PRI9_REG,
                                    &NVIC_PRI10_REG,
                                    &NVIC_PRI11_REG,
                                    &NVIC_PRI12_REG,
                                    &NVIC_PRI13_REG,
                                    &NVIC_PRI14_REG,
                                    &NVIC_PRI15_REG,
                                    &NVIC_PRI16_REG,
                                    &NVIC_PRI17_REG,
                                    &NVIC_PRI18_REG,
                                    &NVIC_PRI19_REG,
                                    &NVIC_PRI20_REG,
                                    &NVIC_PRI21_REG,
                                    &NVIC_PRI22_REG,
                                    &NVIC_PRI23_REG,
                                    &NVIC_PRI24_REG,
                                    &NVIC_PRI25_REG,
                                    &NVIC_PRI26_REG,
                                    &NVIC_PRI27_REG,
                                    &NVIC_PRI28_REG,
                                    &NVIC_PRI29_REG,
                                    &NVIC_PRI30_REG,
                                    &NVIC_PRI31_REG,
                                    &NVIC_PRI32_REG,
                                    &NVIC_PRI33_REG,
                                    &NVIC_PRI34_REG,
};
/*******************************************************************************
 *                      Functions Definitions - IRQ'S Functions                *
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
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    /* Check If IRQ_Num is within valid Range */
#if (IRQ_Num < 0 || IRQ_Num > 138)
#error Invalid IRQ_Num!
#endif


    /* Calculate the Register and The Bit u want to Set*/
    uint8 Enable_Register_Number = IRQ_Num / 32;
    uint8 Bit_Number = IRQ_Num % 32;

    /* Set the corresponding bit in the ENx register To Enable Interrupt Request*/
    switch(Enable_Register_Number)
    {
    case 0:
        NVIC_EN0_REG |= (1<<Bit_Number);
        break;
    case 1:
        NVIC_EN1_REG |= (1<<Bit_Number);
        break;
    case 2:
        NVIC_EN2_REG |= (1<<Bit_Number);
        break;
    case 3:
        NVIC_EN3_REG |= (1<<Bit_Number);
        break;
    case 4:
        NVIC_EN4_REG |= (1<<Bit_Number);
        break;
    }

}

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
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    /* Check If IRQ_Num is within valid Range */
#if (IRQ_Num < 0 || IRQ_Num > 138)
#error Invalid IRQ_Num!
#endif


    /* Calculate the Register and The Bit u want to Set*/
    uint8 Disable_Register_Number = IRQ_Num / 32;
    uint8 Bit_Number = IRQ_Num % 32;

    /* Set the corresponding bit in the ENx register To Enable Interrupt Request*/
    switch(Disable_Register_Number)
    {
    case 0:
        NVIC_DIS0_REG  |= (1<<Bit_Number);
        break;
    case 1:
        NVIC_DIS1_REG  |= (1<<Bit_Number);
        break;
    case 2:
        NVIC_DIS2_REG  |= (1<<Bit_Number);
        break;
    case 3:
        NVIC_DIS3_REG  |= (1<<Bit_Number);
        break;
    case 4:
        NVIC_DIS4_REG  |= (1<<Bit_Number);
        break;
    }

}

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
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority)
{
    /* Check If IRQ_Num and IRQ_Priority is within valid Range */
#if (IRQ_Num < 0 || IRQ_Num > 138)
#error Invalid IRQ_Num!
#endif
#if (IRQ_Priority < 0 || IRQ_Priority > 7)
#error Invalid IRQ_Priority!
#endif

    /* Calculate the Register Number and The First Bit Number of the Three Priority Bits*/
    uint8 Priority_Register_Number = IRQ_Num / 4;
    uint8 Priority_Bit_Position =   (IRQ_Num % 4) * 8 + 5;

    /* Clear The three Bits First before insert by shifting the value 7 "0b00000111" to the Priority_Bit_Position*/
    *(NVIC_PRIx_REG[Priority_Register_Number]) &= ~(7 << Priority_Bit_Position);

    /*Then Insert The Priority*/
    *(NVIC_PRIx_REG[Priority_Register_Number]) |= (IRQ_Priority << Priority_Bit_Position);
}

/*******************************************************************************
 *                      Functions Definitions - Exceptions Functions           *
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
void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
#if (Exception_Num > 9)
#error Invalid NVIC_ExceptionType value!
#endif

    switch (Exception_Num) {

    /* Enable memory fault exception */
    case EXCEPTION_MEM_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK;
        break;

        /* Enable Bus fault exception */
    case EXCEPTION_BUS_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK;
        break;

        /* Enable Usage fault exception */
    case EXCEPTION_USAGE_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK;
        break;

    }
}

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
void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
#if (Exception_Num > 9)
#error Invalid NVIC_ExceptionType value!
#endif

    switch (Exception_Num) {

        /* Disable memory fault exception */
    case EXCEPTION_MEM_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL &= ~MEM_FAULT_ENABLE_MASK;
        break;

        /* Disable Bus fault exception */
    case EXCEPTION_BUS_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL &= ~BUS_FAULT_ENABLE_MASK;
        break;

        /* Disable Usage fault exception */
    case EXCEPTION_USAGE_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL &= ~USAGE_FAULT_ENABLE_MASK;
        break;

    }
}

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
                               Exception_Num, NVIC_ExceptionPriorityType Exception_Priority)
{
#if (Exception_Num < 0 || Exception_Num > 9)
#error Invalid NVIC_ExceptionType value!
#endif
#if (Exception_Priority < 0 || Exception_Priority > 7)
#error Invalid  Exception_Priority!
#endif

    switch (Exception_Num) {

    /* Set the priority value For Memory fault exception */
    case EXCEPTION_MEM_FAULT_TYPE:
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & MEM_FAULT_PRIORITY_MASK) | (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS);
        break;

        /* Set the priority value For Bus fault exception */
    case EXCEPTION_BUS_FAULT_TYPE:
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG &  BUS_FAULT_PRIORITY_MASK ) | (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
        break;

        /* Set the priority value For Usage fault exception */
    case EXCEPTION_USAGE_FAULT_TYPE:
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG &  USAGE_FAULT_PRIORITY_MASK ) | (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
        break;

        /* Set the priority value For SVC exception */
    case EXCEPTION_SVC_TYPE:
        NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & SVC_PRIORITY_MASK) | (Exception_Priority << SVC_PRIORITY_BITS_POS);
        break;

        /* Set the priority value For Debug Monitor exception */
    case EXCEPTION_DEBUG_MONITOR_TYPE:
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & DEBUG_MONITOR_PRIORITY_MASK) | (Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
        break;

        /* Set the priority value Pend_SV exception */
    case EXCEPTION_PEND_SV_TYPE:
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG  &  PENDSV_PRIORITY_MASK) | (Exception_Priority << PENDSV_PRIORITY_BITS_POS);
        break;

        /* Set the priority value SysTick exception */
    case EXCEPTION_SYSTICK_TYPE:
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (Exception_Priority << SYSTICK_PRIORITY_BITS_POS);
        break;

    }
}

