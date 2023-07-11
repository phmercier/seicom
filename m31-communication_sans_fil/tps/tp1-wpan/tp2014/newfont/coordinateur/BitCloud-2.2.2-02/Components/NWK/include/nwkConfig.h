/******************************************************************************
  nwkConfig.h
  Copyright (c)Meshnetics.
  Description: 
    constant definition header file.
  History:
    20/06/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKCONFIG_H
#define _NWKCONFIG_H

/******************************************************************************
                        Definitions section
******************************************************************************/

//define for coordinator address
#define NWKC_COORD_ADDR                         0

//max broadcast jitter, mask to &, msec
#define NWKC_MAX_BROADCAST_JITTER_MASK          0x3F

#define NWKC_PROTOCOL_ID                        0

//sec
#define NWKC_INITIAL_LINK_STATUS_PERIOD         15

//max package transmission time * this const
#define NWKC_BROADCAST_DELIVERY_PACKAGES        400

#define NWK_MAX_CHANNEL 26


#define NWK_MAX_LINK_STATUS_FAILURES            3
#define NWK_END_DEVICE_MAX_FAILURES             3
#define NWK_BTT_SIZE                            20

#define NWK_DATA_RETRANSMISSION_AMOUNT          3
#define NWK_FAILURES_TO_REMOVE_FROM_ROUTE_TABE  1
#define NWK_ROUTE_DISCOVERY_ITEM_TTL            600

#define NWKC_NO_ROUTE_CACHE                     true
#define NWKC_CONCENTRATOR_TIME                  0
#define NWKC_ROUTE_RECORD_ITEM_SIZE             5
#define NWKC_ROUTE_RECORD_TABLE_SIZE            3

#endif //_NWKCONFIG_H
//eof nwkConfig.h
