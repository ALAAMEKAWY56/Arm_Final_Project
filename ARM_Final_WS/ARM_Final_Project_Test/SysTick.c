/**********************************************************************************************************
 * [FILE NAME]      :           SysTick.hc                                                                *
 * [DESCRIPTION]    :           Source file for the ARM Cortex M4 SysTick_driver                          *
 * [DATE CREATED]   :           JUL 27, 2024                                                              *
 * [AURTHOR]        :           Alaa Mekawi                                                               *
 *********************************************************************************************************/
/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "SysTick.h"
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/
/************************************************************************************
 * Service Name: SysTick_Init
 * Sync/Async: Synchronous
 * Reentrancy: non-reentrant
 * Parameters (in): Tick_Time - Time in miliseconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initialize the SysTick timer with the specified time in milliseconds
 *              using interrupts. This function is used to setup the timer to generate periodic
 *              interrupts every specified time in milliseconds.
 ************************************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds)
{
    uint32 Reload_Value ;

    /* Disable SysTick Timer at first */
    SYSTICK_CTRL_REG = 0;

    /* Calculate the reload value for the specified time in milliseconds */
    Reload_Value = (16000000 / 1000) * a_TimeInMilliSeconds;

    /*Set in Reload Register Reload Value to set Timer to Count desired time */
    SYSTICK_RELOAD_REG = Reload_Value - 1;

    /* Clear Counter By clearing Current register */
    SYSTICK_CURRENT_REG = 0;

    /* In STRCTRL choose CLK_SRC = 1 , Enable = 1 and INTEN  = 1 for interrupt Enable */
    SYSTICK_CTRL_REG |= 0x07;

}


/************************************************************************************
 * Service Name: SysTick_StartBusyWait
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): Tick_Time - Time in miliseconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initialize the SysTick timer with the specified time in milliseconds
 *              using polling or busy-wait technique. The function should exit when the time is
 *              elapsed and stops the timer at the end.
 ************************************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds)
{
    uint32 Reload_Value ;

    /* Disable SysTick Timer at first */
    SYSTICK_CTRL_REG = 0;

    /* Calculate the reload value for the specified time in milliseconds */
    Reload_Value = (16000000 / 1000) * a_TimeInMilliSeconds;

    /*Set in Reload Register Reload Value to set Timer to Count desired time */
    SYSTICK_RELOAD_REG = Reload_Value - 1;

    /* Clear Counter By clearing Current register */
    SYSTICK_CURRENT_REG = 0;

    /* In STRCTRL choose CLK_SRC = 1 , Enable = 1 and INTEN  = 0 for interrupt Disable */
    SYSTICK_CTRL_REG |= 0x05;

    /* wait until the COUNT flag = 1
       which mean SysTick Timer reaches ZERO value ...
       COUNT flag is cleared after read the CTRL register value */
    while(!(SYSTICK_CTRL_REG & (1<<SYSTICK_COUNT_FLAG)));

    /* Stop The Timer*/
    SysTick_Stop();
}


/************************************************************************************
 * Service Name: SysTick_Handler
 * Sync/Async: Asynchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Handler for SysTick interrupt use to call the call-back function.
 ************************************************************************************/
void SysTick_Handler(void)
{
    /* Check if the callback function pointer is not NULL */
    if(*g_callBackPtr != NULL_PTR)
    {
        /* Call the callback function*/
        (*g_callBackPtr)();
    }
}


/************************************************************************************
 * Service Name: SysTick_SetCallBack
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): pointer to Call Back function.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:  Function to setup the SysTick Timer call back to be executed in SysTick Handler.
 ************************************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void))
{
    /* Set the global callback function pointer to the provided function pointer */
    g_callBackPtr = Ptr2Func;
}


/************************************************************************************
 * Service Name: SysTick_Stop
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:  Function to setup the SysTick Timer call back to be executed in SysTick Handler.
 ************************************************************************************/
void SysTick_Stop(void)
{
    /* Disable SysTick Timer By Clearing the Enable Bit */
    SYSTICK_CTRL_REG &= ~STCTRL_ENABLE_BIT_MASK;
}


/************************************************************************************
 * Service Name: SysTick_Start
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:  Function to Start/Resume the SysTick timer.
 ************************************************************************************/
void SysTick_Start(void)
{
    /* Enable SysTick Timer By Setting the Enable Bit */
    SYSTICK_CTRL_REG |= STCTRL_ENABLE_BIT_MASK;
}


/************************************************************************************
 * Service Name: SysTick_DeInit
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:  Function to De-initialize the SysTick Timer.
 ************************************************************************************/
void SysTick_DeInit(void)
{
    /* Disable SysTick Timer Setting By Setting control register to Zero */
    SYSTICK_CTRL_REG = 0;
}
