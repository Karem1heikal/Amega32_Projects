################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
TIMER3_test.lss \

FLASH_IMAGE += \
TIMER3_test.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: TIMER3_test.elf secondary-outputs

# Tool invocations
TIMER3_test.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,TIMER3_test.map -mmcu=atmega32 -o "TIMER3_test.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

TIMER3_test.lss: TIMER3_test.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S TIMER3_test.elf  >"TIMER3_test.lss"
	@echo 'Finished building: $@'
	@echo ' '

TIMER3_test.hex: TIMER3_test.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex TIMER3_test.elf  "TIMER3_test.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: TIMER3_test.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 TIMER3_test.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) TIMER3_test.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
