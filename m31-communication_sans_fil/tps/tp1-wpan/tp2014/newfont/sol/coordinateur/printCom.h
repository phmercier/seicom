#ifndef PRINTCOM_H_INCLUDED
#define PRINTCOM_H_INCLUDED

// UART Rx buffer size
#ifndef APP_UART_RX_BUFFER_SIZE
#define APP_UART_RX_BUFFER_SIZE             50
#endif


// UART Tx buffer size
#ifndef APP_UART_TX_BUFFER_SIZE
#define APP_UART_TX_BUFFER_SIZE             100
#endif

// Temporary data received via network buffer size
#ifndef APP_TMP_DATA_BUFFER_SIZE
#define APP_TMP_DATA_BUFFER_SIZE            100
#endif



#ifndef APP_UART_CHANNEL
#define APP_UART_CHANNEL                    UART_CHANNEL_1
#endif

#define APP_MAX_DATA_SIZE                   APS_MAX_ASDU_SIZE


//void UARTDataSent();

void initUART(void);                            // Common application initial function
void writeConf(void);
void sendDataToUart(uint8_t* data, uint8_t length);
void printComMsgVersion(uint8_t version, uint8_t sousVersion);
void printComMsg(const char *msg);
void printComMsgData(const char *msg, uint16_t data);
void printComData8(uint8_t data2);
void printComTxtData8(char * txt,uint8_t data2);
void printComData16(uint16_t data2);
void printComData64(uint64_t data2);
void printComOoops(uint8_t id);
void sendDataToPCServer(uint8_t requete, uint16_t afficheur);
void startReceptionDataFromPCServer();
bool queryDataFromPCServer(uint8_t *buffer, uint8_t length);

#endif // LCD_H_INCLUDED
