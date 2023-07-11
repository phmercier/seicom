COMPONENTS_PATH = ..
#The correct user's Makerules* must be included!
include $(COMPONENTS_PATH)/../lib/Makerules*

###### LIB ##########
ifeq ($(BOARD), MESHBEAN)
  BUILDDIR = ./MeshBean
endif
ifeq ($(BOARD), STK500)
  BUILDDIR = ./STK500
endif
ifeq ($(BOARD), ARM_GWM)
  BUILDDIR = ./GWM
endif
ifeq ($(BOARD), ARM_TURBO)
  BUILDDIR = ./Turbo
endif
ifeq ($(BOARD), ARM_EVALUATION)
  BUILDDIR = ./AT91SAM7X-EK
endif

LIBDIR = ./lib
LDFLAGS = -L$(LIBDIR)
PROG = BSP.elf
LIBS = $(LIBDIR)/lib$(BSP_LIB).a

##### PATHS FLAGS OF INCLUDES #########
CFLAGS += -I$(BUILDDIR)/include
CFLAGS += -I$(BUILDDIR)/../include
CFLAGS += -I$(HAL_PATH)/include  
CFLAGS += -I$(HAL_HWD_PATH)/include
CFLAGS += -I$(SE_PATH)/include


ifeq ($(BOARD), MESHBEAN)
modules =                       \
       leds                     \
       pwrCtrl                  \
       bspTaskManager           \
       buttons                  \
       lm73                     \
       tsl2550                  \
       battery                  \
       sliders                  \
       sensors
endif
ifeq ($(BOARD), STK500)
modules =                       \
       leds                     \
       pwrCtrl                  \
       bspTaskManager           \
       buttons                  \
       battery                  \
       sliders                  \
       sensors
endif
ifeq ($(BOARD), ARM_GWM)
modules =                       \
       leds                     \
       buttons                  \
	   bspTaskManager
endif
ifeq ($(BOARD), ARM_TURBO)
modules =                       \
       leds                     \
       buttons                  \
       sliders                  \
	   bspTaskManager
endif
ifeq ($(BOARD), ARM_EVALUATION)
modules =                       \
       leds                     \
	   joystick                 \
	   bspTaskManager
endif

objects = $(addsuffix .o,$(addprefix $(BUILDDIR)/objs/,$(modules)))

sources = $(addsuffix .c,$(addprefix $(BUILDDIR)/src/,$(modules)))

###### TARGETS ################
all:  LIB_BSP
################
$(BUILDDIR)/objs/%.o: $(BUILDDIR)/src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

################
LIB_BSP : $(objects)
	$(AR) cr $(LIBDIR)/lib$(BSP_LIB).a $(objects)
	$(SIZE) -td $(LIBDIR)/lib$(BSP_LIB).a
################
clean:
	rm -f $(objects) $(LIBS)
