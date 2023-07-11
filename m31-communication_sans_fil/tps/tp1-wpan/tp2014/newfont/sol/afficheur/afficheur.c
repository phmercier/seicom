/**
 *  Copyright (C) 2008-2009 plegal (plegal@appert44.org)
 *  @file         afficheur.c
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

#include "appTimer.h"
#include "zdo.h"
#include "gpio.h"
#include "aps.h"
#include <stdio.h>

/*
 * Includes applications
 */
#include "lcd.h"
#include "globaldef.h"
#include "m24512.h"
#include "i2c.h"
#include "version.h"


/*
 * Defines
 */


// Message types
#define REQ_HEURE  1
#define PAR_HEURE  0

// EndDevice MAC addr base
#define APP_DEVICE_UID  0xAAAAAAABBBBBB121LL

// Coordinator address
#define COORDINATOR_NETWORK_ADDRESS         0x0000      // Default coordinator short (NWK) address

#define TIMER_100ms_INTERVAL 100

#define APP_ENDPOINT                        2           // Endpoint will be used
#define APP_PROFILE_ID                      1           // Profile Id will be used
#define APP_CLUSTER_ID                      1           // Cluster Id will be used

/*
 * Typedef
 */

typedef enum
{
    APP_INITIAL_STATE,                                    // Application initial state (after Power On or Reset)
    APP_NETWORK_JOINING_STATE,                            // Joining network state
    APP_NETWORK_JOINED_STATE,                             // Network available
    APP_ERROR_STATE                                       // Error state
} AppState_t;


// Enddevice state
typedef enum
{
    DEVICE_ACTIVE_IDLE_STATE,                             // Device is not in sleep state
    DEVICE_SENDING_MESSAGE_STATE,
    DEVICE_RESPONSE_WAITING_STATE,
    DEVICE_SLEEP_PREPARE_STATE,
    DEVICE_SLEEP_STATE,                                   // Actually sleep state
    DEVICE_AWAKENING_STATE                                // Node was interrupted. Awakening.
} AppDeviceState_t;


typedef enum                                              // Data transmission feature state
{
    APP_DATA_TRANSMISSION_IDLE_STATE,                     // Data transmission was finished or(and) not started yet
    APP_DATA_TRANSMISSION_BUSY_STATE                      // Data transmission in progress
} AppDataTransmissionState_t;

typedef struct
{
    uint8_t requete;
    uint8_t param;
} PACK AppMessageOut_t;

typedef struct                                          // Application message buffer
{
    uint8_t        header[APS_ASDU_OFFSET];               // Auxilliary header (stack required)
    AppMessageOut_t   message;                               // Actually application message
    uint8_t        footer[APS_AFFIX_LENGTH - APS_ASDU_OFFSET]; // Auxilliary footer (stack required)
} PACK AppMessageOutBuffer_t;

typedef struct
{
    uint8_t reponse;      // Reponse recue du coordinateur
    uint32_t date;
} PACK AppMessageIn_t;

/*
 * Global variables
 */

font_t font_5x7         = {0x0000,5,5,7};
font_t font_7x11        = {0x0241,14,7,11};	// afficheurs N°3,4, 5 (nouvelles fontes)
//font_t font_7x11        = {0x012D,14,7,11};  // afficheurs N°1,2,6 (anciennes fontes : à reprog)

/*
 * Local variables
 */

static AppDataTransmissionState_t appDataTtransmissionState = APP_DATA_TRANSMISSION_IDLE_STATE;

static HAL_AppTimer_t timer100ms;

static uint16_t tmp;
static uint8_t numAfficheur = 0;
static uint8_t numCanal = 0;
static ExtAddr_t    extAddr;
static ShortAddr_t  nwkAddr;
static uint32_t     channelMask;

static char stringLCD[30];
static bool lcdPrint = false;
static bool flagDataReceived;
//static uint8_t cptTry=0;

static AppMessageOutBuffer_t appMessageOutBuffer;
static AppMessageIn_t appMessageIn;

static AppState_t   appState = APP_INITIAL_STATE;                     // Current application state
static AppDeviceState_t appDeviceState = DEVICE_ACTIVE_IDLE_STATE;    // Current device state

// Endpoint simple descriptor (ZDO endpoint descriptor)
static SimpleDescriptor_t        simpleDescriptor = {APP_ENDPOINT, APP_PROFILE_ID, 1, 1, 0, 0 , NULL, 0, NULL};
static APS_RegisterEndpointReq_t apsRegisterEndpointReq;    // APS Register Endpoint Request primitive (APS endpoint descriptor)
static APS_DataReq_t apsDataReq;                            // APS Data Request primitive (for application message sending)


