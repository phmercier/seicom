COMPONENTS_PATH = ..
#The correct user's Makerules* must be included!
include $(COMPONENTS_PATH)/../lib/Makerules*

#### COMPILER FLAGS #######
##### PATHS FLAGS OF INCLUDES #########
CFLAGS += -I./include
CFLAGS += -I$(CS_PATH)/include
CFLAGS += -I$(BSP_PATH)/include
CFLAGS += -I$(SE_PATH)/include
CFLAGS += -I$(ZDO_PATH)/include
CFLAGS += -I$(NWK_PATH)/include
CFLAGS += -I$(APS_PATH)/include
CFLAGS += -I$(MAC_PHY_PATH)/include
CFLAGS += -I$(HAL_PATH)/include
CFLAGS += -I$(HAL_HWD_PATH)/include
CFLAGS += -I$(SSP_PATH)/include

###### LIB #########
BUILDDIR = .
LIBDIR = $(BUILDDIR)/lib
LDFLAGS = -L$(LIBDIR)

objects =                             \
$(BUILDDIR)/objs/pdsDataServer.o  \
$(BUILDDIR)/objs/pdsWriteData.o  \
$(BUILDDIR)/objs/pdsCrcService.o
###### TARGETS ################
all:  LIB_PERSIST_DATA_SERVER
################
$(objects): 
	$(CC) $(CFLAGS) -c $^ -o $@
$(BUILDDIR)/objs/pdsDataServer.o: $(BUILDDIR)/src/pdsDataServer.c
$(BUILDDIR)/objs/pdsWriteData.o: $(BUILDDIR)/src/pdsWriteData.c
$(BUILDDIR)/objs/pdsCrcService.o: $(BUILDDIR)/src/pdsCrcService.c
################
LIB_PERSIST_DATA_SERVER : $(objects)
	$(AR) cr $(LIBDIR)/lib$(PDS_LIB).a $(objects)
	$(SIZE) -td $(LIBDIR)/lib$(PDS_LIB).a
################

clean:
	rm -f $(objects) $(LIB_PERSIST_DATA_SERVER)
