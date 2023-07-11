PROJNAME = coordinateur

# Path to the Stack
STACK_PATH = BitCloud-2.2.2-02/Components

include $(STACK_PATH)/../lib/MakerulesBcCoordinator
include ./Makerules

#-------------------------------------
# Application parameters
#-------------------------------------

#Enables debugging support
CFLAGS += -g

#-------------------------------------
# Stack parameters being set to Config Server
#-------------------------------------

#depends on your application – if you need guaranteed delivery – than use APS ack (set true or 1)
CFLAGS += -DAPP_USE_APS_ACK=0
CFLAGS += -DCS_NWK_UNIQUE_ADDR=true
CFLAGS += -DCS_NWK_ADDR=0x0000
CFLAGS += -DCS_DEVICE_TYPE=DEVICE_TYPE_COORDINATOR

# Coordinateur 1
#CFLAGS += -DCS_EXT_PANID=0xAAAAAAAAAAAAAAAALL
#CFLAGS += -DCANAL=11

# Coordinateur 2
#CFLAGS += -DCS_EXT_PANID=0xABABABABABABABABLL
#CFLAGS += -DCANAL=13

# Coordinateur 3
#CFLAGS += -DCS_EXT_PANID=0xBBBBBBBBBBBBBBBBLL
#CFLAGS += -DCANAL=15

# Coordinateur 4
#CFLAGS += -DCS_EXT_PANID=0xBCBCBCBCBCBCBCBCLL
#CFLAGS += -DCANAL=17

# Coordinateur 5
#CFLAGS += -DCS_EXT_PANID=0xCCCCCCCCCCCCCCCCLL
#CFLAGS += -DCANAL=19

# Coordinateur 6
CFLAGS += -DCS_EXT_PANID=0xCDCDCDCDCDCDCDCDLL
CFLAGS += -DCANAL=21

#false for End Devices only
CFLAGS += -DCS_RX_ON_WHEN_IDLE=true
#15 – is a maximum network depth (four bits field), if you want to control network topology – play with this value
CFLAGS += -DCS_MAX_NETWORK_DEPTH=3
#Neighbor table size – should exceed MAX_CHILDREN_AMOUNT by 1 at least
CFLAGS += -DCS_NEIB_TABLE_SIZE=11
#Total number of children
CFLAGS += -DCS_MAX_CHILDREN_AMOUNT=10
#Number of routers children among total children number
CFLAGS += -DCS_MAX_CHILDREN_ROUTER_AMOUNT=0
#all memory/2 (CS_ROUTE_TABLE_SIZE and CS_ADDRESS_MAP_TABLE_SIZE should be equal to each other and in case of big networks be as big as RAM size allows)
CFLAGS += -DCS_ROUTE_TABLE_SIZE=40
#all memory/2 (CS_ROUTE_TABLE_SIZE and CS_ADDRESS_MAP_TABLE_SIZE should be equal to each other and in case of big networks be as big as RAM size allows)
CFLAGS += -DCS_ADDRESS_MAP_TABLE_SIZE=40
# should be increased in case of big networks
# coord and routers must know the sleep period of children to maintain the neibtable
# should be the same than enddevice
CFLAGS += -DCS_END_DEVICE_SLEEP_PERIOD=30000

## serial com debug : comment for no debug
CFLAGS += -D_DBG_


## app include dirs
INCLUDES += -I.

## app objects to build
OBJ = coordinateur.o printCom.o
## path to app objects
VPATH += .:

## objects to build with -O0
#DBG_OBJS =

#-------------------------------------
# Build
#-------------------------------------
all: clean $(PROJNAME).elf $(PROJNAME).srec $(PROJNAME).hex size

$(OBJ) $(STACK_OBJ): %.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $^ -o $@

$(DBG_OBJ): %.o: %.c
	$(CC) -c $(CFLAGS) -O0 $(INCLUDES) $^ -o $@

#-------------------------------------
# Link
#-------------------------------------
$(PROJNAME).elf: $(OBJ) $(DBG_OBJ) $(STACK_OBJ) Makefile
	$(CC) $(CFLAGS) $(OBJ) $(DBG_OBJ) $(STACK_OBJ) $(LIB_PATH)/WdtInitatmega1281.o -o $(PROJNAME).elf -L$(LIB_PATH) -L$(BSP_PATH)/lib -l$(STACK_LIB)
	rm -f *.o

%.srec: %.elf
	avr-objcopy -O srec --srec-len 128 $< $@

%.hex: %.elf
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

size:
	avr-size -td $(PROJNAME).elf

clean:
	rm -rf *.elf *.hex *.srec *.o

# eof Makefile
