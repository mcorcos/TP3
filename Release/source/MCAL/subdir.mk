################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/MCAL/IRQ.c \
../source/MCAL/gpio.c 

OBJS += \
./source/MCAL/IRQ.o \
./source/MCAL/gpio.o 

C_DEPS += \
./source/MCAL/IRQ.d \
./source/MCAL/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
source/MCAL/%.o: ../source/MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -D__USE_CMSIS -DNDEBUG -I../source -I../ -I../CMSIS -I../startup -Os -fno-common -g -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


