### You only have to modify here when you add a new file.
OSPATH = src/OS
MYLIBPATH = src/MyLib/ \
			src/MyLib/Stdout/ src/MyLib/Stdout/Driver \
			src/MyLib/Adc src/MyLib/Adc/Driver \
			src/MyLib/Led src/MyLib/Led/Driver \
			src/MyLib/WaveGenerator src/MyLib/WaveGenerator/Driver \
			src/MyLib/ThermoCouple src/MyLib/ThermoCouple/Driver \
			src/MyLib/Servo src/MyLib/Servo/Driver 
COMPATH   = src/Common src/Common/FreeRTOS_DemoFile
APPPATH = src/App
###

SRCPATH = src $(OSPATH) $(MYLIBPATH) $(COMPATH) $(APPPATH)

OBJDIR = objs
BINDIR = bin

ifeq ($(OS),Windows_NT)
#	SHELL = cmd.exe
#	REMOVE = del /f /q $(BINDIR)\* $(OBJDIR)\*
	SHELL = sh
	REMOVE = rm -f $(BINDIR)/* $(OBJDIR)/*
	TOOLDIR = ../../Launchpad/bin/
	STARTUP_ASM = ./Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc_ride7/startup_stm32f072.s
	SYSTEM_INIT = ./src/Common/FreeRTOS_DemoFile/system_stm32f0xx.c
	#MKOBJDIR = $(shell if not exist $(OBJDIR) mkdir $(OBJDIR))
	#MKBINDIR = $(shell if not exist $(BINDIR) mkdir $(BINDIR))
	MKOBJDIR =  
	MKBINDIR =  
else
	SHELL = sh
	REMOVE = rm -f $(BINDIR)/* $(OBJDIR)/*
	TOOLDIR = 
	STARTUP_ASM = ./Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc_ride7/startup_stm32f072.s
	#SYSTEM_INIT = ./src/Common/FreeRTOS_DemoFile/system_stm32f0xx.c
	SYSTEM_INIT = ./src/Common/FreeRTOS_DemoFile/system_stm32f0xx.c
	MKOBJDIR = $(shell if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi;)
	MKBINDIR = $(shell if [ ! -d $(BINDIR) ]; then mkdir $(BINDIR); fi;)
endif

FREERTOS_DIR = ./Libraries/FreeRTOS
FREERTOS_PLUS_DIR = ./Libraries/FreeRTOS-Plus

TARGET_ARCH   = -mcpu=cortex-m0 -mthumb
INCLUDE_DIRS  = 	-I ./Libraries/STM32F0xx_StdPeriph_Driver/inc \
					-I ./Libraries/CMSIS/Device/ST/STM32F0xx/Include \
					-I ./Libraries/CMSIS/Include \
					-I ./src/include \
					-I ./src \
					-I $(TOOLDIR)../arm-none-eabi/include \
					-I $(TOOLDIR)../arm-none-eabi/include/c++/4.6.2 \
					-I $(FREERTOS_DIR)/Demo/Common/include \
					-I $(FREERTOS_DIR)/Source/include \
					-I $(FREERTOS_DIR)/Source/portable/GCC/ARM_CM0

BOARD_OPTS = -DHSE_VALUE=12000000 -DSTM32F0XX -DSTM32F07_07xxx -DSTM32F072 -DUSE_32F072IDISCOVERY
FIRMWARE_OPTS = -DUSE_STDPERIPH_DRIVER
COMPILE_OPTS  = -O2 -g3 -ffunction-sections -fdata-sections -fsigned-char -fno-exceptions \
					-Wall -fmessage-length=0 $(INCLUDE_DIRS) $(BOARD_OPTS) $(FIRMWARE_OPTS)

CC      = $(TOOLDIR)arm-none-eabi-gcc
CXX     = $(TOOLDIR)arm-none-eabi-g++
AS      = $(CXX)
LD      = $(CXX)
AR      = $(TOOLDIR)arm-none-eabi-ar
OBJCOPY = $(TOOLDIR)arm-none-eabi-objcopy
CFLAGS  = $(COMPILE_OPTS) -std=gnu99
CXXFLAGS= $(COMPILE_OPTS)  -fno-rtti -fpermissive -fno-threadsafe-statics
ASFLAGS = -x assembler-with-cpp -c $(TARGET_ARCH) $(COMPILE_OPTS) 
LDFLAGS = -Wl,--gc-sections,-Map=$(BINDIR)/main.map,-cref -T stm32_flash.ld -lstdc++ -L $(TOOLDIR)../arm-none-eabi/lib/thumb -L $(OBJDIR)

SRCS = $(wildcard $(addsuffix /*.c, $(SRCPATH)))
CPPSRCS = $(wildcard $(addsuffix /*.cpp, $(SRCPATH)))
OBJS = $(notdir $(patsubst %.c,%.o,$(SRCS)))
OBJS += $(notdir $(patsubst %.cpp,%.o,$(CPPSRCS)))

LIB_SRCS = \
 $(wildcard ./Libraries/STM32F0xx_StdPeriph_Driver/src/*.c) \
 $(wildcard $(FREERTOS_DIR)/Source/portable/MemMang/heap_1.c) \
 $(wildcard $(FREERTOS_DIR)/Source/*.c) \
 $(wildcard $(FREERTOS_DIR)/Source/portable/GCC/ARM_CM0/*.c) \
 $(FREERTOS_DIR)/Demo/Common/Minimal/GenQTest.c \
 $(FREERTOS_DIR)/Demo/Common/Minimal/BlockQ.c \
 $(FREERTOS_DIR)/Demo/Common/Minimal/blocktim.c \
 $(FREERTOS_DIR)/Demo/Common/Minimal/QPeek.c \
 $(FREERTOS_DIR)/Demo/Common/Minimal/PollQ.c 
 #$(wildcard ./Libraries/ff/*.c) \
 #$(wildcard ./Libraries/ff/option/cc932.c) \
 #$(wildcard $(FREERTOS_PLUS_DIR)/Source/FreeRTOS-Plus-Trace/*.c)
LIB_OBJS = $(notdir $(LIB_SRCS:.c=.o))

VPATH = $(SRCPATH) $(dir $(LIB_SRCS))

all: main

main: $(addprefix $(OBJDIR)/,$(OBJS)) $(OBJDIR)/startup_stm32f072.o $(OBJDIR)/system_stm32f0xx.o $(OBJDIR)/libstm32f0xx.a
	$(MKBINDIR)
	$(LD) $(LDFLAGS) $(TARGET_ARCH) $^ -o $(BINDIR)/main.elf 
	$(OBJCOPY) -O ihex $(BINDIR)/main.elf $(BINDIR)/main.hex
	$(OBJCOPY) -O binary $(BINDIR)/main.elf $(BINDIR)/main.bin

$(OBJDIR)/%.o : %.c
	$(MKOBJDIR)
	$(CC) $(CFLAGS) $(TARGET_ARCH) -c -o $@ $<

$(OBJDIR)/%.o : %.cpp
	$(MKOBJDIR)
	$(CXX) $(CXXFLAGS) $(TARGET_ARCH) -c -o $@ $<

$(OBJDIR)/libstm32f0xx.a: $(addprefix $(OBJDIR)/,$(LIB_OBJS))
	$(AR) cr $(OBJDIR)/libstm32f0xx.a $^

$(OBJDIR)/startup_stm32f072.o:
	$(AS) -o $(OBJDIR)/startup_stm32f072.o $(ASFLAGS) $(STARTUP_ASM)

$(OBJDIR)/system_stm32f0xx.o: $(SYSTEM_INIT)
	$(AS) -o $(OBJDIR)/system_stm32f0xx.o $(CFLAGS) $(TARGET_ARCH) -c $(SYSTEM_INIT)

clean:
	$(REMOVE)
