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
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
dacube.lss \

FLASH_IMAGE += \
dacube.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: dacube.elf secondary-outputs

# Tool invocations
dacube.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,dacube.map -mmcu=attiny2313 -o "dacube.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

dacube.lss: dacube.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S dacube.elf  >"dacube.lss"
	@echo 'Finished building: $@'
	@echo ' '

dacube.hex: dacube.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex dacube.elf  "dacube.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: dacube.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny2313 dacube.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: dacube.elf
	@echo 'Invoking: AVRDude'
	/usr/bin/avrdude -pt2313 -cstk500v2 -P/dev/ttyUSB0 -Uflash:w:dacube.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(FLASH_IMAGE)$(ELFS)$(LSS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) dacube.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
