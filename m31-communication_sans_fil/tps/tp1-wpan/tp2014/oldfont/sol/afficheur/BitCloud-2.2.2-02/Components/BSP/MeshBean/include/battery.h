/**************************************************************************//**
\file  battery.h
  Copyright (c)Meshnetics.

\brief
  Description:
    Interface to the battery sensor.

\internal
  History:
    29/06/07 E. Ivanov - Created
******************************************************************************/

#ifndef _BATTERY_H
#define _BATTERY_H

/******************************************************************************
                   Includes section
******************************************************************************/
// \cond
#include <types.h>
// \endcond

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief  Opens the component to use.
\return
    SUCCESS - the component is ready to been use. \n
    FAIL - otherwise.
******************************************************************************/
result_t openBattery(void);

/**************************************************************************//**
\brief  Closes component.
\return
    SUCCESS - always.
******************************************************************************/
result_t closeBattery(void);

/**************************************************************************//**
\brief  Starts ADC request on battery channel.
\param[in]
    callback - callback method.
\param[in]
    data - battery data.
    Can use (4ul * data * 125ul * 3ul) / (1024ul * 100ul) formula to count \n
    battery data in Volts.
\return
    FAIL - battery component was not opened.
    SUCCESS - other case.
******************************************************************************/
result_t readBatteryData(void (*callback)(uint8_t data));

#endif /* _BATTERY_H */
// eof battery.h

