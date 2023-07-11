/******************************************************************************
  nwkDbh.h
  Copyright (c)Meshnetics.

  Description:
              
******************************************************************************/

/***********************************
 NWK section. Range 0x3000 - 0x3FFF
***********************************/

enum _NwkDbgCode_t
{
  NWK_DBG_SECTION                        = 0x3000,
  NWK_NULL_CALLBACK_DATAREQ                      ,
  NWK_NULL_CALLBACK_DISCOVERY                    ,
  NWK_NULL_CALLBACK_EDSCAN                       ,
  NWK_NULL_CALLBACK_FORMATION                    ,
  NWK_NULL_CALLBACK_JOINREQ                      ,
  NWK_NULL_CALLBACK_LEAVE                        ,
  NWK_NULL_CALLBACK_PERMITJOINING                ,
  NWK_NULL_CALLBACK_ROUTEDISCOVERY               ,
  NWK_NULL_CALLBACK_STARTROUTER                  ,
};

