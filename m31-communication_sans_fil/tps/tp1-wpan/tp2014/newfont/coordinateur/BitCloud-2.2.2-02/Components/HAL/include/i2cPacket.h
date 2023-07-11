/******************************************************************************/
/** \file  i2cPacket.h  

\brief
    Declaration of the i2cPacket interface.

\internal
  Copyright (c)Meshnetics.
  History:
    5/12/07 A. Khromykh - Created
*******************************************************************************/

#ifndef _I2CPACKET_H
#define _I2CPACKET_H

/******************************************************************************
                   Includes section
******************************************************************************/
// \cond
#include <i2c.h>
// \endcond

/******************************************************************************
                   Types section
******************************************************************************/
/**************************************************************************//**
\brief i2c access control structure
******************************************************************************/
typedef struct
{
  /** \brief slave address */
  uint8_t id; 
  /** \brief number of bytes to be written to the bus */
  uint16_t length; 
  /** \brief pointer to the data (for avr iinternal address include to data field)*/
  uint8_t *data; 
  /** \brief internal device address size conditions (only for arm):  
                  HAL_NO_INTERNAL_ADRESS - byte command condition  \n
                  HAL_ONE_BYTE_SIZE       \n
                  HAL_TWO_BYTE_SIZE       \n
                  HAL_THREE_BYTE_SIZE */
  uint32_t lengthAddr;
  /** \brief internal device address (only for arm) */
  uint32_t internalAddr;
  /** \brief callback function */
  void (*f)(bool result);
} HAL_I2cParams_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Opens twi resource.\n
field of i2cMode structure \n
i2cClockRate_t clockrate (set by user). Must be chosen from:\n
  I2C_CLOCK_RATE_250 - 250 Kb/s clock rate \n
  I2C_CLOCK_RATE_125 - 125 Kb/s clock rate \n
  I2C_CLOCK_RATE_62   - 62.5 Kb/s clock rate \n
  
\param[in]
  i2cMode - pointer to the mode structure.

\return
  -1 - resource was already open or pointer is NULL. \n
   0 - success.   
******************************************************************************/
int HAL_OpenI2cPacket(HAL_i2cMode_t *i2cMode);

/**************************************************************************//**
\brief Closes resource. 

\return
  -1 - resource was not open. \n
   0 - success.
******************************************************************************/
int HAL_CloseI2cPacket(void);

/**************************************************************************//**
\brief Writes a series of bytes out to the TWI bus. 

\param[in]
  param - pointer to HAL_I2cParams_t structure
\return
   0 - the bus is free and the request is accepted. \n
  -1 - otherwise.  
******************************************************************************/
int HAL_WriteI2cPacket(HAL_I2cParams_t *param);

/**************************************************************************//**
\brief Reads the series of bytes from the TWI bus.

\param[in]
  param - pointer to HAL_I2cParams_t structure
\return
  0 - the bus is free and the request is accepted. \n
 -1 - otherwise.  
******************************************************************************/
int HAL_ReadI2cPacket(HAL_I2cParams_t *param);

#endif /* _I2CPACKET_H */
// eof i2cPacket.h
