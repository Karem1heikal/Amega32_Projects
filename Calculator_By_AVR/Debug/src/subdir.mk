################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CLCD_program.c \
../src/DIO_program.c \
../src/KPD_program.c \
../src/LED_program.c \
../src/PORT_program.c \
../src/SSD_program.c \
../src/SW_program.c \
../src/main.c 

OBJS += \
./src/CLCD_program.o \
./src/DIO_program.o \
./src/KPD_program.o \
./src/LED_program.o \
./src/PORT_program.o \
./src/SSD_program.o \
./src/SW_program.o \
./src/main.o 

C_DEPS += \
./src/CLCD_program.d \
./src/DIO_program.d \
./src/KPD_program.d \
./src/LED_program.d \
./src/PORT_program.d \
./src/SSD_program.d \
./src/SW_program.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


