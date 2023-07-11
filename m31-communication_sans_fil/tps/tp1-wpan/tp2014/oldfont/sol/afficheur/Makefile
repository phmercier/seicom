PROJNAME = afficheur

# Path to the Stack
STACK_PATH = BitCloud-2.2.2-02/Components

#include $(STACK_PATH)/../lib/MakerulesBcAll
include $(STACK_PATH)/../lib/MakerulesBcEndDevice
include ./Makerules

# depends on your application – if you need guaranteed delivery – than use APS ack (set true or 1))
CFLAGS += -DAPP_USE_APS_ACK=0
CFLAGS += -DCS_NWK_UNIQUE_ADDR=true
CFLAGS += -DCS_DEVICE_TYPE=DEVICE_TYPE_END_DEVICE

# Coordinateur 1
CFLAGS += -DCS_EXT_PANID=0xAAAAAAAAAAAAAAAALL

# Coordinateur 2
# CFLAGS += -DCS_EXT_PANID=0xABABABABABABABABLL

# Coordinateur 3
# CFLAGS += -DCS_EXT_PANID=0xBBBBBBBBBBBBBBBBLL

# Coordinateur 4
# CFLAGS += -DCS_EXT_PANID=0xBCBCBCBCBCBCBCBCLL

# Coordinateur 5
# CFLAGS += -DCS_EXT_PANID=0xCCCCCCCCCCCCCCCCLL

# Coordinateur 6
# CFLAGS += -DCS_EXT_PANID=0xCDCDCDCDCDCDCDCDLL

CFLAGS += -DCS_RX_ON_WHEN_IDLE=false
# minimum is 1, but 4 will increase “join speed”
CFLAGS += -DCS_NEIB_TABLE_SIZE=4
CFLAGS += -DCS_MAX_CHILDREN_AMOUNT=0
CFLAGS += -DCS_MAX_CHILDREN_ROUTER_AMOUNT=0
CFLAGS += -DCS_ROUTE_TABLE_SIZE=1
# should be increased in case of big networks
CFLAGS += -DCS_END_DEVICE_SLEEP_PERIOD=30000


CFLAGS += -g

## serial com debug : comment for no debug
#CFLAGS += -D_DBG_

## app include dirs
INCLUDES += -I.

## app objects to build
OBJ = afficheur.o buttons.o bspTaskManager.o
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
	$(CC) $(CFLAGS) $(OBJ) $(DBG_OBJ) $(STACK_OBJ) $(LIB_PATH)/WdtInitatmega1281.o -o $(PROJNAME).elf -L$(LIB_PATH) -L$(BSP_PATH)/lib -l$(STACK_LIB) lcd.a
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
