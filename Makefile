TARGET = LuxMeter

BUILD_DIR = build

C_SOURCES = \
src/main.c \
lib/cmsis/system_stm32f0xx.c \
$(wildcard lib/peripherals/*/*.c) \
$(wildcard lib/modules/*/*.c) 

ASM_SOURCES = startup/startup_stm32f030x6.s

PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

CPU = -mcpu=cortex-m0
MCU = $(CPU) -mthumb

C_INCLUDES = \
-Ilib/cmsis \
-Ilib/peripherals \
-Ilib/modules \
-Ilib/peripherals/GPIO \
-Ilib/peripherals/I2C \
-Ilib/peripherals/RCC \
-Ilib/peripherals/SysTick \
-Ilib/modules/BH1750 \
-Ilib/modules/OLED

AS_DEFS = 
C_DEFS = -DSTM32F030x6

OPT = -O0 -g3

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

LDSCRIPT = STM32F030F4Px_FLASH.ld
LIBS = -lc -lm -lnosys 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--gc-sections

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(CP) -O binary $< $@

$(BUILD_DIR):
	mkdir $@

clean:
	rm -rf $(BUILD_DIR)

flash: all
	openocd -f interface/stlink.cfg -f target/stm32f0x.cfg -c "adapter speed 500" -c "program build/LuxMeter.elf verify reset exit"
