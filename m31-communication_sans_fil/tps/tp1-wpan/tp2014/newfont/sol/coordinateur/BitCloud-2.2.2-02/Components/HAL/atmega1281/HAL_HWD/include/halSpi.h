/*********************************************************************************
  halSpi.h
  Copyright (c)Meshnetics.

  Description:
    Declarations of USART SPI mode, hardware-dependent module.

  History:
    29/06/07 E. Ivanov - Created
**********************************************************************************/

#ifndef HAL_SPI_H_
#define HAL_SPI_H_
#include <avr/io.h>
#include <halClkCtrl.h>

#define UDORD0   2
#define UCPHA0   1
#define UCPOL0   0
// types of the clock mode
typedef enum
{
  // leading edge sample RX bit (rising), trailing edge setup TX bit (falling).
  SPI_CLOCK_MODE0 = ((0 << UCPOL0) | (0 << UCPHA0)),
  // leading edge setup TX bit (rising), trailing edge sample RX bit (falling).
  SPI_CLOCK_MODE1 = ((0 << UCPOL0) | (1 << UCPHA0)),
  // leading edge sample RX bit (falling), trailing edge setup TX bit (rising).
  SPI_CLOCK_MODE2 = ((1 << UCPOL0) | (0 << UCPHA0)),
  // leading edge setup TX bit (falling), trailing edge sample RX bit (rising).
  SPI_CLOCK_MODE3 = ((1 << UCPOL0) | (1 << UCPHA0))
} SpiClockMode_t;

// clock rate
typedef enum
{
  SPI_CLOCK_RATE_62 =  ((F_CPU / (2 * 62500ul)) - 1),
  SPI_CLOCK_RATE_125 =  ((F_CPU / (2 * 125000ul)) - 1),
  SPI_CLOCK_RATE_250 =  ((F_CPU / (2 * 250000ul)) - 1),
  SPI_CLOCK_RATE_500 =  ((F_CPU / (2 * 500000ul)) - 1),
  SPI_CLOCK_RATE_1000 = ((F_CPU / (2 * 1000000ul)) - 1),
  SPI_CLOCK_RATE_2000 = ((F_CPU / (2 * 2000000ul)) - 1)
} SpiBaudRate_t;

// Data order
typedef enum
{
  SPI_DATA_MSB_FIRST = 0 << UDORD0, // data with MSB first
  SPI_DATA_LSB_FIRST = 1 << UDORD0 // data with LSB first
} SpiDataOrder_t;

// SPI mode
typedef struct
{
  SpiClockMode_t clockMode; // SPI clock mode
  SpiDataOrder_t dataOrder; // SPI data order.
  SpiBaudRate_t baudRate; // SPI clock rate.
} HAL_SpiMode_t;

/******************************************************************************
Disables USART channel.
Parameters:
  none.
Returns:
  none.
******************************************************************************/
INLINE void halCloseSpi()
{
   UCSR0B = 0x00; // disable
}

/******************************************************************************
Set the parameters of USART to work at SPI mode.
Only USART0 can be used at this mode at the ZigBit platform.
Parameters:
  spiMode - pointer to HAL_SpiMode_t.
Returns:
  none.
******************************************************************************/
void halSetSpiConfig(HAL_SpiMode_t *spiMode);

/******************************************************************************
  Writes a length bytes to the SPI.
Parameters:
  buffer -  pointer to application data buffer;
  length -  number bytes for transfer;
Returns:
   number of written bytes
******************************************************************************/
uint8_t halSyncWriteData(uint8_t *buffer, uint8_t length);

/******************************************************************************
Enables data register empty interrupt.
Parameters:
  none
Returns:
  none.
******************************************************************************/
INLINE void halEnableSpiDremInterrupt()
{
  UCSR0B |= (1 << UDRIE0);
}

/******************************************************************************
Disables data register empty interrupt.
Parameters:
  none
Returns:
  none.
******************************************************************************/
INLINE void halDisableSpiDremInterrupt()
{
  UCSR0B &= ~(1 << UDRIE0);
}

/******************************************************************************
Enables transmit complete interrupt.
Parameters:
  none
Returns:
  none.
******************************************************************************/
INLINE void halEnableSpiTxcInterrupt()
{
  UCSR0B |=  (1 << TXCIE0);
}

/******************************************************************************
Disables transmit complete interrupt.
Parameters:
  none
Returns:
  none.
******************************************************************************/
INLINE void halDisableSpiTxcInterrupt()
{
  UCSR0B &=  ~(1 << TXCIE0);
}

/*****************************************************************************
Enables receive complete interrupt.
Parameters:
  none.
Returns:
  none.
******************************************************************************/
INLINE void halEnableSpiRxcInterrupt()
{
  UCSR0B |= (1 << RXCIE0);
}

/*****************************************************************************
Disables receive complete interrupt.
Parameters:
  none.
Returns:
  none.
******************************************************************************/
INLINE void halDisableSpiRxcInterrupt()
{
  UCSR0B &= ~(1 << RXCIE0);
}
#endif
//eof halSpi.h

