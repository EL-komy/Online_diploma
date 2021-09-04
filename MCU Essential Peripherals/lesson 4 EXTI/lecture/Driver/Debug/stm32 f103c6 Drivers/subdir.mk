################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32\ f103c6\ Drivers/stm32\ f103c6_EXTI_driver.c \
../stm32\ f103c6\ Drivers/stm32\ f103c6_gpio_driver.c 

OBJS += \
./stm32\ f103c6\ Drivers/stm32\ f103c6_EXTI_driver.o \
./stm32\ f103c6\ Drivers/stm32\ f103c6_gpio_driver.o 

C_DEPS += \
./stm32\ f103c6\ Drivers/stm32\ f103c6_EXTI_driver.d \
./stm32\ f103c6\ Drivers/stm32\ f103c6_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
stm32\ f103c6\ Drivers/stm32\ f103c6_EXTI_driver.o: ../stm32\ f103c6\ Drivers/stm32\ f103c6_EXTI_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Mohamed_ELkomy/embeded_c/unit7/lesson3/Driver/HAL/include" -I"C:/Users/Mohamed_ELkomy/embeded_c/unit7/lesson3/Driver/stm32 f103c6 Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32 f103c6 Drivers/stm32 f103c6_EXTI_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32\ f103c6\ Drivers/stm32\ f103c6_gpio_driver.o: ../stm32\ f103c6\ Drivers/stm32\ f103c6_gpio_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Mohamed_ELkomy/embeded_c/unit7/lesson3/Driver/HAL/include" -I"C:/Users/Mohamed_ELkomy/embeded_c/unit7/lesson3/Driver/stm32 f103c6 Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32 f103c6 Drivers/stm32 f103c6_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

