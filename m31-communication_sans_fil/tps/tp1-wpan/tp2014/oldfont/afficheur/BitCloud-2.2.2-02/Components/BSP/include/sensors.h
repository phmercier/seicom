/**************************************************************************//**
\file  sensors.h

\brief
    Declarations of sensor types and sensors interface.

\internal
  Copyright (c)Meshnetics.
  History:
    29/05/07 E. Ivanov - Created
*******************************************************************************/

#ifndef _SENSORS_H
#define _SENSORS_H

/******************************************************************************
                   Includes section
******************************************************************************/
// \cond
#include <types.h>
// \endcond

/******************************************************************************
                   Define(s) section
******************************************************************************/
// \cond
#define SENSOR_LIGHT       1
#define SENSOR_TEMPERATURE 2
#define SENSOR_BATTERY     3
#define SENSOR_LED         4
// \endcond

/******************************************************************************
                   Prototypes section
******************************************************************************/
/***************************************************************************//**
\brief Opens temperature sensor.
\return
  FAIL - sensor has been already open. \n
  SUCCESS - otherwise.
*******************************************************************************/
result_t BSP_OpenTemperatureSensor(void);

/***************************************************************************//**
\brief Closes the temperature sensor.
\return
  FAIL - if a hardware error has occured or
         there is uncompleted ReadData request. \n
  SUCCESS - otherwise.
*******************************************************************************/
result_t BSP_CloseTemperatureSensor(void);

/**************************************************************************//**
\brief Reads data from the temperature sensor.
\param[in]
    f - callback.
    result - the result of the requested operation.
             true - operation finished successfully, false - some error has
             occured.
    data - sensor data.
\return
    FAIL - previous request was not completed. \n
    SUCCESS - otherwise.
******************************************************************************/
result_t BSP_ReadTemperatureData(void (*f)(bool result, int16_t data));

/***************************************************************************//**
\brief Opens the light sensor.
\return
  FAIL - sensor has been already open. \n
  SUCCESS - otherwise.
*******************************************************************************/
result_t BSP_OpenLightSensor(void);

/***************************************************************************//**
\brief Closes the light sensor.
\return
  FAIL - if a hardware error has occured or
         there is uncompleted ReadData request. \n
  SUCCESS  - otherwise.
*******************************************************************************/
result_t BSP_CloseLightSensor(void);

/**************************************************************************//**
\brief Reads data from the light sensor.
\param[in]
    f - callback.
    result - the result of the requested operation.
             true - operation finished successfully, false - some error has
             occured.
    data - sensor data.
\return
    FAIL - previous request was not completed. \n
    SUCCESS - otherwise.
******************************************************************************/
result_t BSP_ReadLightData(void (*f)(bool result, int16_t data));

/***************************************************************************//**
\brief Opens the battery sensor.
\return
  FAIL - sensor has been already open. \n
  SUCCESS - otherwise.
*******************************************************************************/
result_t BSP_OpenBatterySensor(void);

/***************************************************************************//**
\brief Closes the battery sensor.
\return
  FAIL - sensor was not opened. \n
  SUCCESS  - otherwise.
*******************************************************************************/
result_t BSP_CloseBatterySensor(void);

/**************************************************************************//**
\brief Reads data from battery sensor.
\param[in]
    callback - callback function.
    data - sensor data.
    Can use (4ul * data * 125ul * 3ul) / (1024ul * 100ul) formula to count \n
    battery data in Volts (for avr).
\return
    FAIL - previous request was not completed, or sensor was not opened. \n
    SUCCESS - otherwise.
******************************************************************************/
result_t BSP_ReadBatteryData(void (*callback)(uint8_t data));

#endif/* _SENSORS_H */
// eof sensors.h

