################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/fsl_adapter_usart.c 

C_DEPS += \
./component/uart/fsl_adapter_usart.d 

OBJS += \
./component/uart/fsl_adapter_usart.o 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c component/uart/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\User\Desktop\toffik\ToF_3D\PSM2_ToF\drivers" -I"C:\Users\User\Desktop\toffik\ToF_3D\PSM2_ToF\device" -I"C:\Users\User\Desktop\toffik\ToF_3D\PSM2_ToF\CMSIS" -I"C:\Users\User\Desktop\toffik\ToF_3D\PSM2_ToF\utilities" -I"C:\Users\User\Desktop\toffik\ToF_3D\PSM2_ToF\component\uart" -I"C:\Users\User\Desktop\toffik\ToF_3D\PSM2_ToF\component\serial_manager" -I"C:\Users\User\Desktop\toffik\ToF_3D\PSM2_ToF\component\lists" -I"C:\Users\User\Desktop\toffik\ToF_3D\PSM2_ToF\board" -I"C:\Users\User\Desktop\toffik\ToF_3D\PSM2_ToF\startup" -I"C:\Users\User\Desktop\toffik\ToF_3D\PSM2_ToF\source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-uart

clean-component-2f-uart:
	-$(RM) ./component/uart/fsl_adapter_usart.d ./component/uart/fsl_adapter_usart.o

.PHONY: clean-component-2f-uart

