/******************************************************************************
  nwkSystem.h
  Copyright (c)Meshnetics.
  Description: 
    definition header file.
  History:
    20/06/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKSYSTEM_H
#define _NWKSYSTEM_H

#ifndef FIELD_OFFSET
#define FIELD_OFFSET(TYPE, FIELD)  \
  (((uint8_t*)&(((TYPE *)NULL)->FIELD))-(uint8_t*)NULL)
#endif

#define GET_PARENT_BY_FIELD(TYPE, FIELD, FIELD_POINTER)  \
  ((TYPE *)(((uint8_t *)FIELD_POINTER) - FIELD_OFFSET(TYPE, FIELD)))


#define DEFINE_DBG_ARRAY(TYPE) \
  TYPE (*dbg5##TYPE)[5];   \
  TYPE (*dbg10##TYPE)[10]; \
  TYPE (*dbg20##TYPE)[20]; \
  TYPE (*dbg40##TYPE)[40]

//#define DEFINE_DBG_ARRAY(TYPE) 

#define NWK_DATA_FRAME_HEADER_LEHGTH 9
#define NWK_SECURITY_HEADER_SIZE     14

#endif //_NWKSYSTEM_H
//eof
