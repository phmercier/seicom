/**************************************************************************//**
\file  lm73.c
  Copyright (c)Meshnetics.

\brief 
  Description:
    This module provides access to lm73 the sensor.
    Continues conversion released only.

\internal          
  History:
    29/05/07 E. Ivanov - Created
******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <lm73.h>
#include <i2cPacket.h>
#include <bspTaskManager.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
// device address on i2c bus
#define LM73_DEVICE_ADDRESS  (0x92 >> 1)

// device registers internal address
#define LM73_DATA_REGISTER 0x00
#define LM73_CONFIGURATION_REGISTER 0x01
#define LM73_UPPER_LIMIT_REGISTER 0x02
#define LM73_LOWER_LIMIT_REGISTER 0x03
#define LM73_CONTROL_STATUS_REGISTER 0x04
#define LM73_IDENTIFICATION_REGISTER 0x07

/******************************************************************************
                   Types section
******************************************************************************/
// states 
typedef enum
{
  IDLE,      // idle
  DATA       // performs request
} Lm73States_t;

typedef struct
{
  int32_t lm73Data;                               // Contains the result of sampling
  bool lm73Result;                                // Result of operation. true - there are no errors, false - in other case.
  void(* lm73Callback)(bool error, int16_t data); // callback
} Lm73Control_t;

/******************************************************************************
                   Global variables section
******************************************************************************/
Lm73States_t lm73State = IDLE; // Monitors current state
Lm73Control_t lm73Control;
HAL_I2cParams_t i2cParam;

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief  Opens the component to use.

\return 
    SUCCESS - the component is ready to been use. \n
    FAIL - otherwise.
******************************************************************************/
result_t openLm73(void)
{
  if (IDLE == lm73State) 
    return SUCCESS;

  return FAIL;
}

/**************************************************************************//**
\brief  Performs the test if the component have completed request.

\return
    FAIL - the previous request is not completed.  \n
    SUCCESS - otherwise.
******************************************************************************/
result_t closeLm73(void)
{
  if (IDLE == lm73State) 
    return SUCCESS;

  return FAIL;
}  

/**************************************************************************//**
\brief  The notice on that the packet has been read.

\param[in] 
  result - the result of operation
******************************************************************************/
void lm73I2cPacketReadDone(bool result)
{
  int32_t i;
  
  lm73Control.lm73Result = result; // stores the result of operation
  if (false == lm73Control.lm73Result)
  { // there were some errors on the i2c interface
    lm73Control.lm73Data = 0;
    bspPostTask0(BSP_TEMPERATURE);
    return;
  }

  if (DATA == lm73State)
  {
    i = (uint8_t)lm73Control.lm73Data; 
    i <<= 8;
    i |= ((lm73Control.lm73Data >> 8) & 0x00FF);
    lm73Control.lm73Data = (i * 3125l) / (4l * 100000l);
    bspPostTask0(BSP_TEMPERATURE);
  }
}
 
/**************************************************************************//**
\brief  Reads data from lm73 sensor.

\param[in]
    f - callback method.
\param[in]
    result - the result of the requested operation.
             true - operation finished successfully, false - some error has 
             occured.
\param[in]
    data - sensor data.

\return
    FAIL - the previous request was not completed,
           the address of callback is 0, i2c interface is busy,
	       there is error on i2c interface. \n
    SUCCESS - other case.
******************************************************************************/
result_t readLm73Data(void (*f)(bool result, int16_t data))
{
  HAL_i2cMode_t i2cMode;
   
  if (IDLE != lm73State) 
    return FAIL;
      
  if (!f) 
    return FAIL;
    
  i2cMode.clockrate = I2C_CLOCK_RATE_62;
  if (-1 == HAL_OpenI2cPacket(&i2cMode)) 
    return FAIL;
  lm73State = DATA;
  lm73Control.lm73Callback = f;
  
  i2cParam.data = (uint8_t*)(&lm73Control.lm73Data);
  i2cParam.f = lm73I2cPacketReadDone;
  i2cParam.id = LM73_DEVICE_ADDRESS;  
  i2cParam.length = 2;
  
  if (-1 == HAL_ReadI2cPacket(&i2cParam)) 
  {
    lm73State = IDLE;
    HAL_CloseI2cPacket();
    return FAIL;
  }
  
  return SUCCESS;
}

/**************************************************************************//**
\brief BSP task handler.
******************************************************************************/
void bspLM73Handler(void)
{
  HAL_CloseI2cPacket(); // free
  lm73State = IDLE; 
  lm73Control.lm73Callback(lm73Control.lm73Result, lm73Control.lm73Data);
}

// eof lm73.c
