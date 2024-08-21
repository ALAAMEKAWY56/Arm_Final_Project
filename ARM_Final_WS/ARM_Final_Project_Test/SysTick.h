/**********************************************************************************************************
 * [FILE NAME]      :           SysTick.h                                                                 *
 * [DESCRIPTION]    :           Header file for the ARM Cortex M4 SysTick_driver                          *
 * [DATE CREATED]   :           JUL 27, 2024                                                              *
 * [AURTHOR]        :           Alaa Mekawi                                                               *
 *********************************************************************************************************/
#ifndef SYSTICK_H_
#define SYSTICK_H_
/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "tm4c123gh6pm_registers.h"
#include "std_types.h"
#include "NVIC.h"
/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/
#define STCTRL_ENABLE_BIT_MASK    0x00000001
#define SYSTICK_COUNT_FLAG        16
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/************************************************************************************
* Service Name: SysTick_Init
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): Tick_Time - Time in miliseconds
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initialize the SysTick timer with the specified time in milliseconds
*              using interrupts. This function is used to setup the timer to generate periodic
*              interrupts every specified time in milliseconds.
************************************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds);


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
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);


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
void SysTick_Handler(void);


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
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));


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
void SysTick_Stop(void);


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
void SysTick_Start(void);


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
void SysTick_DeInit(void);

#endif /* SYSTICK_H_ */
