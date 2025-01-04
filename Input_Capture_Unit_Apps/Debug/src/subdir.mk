################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADC_program.c \
../src/CLCD_program.c \
../src/DAC_program.c \
../src/DIO_program.c \
../src/EXTI_program.c \
../src/GIE_program.c \
../src/KPD_program.c \
../src/LED_program.c \
../src/PORT_program.c \
../src/SERVO_program.c \
../src/SSD_program.c \
../src/STEP_MOTOR_program.c \
../src/SW_program.c \
../src/TIMER_program.c \
../src/WDT_program.c \
../src/main.c 

OBJS += \
./src/ADC_program.o \
./src/CLCD_program.o \
./src/DAC_program.o \
./src/DIO_program.o \
./src/EXTI_program.o \
./src/GIE_program.o \
./src/KPD_program.o \
./src/LED_program.o \
./src/PORT_program.o \
./src/SERVO_program.o \
./src/SSD_program.o \
./src/STEP_MOTOR_program.o \
./src/SW_program.o \
./src/TIMER_program.o \
./src/WDT_program.o \
./src/main.o 

C_DEPS += \
./src/ADC_program.d \
./src/CLCD_program.d \
./src/DAC_program.d \
./src/DIO_program.d \
./src/EXTI_program.d \
./src/GIE_program.d \
./src/KPD_program.d \
./src/LED_program.d \
./src/PORT_program.d \
./src/SERVO_program.d \
./src/SSD_program.d \
./src/STEP_MOTOR_program.d \
./src/SW_program.d \
./src/TIMER_program.d \
./src/WDT_program.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


