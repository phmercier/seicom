/**************************************************************************//**
\file  battery.c
  Copyright (c)Meshnetics.

\brief
  Description:
    This module is used for measurment battery voltage.

\internal
  History:
    29/06/07 E. Ivanov - Created
******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <battery.h>
#include <adc.h>
#include <bspTaskManager.h>
#include <types.h>

/******************************************************************************
                   Types section
******************************************************************************/
// battery states
typedef enum
{
  IDLE,      // idle
  BUSY,      // opened and ready to be used
  DATA       // performs request
} batteryStates_t;

// battery descriptor
typedef struct
{
  uint8_t batteryData;
  void (* batteryCallback)(uint8_t data); // callback
} BatteryControl_t;

/******************************************************************************
                   Global variables section
******************************************************************************/
// Monitors current state
batteryStates_t batteryState = IDLE;
BatteryControl_t batteryControl;
HAL_AdcParams_t adcParam;

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Callabck about ADC request was completed.
\param[in]
  data - result of ADC.
******************************************************************************/
void batteryCalback(void)
{
  //batteryControl.batteryData = (4ul * batteryControl.batteryData * 125ul * 3ul) / (1024ul * 100ul);
  bspPostTask0(BSP_BATTERY);
}

/**************************************************************************//**
\brief Opens the component to use.
\return
    SUCCESS - the component is ready to been use. \n
    FAIL - otherwise.
******************************************************************************/
result_t openBattery(void)
{
  if (IDLE == batteryState)
  {
  	adcParam.bufferPointer = &(batteryControl.batteryData);
  	adcParam.callback = batteryCalback;
  	adcParam.resolution = RESOLUTION_8_BIT;
  	adcParam.sampleRate = ADC_4800SPS;
  	adcParam.selectionsAmount = 1;
    batteryState = BUSY;
    HAL_OpenAdc(&adcParam);
    return SUCCESS;
  }
  return FAIL;
}

/**************************************************************************//**
\brief  Closes component.
\return
    SUCCESS - always.
******************************************************************************/
result_t closeBattery(void)
{
  if (IDLE == batteryState)
    return FAIL;
  batteryState = IDLE;
  HAL_CloseAdc();
  return SUCCESS;
}

/**************************************************************************//**
\brief  Starts ADC request on battery channel.
\param[in]
    data - sensor data.
\return
    FAIL - battery component was not opened. \n
    SUCCESS - other case.
******************************************************************************/
result_t readBatteryData(void (*callback)(uint8_t data))
{
  if (BUSY != batteryState)
    return FAIL;
  batteryState = DATA;
  batteryControl.batteryCallback = callback;
  HAL_ReadAdc(HAL_ADC_CHANNEL0);
  return SUCCESS;
}

/**************************************************************************//**
\brief BSP battery handler.
******************************************************************************/
void bspBatteryHandler(void)
{
  batteryState = BUSY;
  batteryControl.batteryCallback(batteryControl.batteryData);
}

// eof battery.c
