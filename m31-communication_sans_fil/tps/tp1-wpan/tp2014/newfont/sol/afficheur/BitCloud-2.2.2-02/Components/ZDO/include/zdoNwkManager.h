/************************************************************************
  ZdoNwkManager.h
  Copyright (c)Meshnetics.

  History:
    07/06/07 I. Kalganova - Modified
**************************************************************************/

#ifndef _ZDONWKMANAGER_H_
#define _ZDONWKMANAGER_H_

#include <macAddr.h>
#include <nwk.h>
#include <zdo.h>
#include <zdoTaskManager.h>
#include <aps.h>

typedef struct ZdoNwkManager_t_
{
  uint8_t               statusIndCounter;
  ZDO_ZdpReq_t          zdpDataReq;     
  MAC_SetReq_t          macSetReq; 
  ZDO_SetTxPowerReq_t   *txPowerReq;  
#ifdef _SECURITY_     
  APS_UpdateDeviceReq_t apsUpdateDeviceReq;
#endif //_SECURITY_   
  uint16_t              totalTransactions;
  uint16_t              failTransactions;
  uint8_t               badLink;
} ZdoNwkManager_t;

bool zdoCheckState(ZDO_TaskID_t zdoComponentId);
void zdoNwkManagerReset(void);
void zdoSendDeviceAnnce(void);

extern void NWK_JoinInd(NWK_JoinInd_t *);
extern void NWK_LeaveInd(NWK_LeaveInd_t *);
extern void NWK_StatusInd(NWK_NwkStatusInd_t *);

#endif //_ZDONWKMANAGER_H_
