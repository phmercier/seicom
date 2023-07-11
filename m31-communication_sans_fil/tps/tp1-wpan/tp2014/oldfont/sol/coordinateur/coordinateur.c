/**
 *  Copyright (C) 2007-2008 plegal (plegal@appert44.org)
 *  @file         coordinateur.c
 *  @brief        TP ZigBee - SEICOM
 *  @version      0.01
 *  @date         13 nov 2008 12:43:31
 *  @author       P. Le Gal
 *
 *  Fabrication   avr-gcc
 *  @todo         Liste des choses restant a faire.
 *  @bug          Aucun pour l'instant
 *
 *  Modifications :
 *
 *  Date     Modifications
 *
 */


/*
* Includes BitCloud
*/

#include <configServer.h>                               // Config Server header
#include <appFramework.h>                               // Main stack types
#include <zdo.h>                                        // Main ZDO header
#include <aps.h>                                        // Main APS header
#include <appTimer.h>                                   // Application timer header
#include <atomic.h>

#include "gpio.h"
#include <stdio.h>

/*
 * Includes applications
 */
#include "printCom.h"
#include "version.h"

/*
 * Defines
 */

#define APP_MAX_DATA_SIZE                   APS_MAX_ASDU_SIZE

#define APP_ENDPOINT                        2           // Endpoint will be used
#define APP_PROFILE_ID                      1           // Profile Id will be used
#define APP_CLUSTER_ID                      1           // Cluster Id will be used

#define TIMER_100ms_INTERVAL 100

// Message types
#define REQ_HEURE  1


/*
 * Typedef
 */

// Application general state
typedef enum
{
    APP_INITIAL_STATE,                                    // Application initial state (after Power On or Reset)
    APP_NETWORK_JOINING_STATE,                            // Joining network state
    APP_NETWORK_JOINED_STATE,                             // Network available
    APP_ERROR_STATE                                       // Error state
} AppState_t;


// Coordinator state
typedef enum
{
    COORD_ACTIVE_IDLE_STATE,
    COORD_SENDING_MESSAGE_STATE
} AppDeviceState_t;

// Data transmission feature state
typedef enum
{
    APP_DATA_TRANSMISSION_IDLE_STATE,                     // Data transmission was finished or(and) not started yet
    APP_DATA_TRANSMISSION_BUSY_STATE                      // Data transmission in progress
} AppDataTransmissionState_t;


// Message from enddevice
typedef struct
{
    uint8_t requete;
    uint8_t param;
} PACK AppMessageIn_t;


// Message to enddevice
typedef struct
{
    uint8_t reponse;
    //char heure[9];
    uint32_t date;
} PACK AppMessageOut_t;



// General message structure
typedef struct                                          // Application message buffer
{
    uint8_t        header[APS_ASDU_OFFSET];               // Auxilliary header (stack required)
    AppMessageOut_t   message;                               // Actually application message
    uint8_t        footer[APS_AFFIX_LENGTH - APS_ASDU_OFFSET]; // Auxilliary footer (stack required)
} PACK AppMessageOutBuffer_t;


/*
 * Global variables
 */


// global initial state machine
static AppState_t   appState = APP_INITIAL_STATE;                     // Current application state
static AppDeviceState_t appCoordState = COORD_ACTIVE_IDLE_STATE;    // Current coord state
static AppDataTransmissionState_t appDataTtransmissionState = APP_DATA_TRANSMISSION_IDLE_STATE;

// Time out timer
static HAL_AppTimer_t timer100ms;
static uint8_t tmp = 30;


static AppMessageOutBuffer_t appMessageOutBuffer;


static uint8_t targetChild = 0;
static uint32_t     channelMask;
static uint8_t      numCanal = 0;
static uint8_t      numCoord = 0;
static char strBuf[35];


// Endpoint simple descriptor (ZDO endpoint descriptor)
static SimpleDescriptor_t        simpleDescriptor = {APP_ENDPOINT, APP_PROFILE_ID, 1, 1, 0, 0 , NULL, 0, NULL};
static APS_RegisterEndpointReq_t apsRegisterEndpointReq;    // APS Register Endpoint Request primitive (APS endpoint descriptor)