// ZDO primitives
static ZDO_StartNetworkReq_t  zdoStartNetworkReq;
static ZDO_ZdpReq_t leaveReq;
static ZDO_NwkStatus_t zdoNwkStatus;
static ZDO_SleepReq_t zdoSleepReq;                          // Request parameters for stack sleep
static ZDO_WakeUpReq_t zdoWakeUpReq;                        // Request parameters for stack awakening
static ZDO_ResetNetworkReq_t resetParams;

/*
 * Static functions
 */

static void timer100msFired(void);
static void initApp(void);
static void initAfficheur(void);
static void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t *confInfo);
static void APS_DataInd(APS_DataInd_t *ind);
static void sendMessage(void);
static void zdpLeaveResp(ZDO_ZdpResp_t *zdpResp);
static void startNetwork(void);
static void deviceTaskHandler(void);
static void ZDO_WakeUpConf(ZDO_WakeUpConf_t *conf);         // Wake up confirmation handler
static void APS_DataConf(APS_DataConf_t *conf);             // Data transmission confirmation handler
static void afficherMessage(void);
static void ZDO_SleepConf(ZDO_SleepConf_t *conf);
static void prepareToSleep(void);
static void wakeUpHandler(void);


static void buttonsPressed(uint8_t buttonNumber)
{
    GPIO_1_clr();
    if (GPIO_8_read() == 1)
        GPIO_6_clr(); // power off
}

static void buttonsReleased(uint8_t buttonNumber)
{
    // A COMPLETER
    GPIO_1_set();
    if ((appState == APP_NETWORK_JOINED_STATE) && (appDeviceState == DEVICE_ACTIVE_IDLE_STATE))
	        {
			        appDeviceState = DEVICE_SENDING_MESSAGE_STATE;
				        SYS_PostTask(APL_TASK_ID);
					    }
}

/********************************************************************
  Description:  application and stack parameters init
  Parameters:   none
  Returns:      none
********************************************************************/
static void initApp(void)
{

    GPIO_6_make_out(); // power_on
    GPIO_6_set();

    GPIO_0_make_out(); //led rouge
    GPIO_1_make_out(); //led verte

    GPIO_0_clr(); // led rouge on
    GPIO_1_clr(); // led verte on

    // init i2c
    i2cInit();

    // init IT button
    BSP_OpenButtons(buttonsPressed, buttonsReleased);

}

/********************************************************************
  Description:  Init LCD
  Parameters:   none
  Returns:      none
********************************************************************/

static void initAfficheur(void)
{

    // switch read
    uint16_t data = 0xFFFF;
    i2cWrite(PCF8575_SWITCH_ADDRESS,(uint8_t *)&data,2);
    i2cRead(PCF8575_SWITCH_ADDRESS,(uint8_t *)&data,2);

    uint16_t datatmp = data;
    numAfficheur = ~((uint8_t)data);

    // Coordinator address test
    if (numAfficheur == 0)
    {
        GPIO_0_clr();
        GPIO_1_clr();
        while (1);  //error
    }
    numCanal = (uint8_t)(~(datatmp >> 8)&0x0F) +11;

    // Assign own MAC address
    extAddr     = APP_DEVICE_UID + numAfficheur;
    CS_WriteParameter(CS_UID_ID, &extAddr);

    // Assign NWK address
    nwkAddr = numAfficheur;
    CS_WriteParameter(CS_NWK_ADDR_ID, &nwkAddr);

    // Assign Channel Mask
    channelMask = (0x01L << numCanal);
    CS_WriteParameter(CS_CHANNEL_MASK_ID,&channelMask);

    // LCD init
    _lcdInit();
    _lcdClear();

    sprintf(stringLCD, "V%s",FULLVERSION_STRING);
    _lcdPutString(stringLCD,font_7x11,1,50);
    sprintf(stringLCD, "C%02d",numCanal);
    _lcdPutString(stringLCD,font_7x11,97,30);
    sprintf(stringLCD, "A%03d",numAfficheur);
    _lcdPutString(stringLCD,font_7x11,97,40);

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
        initApp();                          // Init application as a whole
        initAfficheur();
        GPIO_0_set();                   // led rouge off
        GPIO_1_set();                   // leg verte off
        lcdPrint = false;
        appState = APP_NETWORK_JOINING_STATE;
        SYS_PostTask(APL_TASK_ID);            // Application task posting
        break;

    case APP_NETWORK_JOINING_STATE:         // Network is in the joining stage
        if (!lcdPrint)
        {
            sprintf(stringLCD, "   ");
            _lcdPutString(stringLCD,font_7x11,107,56);
            sprintf(stringLCD, "~^~");
            _lcdPutString(stringLCD,font_7x11,107,56);
            lcdPrint = true;
        }
        startNetwork();                       // Start/joing network
        break;

    case APP_NETWORK_JOINED_STATE:          // Network was successfully started
        if (!lcdPrint)
        {
            sprintf(stringLCD, "   ");
            _lcdPutString(stringLCD,font_7x11,107,56);
            sprintf(stringLCD, "~~~");
            _lcdPutString(stringLCD,font_7x11,107,56);
            lcdPrint = true;
        }
        deviceTaskHandler();                  // Normal device operation when one joined network
        break;


    default:
        break;
    }
}

