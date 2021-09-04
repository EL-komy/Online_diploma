################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32\ f103c6\ Drivers/Keypad/keypad.c 

OBJS += \
./stm32\ f103c6\ Drivers/Keypad/keypad.o 

C_DEPS += \
./stm32\ f103c6\ Drivers/Keypad/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
stm32\ f103c6\ Drivers/Keypad/keypad.o: ../stm32\ f103c6\ Drivers/Keypad/keypad.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"F:/all/unit 7/lesson3/section/lab/Drivers/stm32 f103c6 Drivers/Keypad" -I"F:/all/unit 7/lesson3/section/lab/Drivers/stm32 f103c6 Drivers/inc" -I"F:/all/unit 7/lesson3/section/lab/Drivers/stm32 f103c6 Drivers/lcd_driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32 f103c6 Drivers/Keypad/keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

