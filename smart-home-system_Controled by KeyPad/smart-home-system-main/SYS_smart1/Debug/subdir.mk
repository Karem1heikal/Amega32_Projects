################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../CLCD_program.c \
../DIO_program.c \
../GINT_program.c \
../KPD_program.c \
../PORT_program.c \
../main.c \
../smartAPP.c 

OBJS += \
./ADC_program.o \
./CLCD_program.o \
./DIO_program.o \
./GINT_program.o \
./KPD_program.o \
./PORT_program.o \
./main.o \
./smartAPP.o 

C_DEPS += \
./ADC_program.d \
./CLCD_program.d \
./DIO_program.d \
./GINT_program.d \
./KPD_program.d \
./PORT_program.d \
./main.d \
./smartAPP.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


