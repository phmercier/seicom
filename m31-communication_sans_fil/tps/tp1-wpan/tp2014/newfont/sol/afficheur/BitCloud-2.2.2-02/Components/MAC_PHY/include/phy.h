/**************************************************************************//**
  \file  
    phy.h
  \brief
    Types and constants declaration for IEEE std 802.15.4-2006
    PHY implementation.
  \internal
    Copyright (c)Meshnetics.
    History:     
     18/05/07 ALuzhetsky - Created.
******************************************************************************/

#ifndef _PHY_H
#define _PHY_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <inttypes.h>

/******************************************************************************
                    Define(s) section
******************************************************************************/
#define DBM_11 11
#define DBM_10 10
#define DBM_9 9
#define DBM_8 8
#define DBM_7 7
#define DBM_6 6
#define DBM_5 5
#define DBM_4 4
#define DBM_3 3
#define DBM_2 2
#define DBM_1 1
#define DBM_0 0
#define DBM_MIN_1 (-1)
#define DBM_MIN_2 (-2)
#define DBM_MIN_3 (-3)
#define DBM_MIN_4 (-4)
#define DBM_MIN_5 (-5)
#define DBM_MIN_6 (-6)
#define DBM_MIN_7 (-7)
#define DBM_MIN_8 (-8)
#define DBM_MIN_9 (-9)
#define DBM_MIN_10 (-10)
#define DBM_MIN_11 (-11)
#define DBM_MIN_12 (-12)
#define DBM_MIN_13 (-13)
#define DBM_MIN_14 (-14)
#define DBM_MIN_15 (-15)
#define DBM_MIN_16 (-16)
#define DBM_MIN_17 (-17)
#define DBM_MIN_18 (-18)
#define DBM_MIN_19 (-19)
#define DBM_MIN_20 (-20)
#define DBM_MIN_21 (-21)
#define DBM_MIN_22 (-22)
#define DBM_MIN_23 (-23)
#define DBM_MIN_24 (-24)
#define DBM_MIN_25 (-25)
#define DBM_MIN_26 (-26)
#define DBM_MIN_27 (-27)

#define CHANNEL_0   0
#define CHANNEL_1   1
#define CHANNEL_2   2
#define CHANNEL_3   3
#define CHANNEL_4   4
#define CHANNEL_5   5
#define CHANNEL_6   6
#define CHANNEL_7   7
#define CHANNEL_8   8
#define CHANNEL_9   9
#define CHANNEL_10  10
#define CHANNEL_11  11
#define CHANNEL_12  12
#define CHANNEL_13  13
#define CHANNEL_14  14
#define CHANNEL_15  15
#define CHANNEL_16  16
#define CHANNEL_17  17
#define CHANNEL_18  18
#define CHANNEL_19  19
#define CHANNEL_20  20
#define CHANNEL_21  21
#define CHANNEL_22  22
#define CHANNEL_23  23
#define CHANNEL_24  24
#define CHANNEL_25  25
#define CHANNEL_26  26

#define PHY_SYMBOL_DURATION_PAGE_0_CHANNELS_0     50 ///< Symbol duration for channel 0 and BPSK modulation.
#define PHY_SYMBOL_DURATION_PAGE_0_CHANNELS_1_10  25 ///< Symbol duration for channels [1 - 10] and BPSK modulation.
#define PHY_SYMBOL_DURATION_PAGE_0_CHANNELS_11_26 16 ///< Symbol duration for channels [11 - 26] and OQPSK modulation.
#define PHY_SYMBOL_DURATION_PAGE_1_CHANNELS_0     80 ///< Symbol duration for channel 0 and ASK modulation.
#define PHY_SYMBOL_DURATION_PAGE_1_CHANNELS_1_10  20 ///< Symbol duration for channels [1 - 10] and ASK modulation.
#define PHY_SYMBOL_DURATION_PAGE_2_CHANNELS_0     40 ///< Symbol duration for channel 0 and OQPSK modulation.
#define PHY_SYMBOL_DURATION_PAGE_2_CHANNELS_1_10  16 ///< Symbol duration for channels [1 - 10] and OQPSK modulation.

// PHY PIB attribute read only parameters.
#define PHY_SYMBOLS_PER_OCTET_PAGE_0_CHANNELS_0     8
#define PHY_SYMBOLS_PER_OCTET_PAGE_0_CHANNELS_0_10  8
#define PHY_SYMBOLS_PER_OCTET_PAGE_0_CHANNELS_11_26 2
//#define PHY_SYMBOLS_PER_OCTET_PAGE_1_CHANNELS_0    (2/5)
//#define PHY_SYMBOLS_PER_OCTET_PAGE_1_CHANNELS_1_10 (6/3.75)
#define PHY_SYMBOLS_PER_OCTET_PAGE_2_CHANNELS_0     2
#define PHY_SYMBOLS_PER_OCTET_PAGE_2_CHANNELS_0_10  2

// Size of frame fields
#define PHY_FRAME_LENGTH_FIELD_SIZE 1
#define PHY_FCS_FIELD_SIZE          2
#define PHY_SFD_FIELD_SIZE          1
#define PHY_PREAMBLE_FIELD_SIZE     4
#define PHY_LQI_FIELD_SIZE          1
#define PHY_RSSI_FIELD_SIZE         1

/******************************************************************************
                    Types section
******************************************************************************/
//! CCA mode types. IEEE 802.15.4-2006 6.9.9 Clear channel assessment (CCA).
typedef enum
{
  PHY_CCA_MODE_N = 0,
  PHY_CCA_MODE_1 = 1,
  PHY_CCA_MODE_2 = 2,
  PHY_CCA_MODE_3 = 3
} PHY_CcaMode_t;

//! Energy level type.
typedef uint8_t PHY_EnergyLevel_t;

//! Evailible channel pages.
enum
{
  CHANNEL_PAGE_0 = 0,
  CHANNEL_PAGE_1 = 1,
  CHANNEL_PAGE_2 = 2,
};

#endif /* _PHY_H */

// eof phy.h
