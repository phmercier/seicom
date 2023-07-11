/******************************************************************************
  nwkEDScan.h
  Copyright (c)Meshnetics.
  Description: 
    EDScan header file.
  History:
    14/06/07 S. Vladykin - Created.
******************************************************************************/
#ifndef _NWKEDSCAN_H
#define _NWKEDSCAN_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwk.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum _NwkEDScanState_t  // states 
{
  EDSCAN_IDLE_STATE,
  EDSCAN_WAIT_STATE,
  EDSCAN_CONFIRM_STATE,
} NwkEDScanState_t;

typedef struct _NwkEDScan_t
{
  struct {
  NwkEDScanState_t        state:8; // finite-state machine
  };
  NWK_EDScanReq_t*        req;   // request being processed    
  QueueDescriptor_t       queue; // additional fields
  MAC_ScanReq_t           scanReq;
} NwkEDScan_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
  standard request
******************************************************************************/
void NWK_EDScanReq(NWK_EDScanReq_t *req);

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetEDScan(void);

/******************************************************************************
  task handler
******************************************************************************/
void nwkEDScanTaskHandler(void);

#endif   // _NWKEDSCAN_H
//eof nwkEDScan