static APS_DataReq_t apsDataReq;                            // APS Data Request primitive (for application message sending)

// ZDO primitives
static ZDO_StartNetworkReq_t  zdoStartNetworkReq;           // Request parameters for network start

/*
 * Static functions
 */
static void timer100msFired(void);
static void initApp(void);
static void startNetwork(void);
static void APS_DataInd(APS_DataInd_t *ind);
static void APS_DataConf(APS_DataConf_t *conf);             // Data transmission confirmation handler
static void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t *confInfo);
static void coordTaskHandler(void);
static void sendMessageTargetChild();


/*******************************************************************************
 Description: Timer 100ms
 Parameters:
 Returns: none
*******************************************************************************/

static void timer100msFired()
{
    if ( tmp )
        tmp--;
    SYS_PostTask(APL_TASK_ID);
}

/********************************************************************
  Description:  application and stack parameters init
  Parameters:   none
  Returns:      none
********************************************************************/
static void initApp(void)
{
    uint16_t data = 0xFFFF;
    // Assign own MAC address
    uint64_t appUid_id = 0x5555;
    CS_WriteParameter(CS_UID_ID, &appUid_id);

    GPIO_0_make_out(); //led rouge
    GPIO_1_make_out(); //led verte
    GPIO_2_make_out(); //led jaune

    GPIO_0_set();
    GPIO_1_set();
    GPIO_2_set();

    channelMask = (0x01L << CANAL);
    CS_WriteParameter(CS_CHANNEL_MASK_ID,&channelMask);

    initUART();

#ifdef _DBG_
    printComMsg(FULLVERSION_STRING);
    printComMsg("Coordinator started");
#endif

    timer100ms.interval = TIMER_100ms_INTERVAL;     // Timer interval
    timer100ms.mode     = TIMER_REPEAT_MODE;        // Repeating mode (TIMER_REPEAT_MODE or TIMER_ONE_SHOT_MODE)
    timer100ms.callback = timer100msFired;          // Callback function for timer fire event
#ifdef _DBG_
    HAL_StartAppTimer(&timer100ms);                 // Start timer for debug message
#endif
}


/********************************************************************
  Description: Application task handler
  Parameters: none.
  Returns:    none
********************************************************************/
void APL_TaskHandler()
{
    switch (appState)
    {
        // node is in initial state
    case APP_INITIAL_STATE:                 // Initial (after RESET) state
        initApp();                            // Init application as a whole
        appState = APP_NETWORK_JOINING_STATE;
        SYS_PostTask(APL_TASK_ID);            // Application task posting
        break;
    case APP_NETWORK_JOINING_STATE:         // Network is in the joining stage
        GPIO_0_clr();
        GPIO_1_clr();
        GPIO_2_clr();
        startNetwork();                       // Start/joing network
        break;
    case APP_NETWORK_JOINED_STATE:          // Network was successfully started
        GPIO_0_set();
        coordTaskHandler();                  // Normal coord operation when one joined network
        break;

    default:
        break;
    }
}

/********************************************************************
  Description: Coordinator common task handler
  Parameters: none.
  Returns:    none
********************************************************************/

static void coordTaskHandler(void)
{
    uint8_t nb = 0;

    switch (appCoordState)                     // Actual device state when one joined network
    {
    case COORD_ACTIVE_IDLE_STATE:            // coordinator wait for child's message

        if (targetChild != 0)
        {
            appCoordState = COORD_SENDING_MESSAGE_STATE;
            SYS_PostTask(APL_TASK_ID);
        }
#ifdef _DBG_
        if ( 0 == tmp)
        {
            tmp=30;
            ZDO_GetNeibAmount_t neibAmount;
            ZDO_GetNeibAmount   (  &neibAmount    );
            printComMsgData("nb children :",neibAmount.childrenAmount);
            ZDO_GetChildrenAddr_t childrenAddr;
            NodeAddr_t childrenTable[16];
            childrenAddr.childrenTable = &childrenTable;
            ZDO_GetChildrenAddr(&childrenAddr);
            if (childrenAddr.childrenCount > 0)
            {
                for (nb=0; nb<childrenAddr.childrenCount;nb++)
                {
                    ZDO_GetLqiRssi_t lqiRssi;
                    lqiRssi.nodeAddr = childrenAddr.childrenTable[nb].shortAddr;
                    ZDO_GetLqiRssi(&lqiRssi);
                    sprintf(strBuf, "@%d - rssi:%d - lqi:%d",lqiRssi.nodeAddr,(int8_t)(lqiRssi.rssi),lqiRssi.lqi);
                    printComMsg(strBuf);
                }
            }
        }
#endif
        SYS_PostTask(APL_TASK_ID);
        break;

    case COORD_SENDING_MESSAGE_STATE :
        sendMessageTargetChild();
        break;

    default:
        break;
    }
}


