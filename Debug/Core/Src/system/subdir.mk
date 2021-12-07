################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/system/cBufferHandler.c \
../Core/Src/system/comm.c \
../Core/Src/system/outputPwmController.c \
../Core/Src/system/pidConroller.c 

OBJS += \
./Core/Src/system/cBufferHandler.o \
./Core/Src/system/comm.o \
./Core/Src/system/outputPwmController.o \
./Core/Src/system/pidConroller.o 

C_DEPS += \
./Core/Src/system/cBufferHandler.d \
./Core/Src/system/comm.d \
./Core/Src/system/outputPwmController.d \
./Core/Src/system/pidConroller.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/system/%.o: ../Core/Src/system/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F334x8 -I"C:/Users/usuario/Documents/Controlador_platina/Controlador_Platina/Controlador_Platina/Core/Inc" -I"C:/Users/usuario/Documents/Controlador_platina/Controlador_Platina/Controlador_Platina/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Users/usuario/Documents/Controlador_platina/Controlador_Platina/Controlador_Platina/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Users/usuario/Documents/Controlador_platina/Controlador_Platina/Controlador_Platina/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Users/usuario/Documents/Controlador_platina/Controlador_Platina/Controlador_Platina/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


