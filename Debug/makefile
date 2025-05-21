################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include xip/subdir.mk
-include utilities/str/subdir.mk
-include utilities/debug_console_lite/subdir.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include board/subdir.mk
-include accel/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := nxp_embedded_machine_learning_ecompass
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: nxp_embedded_machine_learning_ecompass.axf

# Tool invocations
nxp_embedded_machine_learning_ecompass.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\source\lib" -Xlinker -no-warn-rwx-segments -Xlinker -Map="nxp_embedded_machine_learning_ecompass.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -T nxp_embedded_machine_learning_ecompass_Debug.ld -o "nxp_embedded_machine_learning_ecompass.axf" $(OBJS) $(USER_OBJS) $(LIBS) -Wl,--start-group -ltss -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) nxp_embedded_machine_learning_ecompass.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "nxp_embedded_machine_learning_ecompass.axf"; # arm-none-eabi-objcopy -v -O binary "nxp_embedded_machine_learning_ecompass.axf" "nxp_embedded_machine_learning_ecompass.bin" ; # checksum -p MIMXRT1052xxxxB -d "nxp_embedded_machine_learning_ecompass.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
