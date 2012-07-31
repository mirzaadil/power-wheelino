################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
MEGA2560_SerialRead.lss \

FLASH_IMAGE += \
MEGA2560_SerialRead.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: MEGA2560_SerialRead.elf secondary-outputs

# Tool invocations
MEGA2560_SerialRead.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-gcc --cref -s -Os -o"MEGA2560_SerialRead.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lm -Wl,-Map,MEGA2560_SerialRead.map,--cref -Wl,--gc-sections -L"/home/kranzrm/workspace/MEGA2560_SerialRead" -mmcu=atmega2560
	@echo 'Finished building target: $@'
	@echo ' '

MEGA2560_SerialRead.lss: MEGA2560_SerialRead.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S MEGA2560_SerialRead.elf  >"MEGA2560_SerialRead.lss"
	@echo 'Finished building: $@'
	@echo ' '

MEGA2560_SerialRead.hex: MEGA2560_SerialRead.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex MEGA2560_SerialRead.elf  "MEGA2560_SerialRead.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: MEGA2560_SerialRead.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega2560 MEGA2560_SerialRead.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) MEGA2560_SerialRead.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
