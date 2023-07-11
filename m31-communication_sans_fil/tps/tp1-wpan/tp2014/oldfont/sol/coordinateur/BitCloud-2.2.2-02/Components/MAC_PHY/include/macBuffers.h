/**************************************************************************//**
  \file
  macBuffers.h
  \brief
    MAC and PHY buffers' description.
  \internal
    Copyright (c)Meshnetics.
    History:     
    09/10/07 A. Luzhetsky - Created.
******************************************************************************/

#ifndef _MACBUFFERS_H
#define _MACBUFFERS_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <inttypes.h>
#include <types.h>
#include <phy.h>
#include <macphyPib.h>

/******************************************************************************
                    Define(s) section
******************************************************************************/
//! Size of internal reception buffer.
#define FRAME_RX_BUFFER_SIZE (PHY_FRAME_LENGTH_FIELD_SIZE + \
                              PHY_MAX_PACKET_SIZE + \
                              PHY_LQI_FIELD_SIZE + \
                              PHY_RSSI_FIELD_SIZE)
                        
/******************************************************************************
                    Types section
******************************************************************************/
//! Single Rx frame buffer descriptor.
typedef struct
{
  //! Receive buffer busy flag.
  bool busy;
  //! Receive buffer.
  uint8_t data[FRAME_RX_BUFFER_SIZE];
}  FrameRxBuffer_t;

//! Description of the memory for frame reception.
typedef struct
{
  //! Pointer to the receive buffers.
  FrameRxBuffer_t (*buffer)[];
  //! Number of receive buffers.
  uint8_t amount;
}  FrameRxBufferDescr_t;

#endif // _MACBUFFERS_H

// eof macBuffers.h
