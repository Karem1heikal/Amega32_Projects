################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADC_program.c \
../src/CLCD_program.c \
../src/DIO_program.c \
../src/PORT_program.c \
../src/main.c 

OBJS += \
./src/ADC_program.o \
./src/CLCD_program.o \
./src/DIO_program.o \
./src/PORT_program.o \
./src/main.o 

C_DEPS += \
./src/ADC_program.d \
./src/CLCD_program.d \
./src/DIO_program.d \
./src/PORT_program.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


