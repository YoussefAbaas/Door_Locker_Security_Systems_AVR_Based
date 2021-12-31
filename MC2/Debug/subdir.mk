################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../DcMotor.c \
../Timer.c \
../external_eeprom.c \
../gpio.c \
../i2c.c \
../lcd.c \
../main.c \
../uart.c 

OBJS += \
./Buzzer.o \
./DcMotor.o \
./Timer.o \
./external_eeprom.o \
./gpio.o \
./i2c.o \
./lcd.o \
./main.o \
./uart.o 

C_DEPS += \
./Buzzer.d \
./DcMotor.d \
./Timer.d \
./external_eeprom.d \
./gpio.d \
./i2c.d \
./lcd.d \
./main.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