/********************************************************************
  Description: start network
  Parameters: none.
  Returns:    none
********************************************************************/
static void startNetwork(void)
{
    // Network started confirm handler
    zdoStartNetworkReq.ZDO_StartNetworkConf = ZDO_StartNetworkConf;
    // start network
    ZDO_StartNetworkReq(&zdoStartNetworkReq);

}


/********************************************************************
  Description: ZDO_StartNetwork primitive confirmation was received.
  Parameters: confirmInfo - confirmation information
  Returns:    none
********************************************************************/
static void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t *confInfo)
{

    switch (confInfo->status)
    {
    case ZDO_SUCCESS_STATUS:
        appState = APP_NETWORK_JOINED_STATE;          // Application state switching
        appCoordState = COORD_ACTIVE_IDLE_STATE;
#ifdef _DBG_
        printComMsgData("Network started on channel :",confInfo->activeChannel);
#endif
        // Set application endpoint properties
        apsRegisterEndpointReq.simpleDescriptor = &simpleDescriptor;
        apsRegisterEndpointReq.APS_DataInd = APS_DataInd;
        // Register endpoint
        APS_RegisterEndpointReq(&apsRegisterEndpointReq);


        break;

    default:
#ifdef _DBG_
        printComMsgData("unhandled status :",confInfo->status);
#endif
        break;
    }
    SYS_PostTask(APL_TASK_ID);                      // Application task posting
}




/********************************************************************
  Description:  Application endpoint indication handler
  Parameters:   ind - APS Data Indication primitive
  Returns:      none
********************************************************************/


static void APS_DataInd(APS_DataInd_t* indData)
{
    if (APP_NETWORK_JOINED_STATE == appState)
    {
        GPIO_2_set();
        AppMessageIn_t *appMessageIn = (AppMessageIn_t *) indData->asdu;

#ifdef _DBG_
        sprintf(strBuf, "<~ @%d - req:%d - par:%d - rssi:%d",indData->srcAddress.shortAddress,appMessageIn->requete,appMessageIn->param,(int8_t)(indData->rssi));
        printComMsg(strBuf);
#endif

        // A COMPLETER

        if ((appMessageIn->requete == REQ_HEURE) && (targetChild == 0))
        {
            targetChild = indData->srcAddress.shortAddress;
        }
        else
        {
            targetChild = 0;
        }


        GPIO_2_clr();
    }
    SYS_PostTask(APL_TASK_ID);

}

/********************************************************************
  Description:
  Parameters:   none
  Returns:      none
********************************************************************/

static void sendMessageTargetChild()
{
    // A COMPLETER
    GPIO_2_clr();
    GPIO_1_set();
    appCoordState = COORD_ACTIVE_IDLE_STATE;
    if (APP_DATA_TRANSMISSION_IDLE_STATE == appDataTtransmissionState)
    {
        appDataTtransmissionState = APP_DATA_TRANSMISSION_BUSY_STATE;

#ifdef _DBG_
        sprintf(strBuf, "~> @%d",targetChild);
        printComMsg(strBuf);
#endif

        // A COMPLETER
        appMessageOutBuffer.message.reponse = REQ_HEURE;
        appMessageOutBuffer.message.date = HAL_GetSystemTime();

        apsDataReq.dstAddrMode             = APS_SHORT_ADDRESS;                           // Short addressing mode
        // A COMPLETER
        apsDataReq.dstAddress.shortAddress = targetChild;

        apsDataReq.dstEndpoint             = APP_ENDPOINT;                                // Destination endpoint
        apsDataReq.profileId               = simpleDescriptor.AppProfileId;               // Profile ID
        apsDataReq.clusterId               = APP_CLUSTER_ID;                              // Destination cluster ID
        apsDataReq.srcEndpoint             = APP_ENDPOINT;                                // Source endpoint
        apsDataReq.asduLength              = sizeof (AppMessageOut_t);                       // ASDU size

        apsDataReq.asdu             	   = (uint8_t *) &appMessageOutBuffer.message;      // ASDU pointer as an application message

        apsDataReq.txOptions.acknowledgedTransmission = 0;                                // Acknowledged transmission enabled
        apsDataReq.radius                  = 0;                                           // Default radius
        apsDataReq.APS_DataConf            = APS_DataConf;                                // Confirm handler

        APS_DataReq(&apsDataReq);
    }
}


