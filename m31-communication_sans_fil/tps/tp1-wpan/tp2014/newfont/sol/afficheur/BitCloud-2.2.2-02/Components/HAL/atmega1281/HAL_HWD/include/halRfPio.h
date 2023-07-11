/*********************************************************************************
  rfpins.h
  Copyright (c)Meshnetics.

  Description:
   AT86RF230 control pins declarations.
          
  History:
    29/05/07 A. Luzhetsky - Created
**********************************************************************************/

#ifndef RFPINS_H_
#define RFPINS_H_

#include <gpio.h>

// Macros for the RF_SLP_TR pin manipulation.
HAL_ASSIGN_PIN(RF_SLP_TR, B, 4);
// Macros for the RF_RST pin manipulation.
HAL_ASSIGN_PIN(RF_RST, A, 7);
// Macros for the RF_IRQ pin manipulation.
HAL_ASSIGN_PIN(RF_IRQ, E, 5);
// Macros for the SPI_CS pin manipulation.
HAL_ASSIGN_PIN(SPI_CS, B, 0);
// Macros for the SPI_SCK pin manipulation.
HAL_ASSIGN_PIN(SPI_SCK, B, 1);
// Macros for the SPI_MOSI pin manipulation.
HAL_ASSIGN_PIN(SPI_MOSI, B, 2);
// Macros for the SPI_MISO pin manipulation.
HAL_ASSIGN_PIN(SPI_MISO, B, 3);
#endif // RFPINS_H
