################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_cache.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_dcdc.c \
../drivers/fsl_gpc.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpi2c.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_pmu.c \
../drivers/fsl_src.c 

C_DEPS += \
./drivers/fsl_cache.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_dcdc.d \
./drivers/fsl_gpc.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpi2c.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_pmu.d \
./drivers/fsl_src.d 

OBJS += \
./drivers/fsl_cache.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_dcdc.o \
./drivers/fsl_gpc.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpi2c.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_pmu.o \
./drivers/fsl_src.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DMCUXPRESSO_SDK -DXIP_BOOT_HEADER_ENABLE=1 -DXIP_EXTERNAL_FLASH=1 -DPRINTF_FLOAT_ENABLE=1 -DPRINTF_ADVANCED_ENABLE=1 -DSDK_I2C_BASED_COMPONENT_USED=1 -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\source" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\xip" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\drivers" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\CMSIS" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\CMSIS\m-profile" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\device" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\device\periph" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\utilities" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\utilities\str" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\utilities\debug_console_lite" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\component\uart" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\accel" -I"C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\board" -O0 -fno-common -g3 -gdwarf-4 -mthumb -c -ffunction-sections -fdata-sections -fno-builtin -imacros "C:\Users\xmartij01\Documents\MCUXpressoIDE_24.12.148\workspace\nxp_embedded_machine_learning_ecompass\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_cache.d ./drivers/fsl_cache.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_dcdc.d ./drivers/fsl_dcdc.o ./drivers/fsl_gpc.d ./drivers/fsl_gpc.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_lpi2c.d ./drivers/fsl_lpi2c.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_pmu.d ./drivers/fsl_pmu.o ./drivers/fsl_src.d ./drivers/fsl_src.o

.PHONY: clean-drivers