/********************************************************************
  Description:  Data sent handler
  Parameters:   conf - APS Data Confirm primitive
  Returns:      none
********************************************************************/
static void APS_DataConf(APS_DataConf_t *conf)
{
    targetChild=0;
    appDataTtransmissionState = APP_DATA_TRANSMISSION_IDLE_STATE; // Data transmission entity is idle
    GPIO_1_clr();

    switch (conf->status)
    {
    case APS_SUCCESS_STATUS :

#ifdef _DBG_
        printComMsg("!~> OK");
#endif

        break;

    case NWK_ROUTE_ERROR_STATUS :
#ifdef _DBG_
        printComMsg("!~> nwk_route?");
#endif
        break;

    case MAC_TRANSACTION_EXPIRED_STATUS :
#ifdef _DBG_
        printComMsg("!~> mac...");
#endif
        break;

    case MAC_NO_ACK_STATUS :
#ifdef _DBG_
        printComMsg("!~> mac_no_ack");
#endif
        break;

    default: // provoque parfois le status inconnu 0xe9 (233)
#ifdef _DBG_
        printComMsgData("aps unhandled status",conf->status);
#endif
        break;
    }
    SYS_PostTask(APL_TASK_ID);
}


/********************************************************************
  Description: Network update notification

  Parameters: ZDO_MgmtNwkUpdateNotf_t *nwkParams - update notification

  Returns: nothing.
********************************************************************/
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *nwkParams)
{

    ZDO_StartNetworkConf_t conf;

    switch (nwkParams->status)
    {
    case ZDO_NETWORK_STARTED_STATUS :
#ifdef _DBG_
        printComMsg("Device has joined network");
#endif
        conf.status = ZDO_SUCCESS_STATUS;
        ZDO_StartNetworkConf(&conf);
        break;
    case ZDO_NETWORK_LEFT_STATUS:
        appState =  APP_NETWORK_JOINING_STATE;

        break;
    case ZDO_NETWORK_LOST_STATUS :
        appState = APP_NETWORK_JOINING_STATE;
#ifdef _DBG_
        printComMsgData("Device has lost parent :",nwkParams->childAddr.shortAddr);
#endif

        break;
    case ZDO_CHILD_JOINED_STATUS :
#ifdef _DBG_
        printComMsgData("!^ ",nwkParams->childAddr.shortAddr);
#endif
        //SYS_PostTask(APL_TASK_ID);
        break;
    case ZDO_CHILD_REMOVED_STATUS :
#ifdef _DBG_
        printComMsgData("!X ",nwkParams->childAddr.shortAddr);
#endif
        break;
    case ZDO_NWK_UPDATE_STATUS:
#ifdef _DBG_
        printComMsg("Network updated");
#endif
        break;
    default:
#ifdef _DBG_
        printComMsgData("Zdo unhandled status :",nwkParams->status);
#endif
        break;
    }
    SYS_PostTask(APL_TASK_ID);
}


/********************************************************************
  Description:
  Parameters:   none
  Returns:      none
********************************************************************/

void ZDO_WakeUpInd(void)
{
}

/********************************************************************
  Description:
  Parameters:   none
  Returns:      none
********************************************************************/
void ZDO_SleepInd(void)
{
}

/********************************************************************
  Description:
  Parameters:   none
  Returns:      none
********************************************************************/
void BSP_TaskHandler(void)
{
}


