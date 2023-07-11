/******************************************************************************
  nwkStatusInd.h
  Copyright (c)Meshnetics.
  Description: 
    header file.
  History:
    14/06/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKSTATUSIND_H
#define _NWKSTATUSIND_H

/******************************************************************************
                        Includes section
******************************************************************************/
#include <types.h>
#include <nwk.h>

/******************************************************************************
                        Prototypes section
******************************************************************************/

/******************************************************************************
  standard indication
******************************************************************************/
void NWK_NwkStatusInd(NWK_NwkStatusInd_t *ind);

void nwkStatusIndicate(ShortAddr_t shortAddress,NWK_StatusIndErrorCodes_t status);
void nwkStatusLinkFailure(ShortAddr_t dstAddress, ShortAddr_t srcAddress);
void nwkStatusLinkSuccess(ShortAddr_t dstAddress, ShortAddr_t srcAddress);
void nwkStatusNoRouteAvailable(ShortAddr_t dstAddress, ShortAddr_t srcAddress);

#endif  //_NWKSTATUSIND_H

//eof nwkStatusInd.h
