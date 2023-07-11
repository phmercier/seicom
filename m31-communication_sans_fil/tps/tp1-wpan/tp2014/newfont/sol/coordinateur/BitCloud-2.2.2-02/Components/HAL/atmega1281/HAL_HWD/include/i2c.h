/*****************************************************************************//**
\file i2c,h 
  
\brief Declarations of i2c interface.
  
\internal  
  Copyright (c)Meshnetics.
  History:
    5/12/07 A. Khromykh - Created
**********************************************************************************/

#ifndef _I2C_H
#define _I2C_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <halClkCtrl.h>
#include <halTaskManager.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
/** \brief i2c bus prescaler */
#define HAL_I2C_PRESCALER 0ul

/** \brief TWI status codes. */ 
enum 
{
  TWS_BUSERROR      = 0x00,
  TWS_START         = 0x08,
  TWS_RSTART        = 0x10,
  TWS_MT_SLA_ACK    = 0x18,
  TWS_MT_SLA_NACK   = 0x20,
  TWS_MT_DATA_ACK   = 0x28,
  TWS_MT_DATA_NACK  = 0x30,
  TWS_M_ARB_LOST    = 0x38,
  TWS_MR_SLA_ACK    = 0x40,
  TWS_MR_SLA_NACK   = 0x48,
  TWS_MR_DATA_ACK   = 0x50,
  TWS_MR_DATA_NACK  = 0x58
};

/******************************************************************************
                   Types section
******************************************************************************/
/** \brief i2c baud rate */
typedef enum
{
  I2C_CLOCK_RATE_250 = ((F_CPU/250000ul) - 16ul)/(2ul * (1ul << HAL_I2C_PRESCALER) * (1ul << HAL_I2C_PRESCALER)), // 250 Kb/s clock rate
  I2C_CLOCK_RATE_125 = ((F_CPU/125000ul) - 16ul)/(2ul * (1ul << HAL_I2C_PRESCALER) * (1ul << HAL_I2C_PRESCALER)), // 125 Kb/s clock rate
  I2C_CLOCK_RATE_62  = ((F_CPU/62500ul) - 16ul)/(2ul * (1ul << HAL_I2C_PRESCALER) * (1ul << HAL_I2C_PRESCALER))// 62.5 Kb/s clock rate
} I2cClockRate_t;

/** \brief TWI clock rate */
typedef struct 
{
  I2cClockRate_t clockrate; // clock rate
} HAL_i2cMode_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Signals that error occured.
******************************************************************************/
void halI2cBusError(void);

/**************************************************************************//**
\brief Inits TWI module. Setup teh speed of TWI.
\param[in]
  i2cMode - the speed of TWI.
******************************************************************************/
void halInitI2c(const HAL_i2cMode_t*);

/**************************************************************************//**
\brief Notification about the stop condition was sent.
******************************************************************************/
void halSendEndDoneI2c(void);

/**************************************************************************//**
\brief Notification about the start condition was sent.
******************************************************************************/
void halSendStartDoneI2c(void);

/**************************************************************************//**
\brief Notification that byte was written to the TWI.
\param[in]
  result - contains result of previous operation.
******************************************************************************/
void halWriteDoneI2c(bool result);

/**************************************************************************//**
\brief Notification that byte was read from the TWI.
\param[in]
  data - contains byte that was read.
******************************************************************************/
void halReadDoneI2c(uint8_t data);

/******************************************************************************
                   Inline static functions section 
******************************************************************************/
/**************************************************************************//**
\brief Enables interrupt on TWI.
******************************************************************************/
INLINE void halInterruptEnableI2c(void)
{
  TWCR |= (1 << TWIE);
}

/**************************************************************************//**
\brief Disables interrupt on TWI.
******************************************************************************/
INLINE void halInterruptDisableI2c(void)
{
  TWCR &= (~(1 << TWIE));
}

/*************************************************************************//**
\brief Returns byte that was read from the TWI.
******************************************************************************/
INLINE uint8_t halReadByteI2c(void)
{
  return TWDR;
}

/*************************************************************************//**
\brief Resets the TWI.
******************************************************************************/
INLINE void halResetI2c(void)
{
  TWCR = ((1 << TWSTO) | (1 << TWINT));  // Reset TWI
}

/**************************************************************************//**
\brief Begins writing an byte to TWI.
\param[in]
  data - an byte for sending.
******************************************************************************/
INLINE void halWriteI2c(uint8_t data) 
{ 
  TWDR =  data;
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);
}

/**************************************************************************//**
\brief Begins read an byte from TWI.
\param[in]
  ack - defines the need to send ACK after an byte was recieved.
******************************************************************************/
INLINE void halReadI2c(bool ack) 
{
  if (ack) 
    TWCR |= (1 << TWEA);
  else
    TWCR &= ~(1 << TWEA);

  TWCR |= ((1 << TWINT) | (1 << TWIE) | (1 << TWEN));  // Trigger the TWI
}

/**************************************************************************//**
\brief Directs TWI to send stop condition.
******************************************************************************/
INLINE void halSendStopI2c(void) 
{
  TWCR = ((1 << TWSTO) | (1 << TWINT) | (1 << TWEN));
  halPostTask4(HAL_TWI);
}

/**************************************************************************//**
\brief Directs the TWI to send start condition.
******************************************************************************/
INLINE void halSendStartI2c(void) 
{
  TWCR = ((1 << TWSTA) | (1 <<TWINT) | (1 << TWEN) | (1 << TWIE));
}

#endif /* _I2C_H*/
// eof i2c.h
