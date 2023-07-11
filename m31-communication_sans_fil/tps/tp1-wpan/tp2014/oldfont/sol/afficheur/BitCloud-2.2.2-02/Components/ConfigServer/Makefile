COMPONENTS_PATH = ..
#The correct user's Makerules* must be included!
include $(COMPONENTS_PATH)/../lib/Makerules*
 
#### COMPILER FLAGS #######
##### PATHS FLAGS OF INCLUDES #########
CFLAGS += -I./include
CFLAGS += -I$(SE_PATH)/include
CFLAGS += -I$(ZDO_PATH)/include
CFLAGS += -I$(NWK_PATH)/include
CFLAGS += -I$(APS_PATH)/include
CFLAGS += -I$(MAC_PHY_PATH)/include
CFLAGS += -I$(HAL_PATH)/include
CFLAGS += -I$(HAL_HWD_PATH)/include
CFLAGS += -I$(SSP_PATH)/include
CFLAGS += -I$(PDS_PATH)/include
CFLAGS += -I$(TC_PATH)/include

###### LIB #########
BUILDDIR = .
LIBDIR = $(BUILDDIR)/lib
LDFLAGS = -L$(LIBDIR)
LIB = $(LIBDIR)/lib$(CS_LIB).a 

objects = $(BUILDDIR)/objs/configServer.o       

###### TARGETS ################
all: LIB_CONFIG_SERVER
################
$(objects): 
	$(CC) $(CFLAGS) -c $^ -o $@
#	$(CC) $(CFLAGS) -E $^ -o $@.e
$(BUILDDIR)/objs/configServer.o: $(BUILDDIR)/src/configServer.c
################
LIB_CONFIG_SERVER: $(objects)
	$(AR) cr $(LIB) $(objects)
	$(SIZE) -td $(LIB)
################

clean:
	rm -f $(PROG) $(objects) $(LIB) 
