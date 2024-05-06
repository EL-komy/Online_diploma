################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/stm32f103x8_EXTI_driver.c \
../Inc/stm32f103x8_I2C_Drver.c \
../Inc/stm32f103x8_RCC_driver.c \
../Inc/stm32f103x8_SPI_Drver.c \
../Inc/stm32f103x8_USART_driver.c \
../Inc/stm32f103x8_gpio_driver.c 

OBJS += \
./Inc/stm32f103x8_EXTI_driver.o \
./Inc/stm32f103x8_I2C_Drver.o \
./Inc/stm32f103x8_RCC_driver.o \
./Inc/stm32f103x8_SPI_Drver.o \
./Inc/stm32f103x8_USART_driver.o \
./Inc/stm32f103x8_gpio_driver.o 

C_DEPS += \
./Inc/stm32f103x8_EXTI_driver.d \
./Inc/stm32f103x8_I2C_Drver.d \
./Inc/stm32f103x8_RCC_driver.d \
./Inc/stm32f103x8_SPI_Drver.d \
./Inc/stm32f103x8_USART_driver.d \
./Inc/stm32f103x8_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/stm32f103x8_EXTI_driver.o: ../Inc/stm32f103x8_EXTI_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Genius/STM32CubeIDE/workspace_1.4.0/s/MY_RTOS/inc" -I"C:/Users/Genius/STM32CubeIDE/workspace_1.4.0/s/CMSIS_5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/stm32f103x8_EXTI_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Inc/stm32f103x8_I2C_Drver.o: ../Inc/stm32f103x8_I2C_Drver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Genius/STM32CubeIDE/workspace_1.4.0/s/MY_RTOS/inc" -I"C:/Users/Genius/STM32CubeIDE/workspace_1.4.0/s/CMSIS_5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/stm32f103x8_I2C_Drver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Inc/stm32f103x8_RCC_driver.o: ../Inc/stm32f103x8_RCC_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Genius/STM32CubeIDE/workspace_1.4.0/s/MY_RTOS/inc" -I"C:/Users/Genius/STM32CubeIDE/workspace_1.4.0/s/CMSIS_5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/stm32f103x8_RCC_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Inc/stm32f103x8_SPI_Drver.o: ../Inc/stm32f103x8_SPI_Drver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Genius/STM32CubeIDE/workspace_1.4.0/s/MY_RTOS/inc" -I"C:/Users/Genius/STM32CubeIDE/workspace_1.4.0/s/CMSIS_5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/stm32f103x8_SPI_Drver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Inc/stm32f103x8_USART_driver.o: ../Inc/stm32f103x8_USART_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Genius/STM32CubeIDE/workspace_1.4.0/s/MY_RTOS/inc" -I"C:/Users/Genius/STM32CubeIDE/workspace_1.4.0/s/CMSIS_5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/stm32f103x8_USART_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Inc/stm32f103x8_gpio_driver.o: ../Inc/stm32f103x8_gpio_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/Genius/STM32CubeIDE/workspace_1.4.0/s/MY_RTOS/inc" -I"C:/Users/Genius/STM32CubeIDE/workspace_1.4.0/s/CMSIS_5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Inc/stm32f103x8_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

