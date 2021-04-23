################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc16.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_enet.c \
../drivers/fsl_ftfx_cache.c \
../drivers/fsl_ftfx_controller.c \
../drivers/fsl_ftfx_flash.c \
../drivers/fsl_ftfx_flexnvm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2c.c \
../drivers/fsl_rnga.c \
../drivers/fsl_smc.c \
../drivers/fsl_uart.c 

OBJS += \
./drivers/fsl_adc16.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_enet.o \
./drivers/fsl_ftfx_cache.o \
./drivers/fsl_ftfx_controller.o \
./drivers/fsl_ftfx_flash.o \
./drivers/fsl_ftfx_flexnvm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_rnga.o \
./drivers/fsl_smc.o \
./drivers/fsl_uart.o 

C_DEPS += \
./drivers/fsl_adc16.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_enet.d \
./drivers/fsl_ftfx_cache.d \
./drivers/fsl_ftfx_controller.d \
./drivers/fsl_ftfx_flash.d \
./drivers/fsl_ftfx_flexnvm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_rnga.d \
./drivers/fsl_smc.d \
./drivers/fsl_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\board" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\source" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\template\aws" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\flash\mflash" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\template" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mbedtls\port\ksdk" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\freertos_kernel\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\http_parser" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\template\ARM_CM4F" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\drivers" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\utilities" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\component\serial_manager" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\component\uart" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\serializer\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\src\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\common\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\common\include\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\common\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\demos\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\demos\dev_mode_key_provisioning\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\jsmn" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\mbedtls_utils" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\pkcs11" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\pkcs11\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\freertos\include\platform" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\include\platform" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\freertos\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\secure_sockets\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\pkcs11\mbedtls" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\wifi\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\https\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\https\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\https\src\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\aws\greengrass\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\aws\greengrass\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\crypto\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\pkcs11\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\tls\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\utils\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\src\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\demos\network_manager" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\port" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\src\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mbedtls\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mbedtls\library" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mmcau" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mdio" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\phy" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\component\lists" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\flash\mflash\frdmk64f" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\CMSIS" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


