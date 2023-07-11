/****************************************************************************//*!
\file spi.h
  
\brief Declaration of USART SPI mode (for avr) and SPI1 bus (for arm), 
       hardware-independent module.

\internal
  Copyright (c)Meshnetics.
  History:
    29/05/08 A. Khromykh - Created
******************************************************************************/

#ifndef _SPI_H
#define _SPI_H

/******************************************************************************
                   Includes section
******************************************************************************/
#if defined(AT91SAM7X256)
  #include <halMemSpi.h>
#elif defined(ATMEGA1281) || defined(ATMEGA2561)
  #include <halSpi.h>
#endif  

/**************************************************************************//**
\brief Opens USART in MSPI mode(for avr) or opens SPI1(for arm). \n
fields of HAL_SpiMode_t structure: \n

SpiClockMode_t clockMode - spi clock mode (set by user). Must be chosen from: \n
           SPI_CLOCK_MODE0 \n 
           SPI_CLOCK_MODE1 \n 
           SPI_CLOCK_MODE2 \n 
           SPI_CLOCK_MODE3 \n
           
parameters valid only for avr:

SpiDataOrder_t dataOrder - spi data order (set by user). Must be chosen from: \n 
           SPI_DATA_MSB_FIRST \n 
           SPI_DATA_LSB_FIRST \n 
SpiBaudRate_t baudRate - spi clock rate (set by user). Must be chosen from: \n 
           SPI_CLOCK_RATE_62  \n 
           SPI_CLOCK_RATE_125 \n 
           SPI_CLOCK_RATE_250 \n 
           SPI_CLOCK_RATE_500 \n
  
parameters valid only for arm:
        
uint8_t csName - select CS signal (set by user). Must be set: \n
           CS2  \n 
uint32_t pack_parameterCs - list of time parameter. \n 
Must be use macros HAL_SPI_PACK_PARAMETER(freq_value, valid_delay_value, cons_delay_value). \n
Where is: \n
    freq_value - spi frequency (Hz) \n  
    valid_delay_value - delay between setting CS and clock start (sec) \n
    cons_delay_value - delay between consecutive transfers (sec) \n 
 
\param[in]
  spiMode - SPI parametrs (see above).
\param[in]
  callback - address of the function to notify the application 
             when a transmission was completed.
             When the synchronous method is used, callback must be NULL (only for avr). \n
\return
   -1 - there are no free resources. \n
    0 - SPI channel is ready.
******************************************************************************/
int HAL_OpenSpi(HAL_SpiMode_t *spiMode, void (*callback)());

/**************************************************************************//**
\brief Releases the channel and pins.
\return
  Returns 0 on success or -1 if channel was not opened.
******************************************************************************/
int HAL_CloseSpi(void);

/**************************************************************************//**
\brief Writes a number of bytes to the SPI.\n
 Callback function will be used to notify when the transmission is finished.\n
 The data read are placed to the buffer.
\param[in]
  buffer -  pointer to the application data buffer
\param[in]
  length -  number of bytes to transfer
\return
  -1 - spi module was not opened, or there is unsent data, or the pointer to 
   data or the length are NULL; \n
   0 - success; \n
   Number of written bytes - success (synchronous mode (only for avr)).
******************************************************************************/
int HAL_WriteSpi(uint8_t *buffer, uint8_t length);

#endif /* _SPI_H */
// eof spi.h
