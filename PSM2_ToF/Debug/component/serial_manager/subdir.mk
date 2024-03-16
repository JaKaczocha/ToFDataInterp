################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/serial_manager/fsl_component_serial_manager.c \
../component/serial_manager/fsl_component_serial_port_uart.c 

C_DEPS += \
./component/serial_manager/fsl_component_serial_manager.d \
./component/serial_manager/fsl_component_serial_port_uart.d 

OBJS += \
./component/serial_manager/fsl_component_serial_manager.o \
./component/serial_manager/fsl_component_serial_port_uart.o 


# Each subdirectory must supply rules for building sources it contributes
component/serial_manager/%.o: ../component/serial_manager/%.c component/serial_manager/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\dawid\Documents\MCUXpressoIDE_11.8.1_1197\workspace\PSM2_ToF\drivers" -I"C:\Users\dawid\Documents\MCUXpressoIDE_11.8.1_1197\workspace\PSM2_ToF\device" -I"C:\Users\dawid\Documents\MCUXpressoIDE_11.8.1_1197\workspace\PSM2_ToF\CMSIS" -I"C:\Users\dawid\Documents\MCUXpressoIDE_11.8.1_1197\workspace\PSM2_ToF\utilities" -I"C:\Users\dawid\Documents\MCUXpressoIDE_11.8.1_1197\workspace\PSM2_ToF\component\uart" -I"C:\Users\dawid\Documents\MCUXpressoIDE_11.8.1_1197\workspace\PSM2_ToF\component\serial_manager" -I"C:\Users\dawid\Documents\MCUXpressoIDE_11.8.1_1197\workspace\PSM2_ToF\component\lists" -I"C:\Users\dawid\Documents\MCUXpressoIDE_11.8.1_1197\workspace\PSM2_ToF\board" -I"C:\Users\dawid\Documents\MCUXpressoIDE_11.8.1_1197\workspace\PSM2_ToF\startup" -I"C:\Users\dawid\Documents\MCUXpressoIDE_11.8.1_1197\workspace\PSM2_ToF\source" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-serial_manager

clean-component-2f-serial_manager:
	-$(RM) ./component/serial_manager/fsl_component_serial_manager.d ./component/serial_manager/fsl_component_serial_manager.o ./component/serial_manager/fsl_component_serial_port_uart.d ./component/serial_manager/fsl_component_serial_port_uart.o

.PHONY: clean-component-2f-serial_manager

