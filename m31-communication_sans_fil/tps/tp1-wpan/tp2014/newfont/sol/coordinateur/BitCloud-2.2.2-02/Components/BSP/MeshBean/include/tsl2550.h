/**************************************************************************//**
\file  tsl2550.h
  Copyright (c)Meshnetics.

\brief
  Description:
    Declarations of tsl2550 interface.

\internal          
  History:
    29/06/07 E. Ivanov - Created
*******************************************************************************/

#ifndef _TSL2550_SENSOR_H
#define _TSL2550_SENSOR_H

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
\brief Opens the component to use.
\return 
  SUCCESS - the component is ready to been use. \n
  FAIL - otherwise.
******************************************************************************/
result_t openTsl2550(void);

/**************************************************************************//**
\brief Performs the test if the component have uncompleted request.
\return
    FAIL - the previous request is not completed. \n
    SUCCES - otherwise.
******************************************************************************/
result_t closeTsl2550(void);

/**************************************************************************//**
\brief Reads data from tsl2550 sensor.
\param[in]
    result - the result of the requested operation.
             true - operation finished successfully, false - some error has 
             occured.
\param[in]
    data - sensor data.
\return
  FAIL - the previous request was not completed,  \n
         the address of callback is 0, i2c interface is busy, \n
         there is error on i2c interface. \n
  SUCCESS - other case.
******************************************************************************/
result_t readTsl2550Data(void (*f)(bool result, int16_t data));

#endif /* _TSL2550_SENSOR_H */
// eof tsl2550.h
