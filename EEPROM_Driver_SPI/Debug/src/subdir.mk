################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CLCD_program.c \
../src/DIO_program.c \
../src/EEPROM_program.c \
../src/GINT_program.c \
../src/PORT_program.c \
../src/SPI_program.c \
../src/main.c 

OBJS += \
./src/CLCD_program.o \
./src/DIO_program.o \
./src/EEPROM_program.o \
./src/GINT_program.o \
./src/PORT_program.o \
./src/SPI_program.o \
./src/main.o 

C_DEPS += \
./src/CLCD_program.d \
./src/DIO_program.d \
./src/EEPROM_program.d \
./src/GINT_program.d \
./src/PORT_program.d \
./src/SPI_program.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


