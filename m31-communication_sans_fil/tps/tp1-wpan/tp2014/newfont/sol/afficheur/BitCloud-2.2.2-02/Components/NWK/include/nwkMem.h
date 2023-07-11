/******************************************************************************
  nwkMem.h
  Copyright (c)Meshnetics.
  Description: 
    NWK Memory header file.
  History:
    14/06/07 S. Vladykin - Created.
******************************************************************************/
#ifndef _NWKMEM_H
#define _NWKMEM_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nib.h>
#include <nwkDiscovery.h>
#include <nwkFormation.h>
#include <nwkJoinReq.h>
#include <nwkJoinInd.h>
#include <neibTable.h>
#include <nwkDataInd.h>
#include <nwkDataReq.h>
#include <nwkReset.h>
#include <nwkStateMachine.h>
#include <nwkTaskManager.h>
#include <nwkStartRouter.h>
#include <nwkPermitJoining.h>
#include <nwkLeave.h>
#include <nwkBTT.h>
#include <nwkStatusInd.h>
#include <nwkLinkStatus.h>
#include <nwkSync.h>
#include <nwkRouteDiscovery.h>
#include <nwkStatusCommand.h>
#include <nwkReportCommand.h>
#include <nwkUpdateCommand.h>
#include <nwkRouteTable.h>
#include <nwkCmdRouteRecord.h>
#include <nwkAddrMap.h>
#include <nwkEDScan.h>
#include <nwkDbg.h>
#include <dbg.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef struct
{
  NIB_t                    nib;
  NwkDiscovery_t           discovery;
#if defined(_COORDINATOR_)
  NwkFormation_t           formation;
#endif
  NwkDataReq_t             dataReq;
  NwkDataInd_t             dataInd;
  NwkReset_t               reset;
  NwkTaskManager_t         taskManager;
  NwkStateMachine_t        stateMachine;
#if defined(_ROUTER_)
  NwkStartRouter_t         startRouter;
#endif
#if defined(_ROUTER_)||defined(_COORDINATOR_)
  NwkPermitJoining_t       permitJoining;
  NwkJoinInd_t             joinInd;
  NwkLinkStatus_t          linkStatus;
  NwkRouteDiscovery_t      routeDiscovery;
  NwkReportCommand_t       nwkReportCommand;
  NwkUpdateCommand_t       nwkUpdateCommand;
  NwkRouteRecord_t         routeRecord;
#endif
  NwkStatusCommand_t       nwkStatusCommand;
  NwkLeave_t               leave;
#if defined(_ROUTER_)||defined(_ENDDEVICE_)
  NwkJoinReq_t             joinReq;
#endif
  NwkBTT_t                 BTT;
#if defined(_ENDDEVICE_)
  NwkSync_t                sync;
#endif
  NwkFindRoute_t           findRoute;
  NwkRouteDiscoveryTable_t routeDiscoveryTable;
  NwkRouteTable_t          routeTable;
  NwkAddrMapTable_t        mapTable;
  NwkAge_t                 age;
  NwkEDScan_t              edScan;
} NwkMem_t;

extern NwkMem_t nwkMem;

/******************************************************************************
                   Inline functions section
******************************************************************************/
static inline NIB_t*                    nwkMemNib(void)
{return &nwkMem.nib;};

static inline NwkDiscovery_t*           nwkMemDiscovery(void)
{return &nwkMem.discovery;};

#if defined(_COORDINATOR_)
static inline NwkFormation_t*           nwkMemFormation(void)
{return &nwkMem.formation;};
#endif
static inline NwkDataReq_t*             nwkMemDataReq(void)
{return &nwkMem.dataReq;};

static inline NwkDataInd_t*             nwkMemDataInd(void)
{return &nwkMem.dataInd;};

static inline NwkReset_t*               nwkMemReset(void)
{return &nwkMem.reset;};

static inline NwkTaskManager_t*         nwkMemTaskManager(void)
{return &nwkMem.taskManager;};

static inline NwkStateMachine_t*        nwkMemStateMachine(void)
{return &nwkMem.stateMachine;};

#if defined(_ROUTER_)
static inline NwkStartRouter_t*         nwkMemStartRouter(void)
{return &nwkMem.startRouter;};
#endif

#if defined(_ROUTER_)||defined(_COORDINATOR_)
static inline NwkPermitJoining_t*       nwkMemPermitJoining(void)
{return &nwkMem.permitJoining;};
static inline NwkJoinInd_t*             nwkMemJoinInd(void)
{return &nwkMem.joinInd;};
static inline NwkLinkStatus_t*          nwkMemLinkStatus(void)
{return &nwkMem.linkStatus;};
static inline NwkRouteDiscovery_t*      nwkMemRouteDiscovery(void)
{return &nwkMem.routeDiscovery;};
static inline NwkReportCommand_t*       nwkMemReportCommand(void)
{return &nwkMem.nwkReportCommand;};
static inline NwkUpdateCommand_t*       nwkMemUpdateCommand(void)
{return &nwkMem.nwkUpdateCommand;};
static inline NwkRouteRecord_t*         nwkMemRouteRecord(void)
{return &nwkMem.routeRecord;};
#endif
static inline NwkStatusCommand_t*       nwkMemStatusCommand(void) 
{return &nwkMem.nwkStatusCommand;};

static inline NwkLeave_t*               nwkMemLeave(void)
{return &nwkMem.leave;};

#if defined(_ROUTER_)||defined(_ENDDEVICE_)
static inline NwkJoinReq_t*             nwkMemJoinReq(void)
{return &nwkMem.joinReq;};
#endif

static inline NwkBTT_t*                 nwkMemBTT(void)
{return &nwkMem.BTT;};

static inline NeibTable_t*              nwkMemNeibTable(void)
{return &nwkMem.nib.neibTable;};

#if defined(_ENDDEVICE_)
static inline NwkSync_t*                nwkMemSync(void)
{return &nwkMem.sync;};
#endif

static inline NwkFindRoute_t*           nwkMemFindRoute(void)
{return &nwkMem.findRoute;};

static inline NwkRouteDiscoveryTable_t* nwkMemRouteDiscoveryTable(void)
{return &nwkMem.routeDiscoveryTable;};

static inline NwkRouteTable_t*          nwkMemRouteTable(void)
{return &nwkMem.routeTable;};

static inline NwkAddrMapTable_t*        nwkMemMapTable(void)
{return &nwkMem.mapTable;};

static inline NwkAge_t*                 nwkMemAge(void)
{return &nwkMem.age;};

static inline NwkEDScan_t*              nwkMemEDScan(void)
{return &nwkMem.edScan;};

#endif // _NWKMEM_H
//eof nwkMem.h
