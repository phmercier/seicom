/*********************************************************************************
  halRfSpi.h
  Copyright (c)Meshnetics.

  Description:
    SPI interface routines header.
          
  History:
    29/05/07 A. Luzhetsky - Created
**********************************************************************************/

#ifndef HAL_RFSPI_H_
#define HAL_RFSPI_H_

#include <inttypes.h>
#include <types.h>
#include <avr/io.h>
#include <halRfPio.h>
#include <atomic.h>

/******************************************************************************
  Performs initialization of SPI interface.
******************************************************************************/
void HAL_InitRfSpi(void);

/******************************************************************************
  Writes/reads byte to/from SPI. 
  parameters: value - byte to write.
  Returns:    the byte which was read.
******************************************************************************/
uint8_t HAL_WriteByteRfSpi(uint8_t value);

/******************************************************************************
  Deselects a slave device.
******************************************************************************/
INLINE void HAL_DeselectRfSpi(void)
{
  GPIO_SPI_CS_set();
}

/******************************************************************************
  Selects a slave device.
******************************************************************************/
INLINE void HAL_SelectRfSpi(void)
{
  GPIO_SPI_CS_clr();
}

/******************************************************************************
  Inline function (to use in critical sections)
  Writes/reads byte to/from SPI. 
  parameters: value - byte to write.
  Returns:    the byte which was read.
******************************************************************************/
INLINE uint8_t HAL_WriteByteInlineRfSpi(uint8_t value)
{
  ATOMIC_SECTION_ENTER
    SPDR = value; // Write data.
    asm("nop");   // This "nop" tunes up the "while" to reduce time for SPIF flag 
                  // detecting.
    while (!(SPSR&(1 << SPIF)));
  ATOMIC_SECTION_LEAVE
  return SPDR;
}


#endif /* HAL_RFSPI_H_ */

//eof halRfSpi.h
