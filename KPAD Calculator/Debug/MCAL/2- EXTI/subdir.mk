################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/2-\ EXTI/EXTI_Program.c 

OBJS += \
./MCAL/2-\ EXTI/EXTI_Program.o 

C_DEPS += \
./MCAL/2-\ EXTI/EXTI_Program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/2-\ EXTI/EXTI_Program.o: ../MCAL/2-\ EXTI/EXTI_Program.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"MCAL/2- EXTI/EXTI_Program.d" -MT"MCAL/2-\ EXTI/EXTI_Program.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


