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
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: proj_tz_hello_2.axf

# Tool invocations
proj_tz_hello_2.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/takis/Work/git_stuff/ese3025_2/lpc_board_nxp_lpcxpresso_1769/Debug" -L"/home/takis/Work/git_stuff/ese3025_2/lpc_chip_175x_6x/Debug" -Xlinker -Map="proj_tz_hello_2.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "proj_tz_hello_2_Debug.ld" -o "proj_tz_hello_2.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) proj_tz_hello_2.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "proj_tz_hello_2.axf"; # arm-none-eabi-objcopy -v -O binary "proj_tz_hello_2.axf" "proj_tz_hello_2.bin" ; # checksum -p LPC1769 -d "proj_tz_hello_2.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