/********************************************************************
  Description:  Device common task handler
  Parameters:   none
  Returns:      none
********************************************************************/
static void deviceTaskHandler(void)
{
    switch (appDeviceState)                     // Actual device state when one joined network
    {
    case DEVICE_ACTIVE_IDLE_STATE:            // Device ready
        break;

    case DEVICE_SENDING_MESSAGE_STATE:            // sending message
        sendMessage();
        break;

    case DEVICE_RESPONSE_WAITING_STATE:
        break;

    case DEVICE_SLEEP_PREPARE_STATE:          // Prepare to sleep state
        prepareToSleep();
        break;

    case DEVICE_AWAKENING_STATE:              // Awakening state
        zdoWakeUpReq.ZDO_WakeUpConf = ZDO_WakeUpConf; // ZDO WakeUp confirm handler defining
        ZDO_WakeUpReq(&zdoWakeUpReq);                 // ZDO WakeUp Request sending
        break;

    default:
        break;
    }
}

/********************************************************************
  Description:
  Parameters:   none
  Returns:      none
********************************************************************/

static void startNetwork()
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
    // Joined network successfully
    if ((ZDO_SUCCESS_STATUS == confInfo->status))   // Network was started successfully
    {
        appState = APP_NETWORK_JOINED_STATE;          // Application state switching
        appDeviceState = DEVICE_ACTIVE_IDLE_STATE;
        lcdPrint = false;

        // Set application endpoint properties
        apsRegisterEndpointReq.simpleDescriptor = &simpleDescriptor;
        apsRegisterEndpointReq.APS_DataInd = APS_DataInd;
        // Register endpoint
        APS_RegisterEndpointReq(&apsRegisterEndpointReq);

    }
    SYS_PostTask(APL_TASK_ID);                      // Application task posting
}


/*******************************************************************************
 Description:
 Parameters:
 Returns: none
*******************************************************************************/
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *nwkParams)
{

    ZDO_StartNetworkConf_t conf;
    if (ZDO_NETWORK_STARTED_STATUS == nwkParams->status)
    {
        conf.status = ZDO_SUCCESS_STATUS;
        ZDO_StartNetworkConf(&conf);
    }
    else if (ZDO_NETWORK_LEFT_STATUS == nwkParams->status)
    {
        lcdPrint = false;
        appState =  APP_NETWORK_JOINING_STATE;
        SYS_PostTask(APL_TASK_ID);
    }
}


/********************************************************************
  Description:  Send the application message
  Parameters:   none
  Returns:      none
********************************************************************/
static void sendMessage(void)
{
  // A COMPLETER
        GPIO_0_clr();

        appDataTtransmissionState = APP_DATA_TRANSMISSION_BUSY_STATE;

        sprintf(stringLCD, "   ");
        _lcdPutString(stringLCD,font_7x11,107,56);
        sprintf(stringLCD, "~>~");
        _lcdPutString(stringLCD,font_7x11,107,56);

        // A COMPLETER
        appMessageOutBuffer.message.requete = REQ_HEURE;
        appMessageOutBuffer.message.param = PAR_HEURE;

        // prepare and send APS Data Request
        apsDataReq.dstAddrMode             = APS_SHORT_ADDRESS;                           // Short addressing mode
        // A COMPLETER
        apsDataReq.dstAddress.shortAddress = COORDINATOR_NETWORK_ADDRESS;                 // Destination node short address

        apsDataReq.dstEndpoint             = APP_ENDPOINT;                                // Destination endpoint
        apsDataReq.profileId               = simpleDescriptor.AppProfileId;               // Profile ID
        apsDataReq.clusterId               = APP_CLUSTER_ID;                              // Destination cluster ID
        apsDataReq.srcEndpoint             = APP_ENDPOINT;                                // Source endpoint
        apsDataReq.asduLength              = sizeof (AppMessageOut_t);                    // ASDU size
        apsDataReq.asdu             	   = (uint8_t *) &appMessageOutBuffer.message;    // ASDU pointer as an application message
        apsDataReq.txOptions.acknowledgedTransmission = 0;                                // Acknowledged transmission enabled
        apsDataReq.radius                  = 0;                                           // Default radius
        apsDataReq.APS_DataConf            = APS_DataConf;                                // Confirm handler
        APS_DataReq(&apsDataReq);                                                         // Data Request sending

}

