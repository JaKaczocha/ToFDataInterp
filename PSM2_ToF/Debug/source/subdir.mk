################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/PSM2_ToF.c \
../source/colorConverter.c \
../source/interpolation.c \
../source/lcd.c \
../source/platform.c \
../source/semihost_hardfault.c \
../source/vl53l5cx_api.c 

C_DEPS += \
./source/PSM2_ToF.d \
./source/colorConverter.d \
./source/interpolation.d \
./source/lcd.d \
./source/platform.d \
./source/semihost_hardfault.d \
./source/vl53l5cx_api.d 

OBJS += \
./source/PSM2_ToF.o \
./source/colorConverter.o \
./source/interpolation.o \
./source/lcd.o \
./source/platform.o \
./source/semihost_hardfault.o \
./source/vl53l5cx_api.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\User\Desktop\toff\ToF_3D\PSM2_ToF\drivers" -I"C:\Users\User\Desktop\toff\ToF_3D\PSM2_ToF\device" -I"C:\Users\User\Desktop\toff\ToF_3D\PSM2_ToF\CMSIS" -I"C:\Users\User\Desktop\toff\ToF_3D\PSM2_ToF\utilities" -I"C:\Users\User\Desktop\toff\ToF_3D\PSM2_ToF\component\uart" -I"C:\Users\User\Desktop\toff\ToF_3D\PSM2_ToF\component\serial_manager" -I"C:\Users\User\Desktop\toff\ToF_3D\PSM2_ToF\component\lists" -I"C:\Users\User\Desktop\toff\ToF_3D\PSM2_ToF\board" -I"C:\Users\User\Desktop\toff\ToF_3D\PSM2_ToF\startup" -I"C:\Users\User\Desktop\toff\ToF_3D\PSM2_ToF\source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/PSM2_ToF.d ./source/PSM2_ToF.o ./source/colorConverter.d ./source/colorConverter.o ./source/interpolation.d ./source/interpolation.o ./source/lcd.d ./source/lcd.o ./source/platform.d ./source/platform.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/vl53l5cx_api.d ./source/vl53l5cx_api.o

.PHONY: clean-source

