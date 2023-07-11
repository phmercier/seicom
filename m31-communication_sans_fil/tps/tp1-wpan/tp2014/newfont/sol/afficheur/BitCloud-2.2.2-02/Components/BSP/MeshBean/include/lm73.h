/**************************************************************************//**
\file  lm73.h
  Copyright (c)Meshnetics.

\brief
  Description:
    Declarations of lm73 interface.

\internal          
  History:
    29/05/07 E. Ivanov - Created
*******************************************************************************/

#ifndef _LM73_SENSOR_H
#define _LM73_SENSOR_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Opens the component to use.

\return 
  SUCCESS - the component is ready to been use. \n
  FAIL - otherwise.
******************************************************************************/
result_t openLm73(void);

/**************************************************************************//**
\brief Performs the test if the component have completed request.

\return
    FAIL - the previous request is not completed.
    SUCCESS - otherwise.
******************************************************************************/
result_t closeLm73(void);

/**************************************************************************//**
\brief Reads data from lm73 sensor.
\param[in]
    f - callback method.
\param[in]
    result - the result of the requested operation.
             true - operation finished successfully, 
             false - some error has occured.
\param[in]
    data - sensor data.    
\return
  FAIL - the previous request was not completed,
         the address of callback is 0, i2c interface is busy,
         there is error on i2c interface.
  SUCCESS - other case.
******************************************************************************/
result_t readLm73Data(void (*f)(bool result, int16_t data));

#endif /* _LM73_SENSOR_H */
// eof lm73.h
