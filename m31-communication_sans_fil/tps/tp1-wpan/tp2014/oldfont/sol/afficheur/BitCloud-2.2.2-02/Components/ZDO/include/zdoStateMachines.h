/********************************************************************************
* The header file defines ZDO state machine variable, prototypes, etc			*/
// Copyright (c)Meshnetics.
#ifndef _ZDO_STATEMACHINE_H_
#define _ZDO_STATEMACHINE_H_

#include <nwk.h>
#include <aps.h>
#include <zdo.h>
#include <appTimer.h>

#define MAX_DISCOVERED_NETWORKS_NUMBER 3

/* event bit mask for ZDO */
typedef uint16_t ZdoEventMask_t;

/******************************************************************************
* Type Definitions
******************************************************************************/

/* Possible states which the ZDO state machine can stay for */
typedef enum
 {
  ZDO_INITIAL_STATE,
  ZDO_STARTUP_STATE,
  ZDO_SEARCHNETWORK_STATE,
  ZDO_CREATEPAN_STATE,
  ZDO_JOINING_STATE,
  ZDO_AUTHENTICATION_STATE,
  ZDO_START_DEVICE_STATE,
  ZDO_RUNNING_STATE,
  ZDO_REJOIN_STATE,
  ZDO_LEAVING_STATE,
  ZDO_ALARM_STATE,
  ZDO_RESETTING_STATE,
  ZDO_CONTINUE_STATE,
  ZDO_LEFT_STATE,
} ZdoStateMachineState_t;

/* ZDO to Aps & Nwk message Id */
typedef enum
{
  ZDO_APSME_SET_MSGID 			    = 0x70,
  ZDO_APSME_RESET_MSGID			    = 0x71,
  ZDO_APSME_START_MSGID		      = 0x72,
  ZDO_ZDP_START_MSGID           = 0x73,

  ZDO_NLME_SET_MSGID            = 0x50,
  ZDO_NLME_RESET_MSGID          = 0x51,
  ZDO_NLME_FORMATION_MSGID      = 0x52,
  ZDO_NLME_PERMITJOIN_MSGID     = 0x53,
  ZDO_NLME_ROUTEDISCOVERY_MSGID = 0x54,
  ZDO_NLME_LEAVE_MSGID          = 0x55,
  ZDO_NLME_DISCOVERY_MSGID      = 0x56,
  ZDO_NLME_JOIN_MSGID           = 0x57,
  ZDO_NLME_STARTROUTER_MSGID    = 0x58,
} ZdoToApsNwkMsgId_t;

/* Possible events for ZDO state machine task */

#define APP_ZDO_START_EVENT         ( 1<<0 )
#define	APP_ZDO_RESET_EVENT         ( 1<<1 )

#define NWK_SUCCESS_CONFIRM_EVENT   ( 1<<2 )
#define	NWK_INDICATION_EVENT        ( 1<<3 )

#define APS_SUCCESS_CONFIRM_EVENT   ( 1<<4 )
#define	APS_INDICATION_EVENT        ( 1<<5 )

#define NETWORK_FOUND_EVENT         ( 1<<6 )
#define ZDP_SUCCESS_CONFIRM_EVENT   ( 1<<6 )//FIXME: Is it ok???


#define RUNNING_START_EVENT         ( 1<<7 )

#define JOINED_EVENT                ( 1<<8 )
#define REJOIN_CMD_EVENT            ( 1<<9 )

#define STARTUP_PARAMS_PASSED_EVENT ( 1<<10 )

#define TIMER_OS_EXPIRED_EVENT      ( 1<<11 )
#define SECURITY_SUCCESS_EVENT      ( 1<<12 )

#define	STACK_RESET_EVENT           ( 1<<13 )

#define APS_FAIL_CONFIRM_EVENT      ( 1<<14 )
#define NWK_FAIL_CONFIRM_EVENT      ( 1<<15 )

/* STARTUP ATTRIBUTES SET                                           */

/* startUp control attribute */
typedef enum {
/* Indicates that the device should start "from scratch"
   and join the network using association.                          */
    SEARCH_NET       = 0,
/* Indicates that the device should rejoin the network with
   extended PAN ID given by the ExtendedPANId attribute.            */
    REJOIN_NET       = 1,    
} NetworkStartType_t;

/* criteria bit mask for Network Choose */
#define CHOOSENET_EXTPANID          ( 1<<0 )
#define CHOOSENET_STACKPROFILE      ( 1<<1 )
#define CHOOSENET_ZBVERSION         ( 1<<2 )
#define CHOOSENET_CT_EPID           ( 1<<7 )

/* 
 * State machine variables
 * */
typedef struct ZdoStateMachine_t_
{
  // states for State Machine
  ZdoStateMachineState_t  zdoState;
  // start network type: first start or rejoin
  NetworkStartType_t      networkStartType;  
  // event bits mask
  ZdoEventMask_t          stateMachineEvents;
#if defined(_ROUTER_) || defined(_ENDDEVICE_)  
  // network discovery variables 
  NWK_NetworkDescriptor_t networkList[MAX_DISCOVERED_NETWORKS_NUMBER];
  // selected network descriptor 
  NWK_NetworkDescriptor_t *networkDescriptor;
  // scanning parameters 
  uint8_t                 scanAttempt;
  //rejoining attempts counter
  uint8_t                 rejoinAttempt;
  // structure for timers 
  HAL_AppTimer_t          timerOS;
#endif  
  // aps or nwk message id 
  ZdoToApsNwkMsgId_t      stackMsgId;
  // ZDO_StartNetworkReq    ptr         
  ZDO_StartNetworkReq_t   *startNetworkReqParams;
  // ZDO_ResetNetworkReq    ptr         
  ZDO_ResetNetworkReq_t   *resetNetworkReqParams;
} ZdoStateMachine_t;

void zdoUpdateNetworkStatus(bool rejoinFlag);

#endif 			/*_ZDO_STATEMACHINE_H_*/