/********************************************************************
  Description:  Data sent handler
  Parameters:   conf - APS Data Confirm primitive
  Returns:      none
********************************************************************/
static void APS_DataConf(APS_DataConf_t *conf)
{
  // A COMPLETER
    GPIO_0_set();
    appDataTtransmissionState = APP_DATA_TRANSMISSION_IDLE_STATE; // Data transmission entity is idle
    switch (conf->status)
    {
    case APS_SUCCESS_STATUS :
        appDeviceState = appDeviceState = DEVICE_ACTIVE_IDLE_STATE;
        sprintf(stringLCD, "   ");
        _lcdPutString(stringLCD,font_7x11,107,56);
        sprintf(stringLCD, "~~~",conf->status);
        _lcdPutString(stringLCD,font_7x11,107,56);
        break;


    default:
        // List of status error code :
        // 0xE9 : MAC_NO_ACK_STATUS
        // 0xA3 : APS_ILLEGAL_REQUEST_STATUS

        sprintf(stringLCD, "   ");
        _lcdPutString(stringLCD,font_7x11,107,56);
        sprintf(stringLCD, "!%02X",conf->status);
        _lcdPutString(stringLCD,font_7x11,107,56);
        appDeviceState = DEVICE_SENDING_MESSAGE_STATE;    // Data transmission wasn't successfully finished. Retry.
        break;
    }

    SYS_PostTask(APL_TASK_ID);                      // Application task posting
}

/********************************************************************
  Description:  Application endpoint indication handler
  Parameters:   ind - APS Data Indication primitive
  Returns:      none
********************************************************************/
static void APS_DataInd(APS_DataInd_t *indData)
{
  // A COMPLETER
    GPIO_0_clr();
    sprintf(stringLCD, "   ");
    _lcdPutString(stringLCD,font_7x11,107,56);
    sprintf(stringLCD, "~<~");
    _lcdPutString(stringLCD,font_7x11,107,56);
    memcpy(&appMessageIn,indData->asdu,indData->asduLength);
    sprintf(stringLCD, "                ");
    _lcdPutString(stringLCD,font_7x11,1,1);
    sprintf(stringLCD, "date : %u",appMessageIn.date);
    _lcdPutString(stringLCD,font_7x11,1,1);
    sprintf(stringLCD, "                ");
    _lcdPutString(stringLCD,font_7x11,1,11);
    sprintf(stringLCD, "rssi : %d",(int8_t)(indData->rssi));
    _lcdPutString(stringLCD,font_7x11,1,11);
    sprintf(stringLCD, "   ");
    _lcdPutString(stringLCD,font_7x11,107,56);
    sprintf(stringLCD, "~~~");
    _lcdPutString(stringLCD,font_7x11,107,56);
    GPIO_0_set();
}


/********************************************************************
  Description:  Prepare to sleep
  Parameters:   none
  Returns:      none
********************************************************************/
static void prepareToSleep(void)
{
}

/********************************************************************
  Description:  ZDO Sleep Confirm handler
  Parameters:   conf - ZDO Sleep Confirm primitive
  Returns:      none
********************************************************************/
static void ZDO_SleepConf(ZDO_SleepConf_t *conf)
{
}

/*******************************************************************************
 Description:
 Parameters:
 Returns: none
*******************************************************************************/

static void zdpLeaveResp(ZDO_ZdpResp_t *zdpResp)
{
}


/********************************************************************
  Description: Device wakeup handler. Initialize
  Returns:    none
********************************************************************/
static void wakeUpHandler(void)
{
}

/*******************************************************************************
  Description: just a stub.
  Parameters: none.
  Returns: nothing.
*******************************************************************************/
void ZDO_WakeUpInd(void)
{
}

/********************************************************************
  Description: Wake up confirmation handler
  Parameters: conf - confirmation parameters
  Returns: nothing.
********************************************************************/
void ZDO_WakeUpConf(ZDO_WakeUpConf_t *conf)
{
}

/*******************************************************************************
  Description: just a stub.
  Parameters: none.
  Returns: nothing.
*******************************************************************************/
void ZDO_SleepInd(void)
{
}


/********************************************************************
  Description:  Print stack parameters
  Parameters:   none
  Returns:      none
********************************************************************/

static void ZDO_ResetNetworkConf(ZDO_ResetNetworkConf_t *conf)
{
    conf=conf;
}

