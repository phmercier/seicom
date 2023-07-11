/******************************************************************************
  nwkCommands.h
  Copyright (c)Meshnetics.
  Description: 
    nwk commands header file.
  History:
    20/06/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKCOMMANDS_H
#define _NWKCOMMANDS_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwk.h>
#include <nwkFrame.h>
#include <nwkDataInd.h>

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
  action when any command received
payload - cmd payload (with ID)
header  - nwk header
parse   - parsed header fields
******************************************************************************/
void nwkCommandInd(uint8_t *payload, NwkFrameHeader_t *header, NwkParseHeader_t *parse);

/******************************************************************************
  release command buffer, shall be called by command handler 
******************************************************************************/
void nwkCommandResp(NwkFrameHeader_t *header);

/******************************************************************************
  request to perform outgoing command
   (outgoing frame allocated in data indication buffer)
******************************************************************************/
void nwkCommandReq(NwkCommandReq_t *req);

#endif
//eof
