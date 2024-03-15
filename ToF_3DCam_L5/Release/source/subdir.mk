################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ToF_3DCam.c \
../source/platform.c \
../source/semihost_hardfault.c \
../source/vl53l5cx_api.c 

C_DEPS += \
./source/ToF_3DCam.d \
./source/platform.d \
./source/semihost_hardfault.d \
./source/vl53l5cx_api.d 

OBJS += \
./source/ToF_3DCam.o \
./source/platform.o \
./source/semihost_hardfault.o \
./source/vl53l5cx_api.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/drivers" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/device" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/CMSIS" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/utilities" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/component/uart" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/component/serial_manager" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/component/lists" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/board" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/startup" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/drivers" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/device" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/CMSIS" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/utilities" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/component/uart" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/component/serial_manager" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/component/lists" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/board" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/startup" -I"/Users/daniel/Documents/MCUXpressoIDE_11.7.0_9198/workspace/ToF_3DCam_L5/source" -Os -fno-common -g -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/ToF_3DCam.d ./source/ToF_3DCam.o ./source/platform.d ./source/platform.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/vl53l5cx_api.d ./source/vl53l5cx_api.o

.PHONY: clean-source

