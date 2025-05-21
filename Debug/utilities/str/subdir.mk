################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/str/fsl_str.c 

C_DEPS += \
./utilities/str/fsl_str.d 

OBJS += \
./utilities/str/fsl_str.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/str/%.o: ../utilities/str/%.c utilities/str/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DMCUXPRESSO_SDK -DXIP_BOOT_HEADER_ENABLE=1 -DXIP_EXTERNAL_FLASH=1 -DPRINTF_FLOAT_ENABLE=1 -DPRINTF_ADVANCED_ENABLE=1 -DSDK_I2C_BASED_COMPONENT_USED=1 -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\source" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\xip" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\drivers" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\CMSIS" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\CMSIS\m-profile" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\device" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\device\periph" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\utilities" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\utilities\str" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\utilities\debug_console_lite" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\component\uart" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\accel" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\board" -O0 -fno-common -g3 -gdwarf-4 -mthumb -c -ffunction-sections -fdata-sections -fno-builtin -imacros "C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities-2f-str

clean-utilities-2f-str:
	-$(RM) ./utilities/str/fsl_str.d ./utilities/str/fsl_str.o

.PHONY: clean-utilities-2f-str

