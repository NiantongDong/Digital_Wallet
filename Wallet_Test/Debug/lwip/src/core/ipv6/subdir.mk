################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/core/ipv6/dhcp6.c \
../lwip/src/core/ipv6/ethip6.c \
../lwip/src/core/ipv6/icmp6.c \
../lwip/src/core/ipv6/inet6.c \
../lwip/src/core/ipv6/ip6.c \
../lwip/src/core/ipv6/ip6_addr.c \
../lwip/src/core/ipv6/ip6_frag.c \
../lwip/src/core/ipv6/mld6.c \
../lwip/src/core/ipv6/nd6.c 

OBJS += \
./lwip/src/core/ipv6/dhcp6.o \
./lwip/src/core/ipv6/ethip6.o \
./lwip/src/core/ipv6/icmp6.o \
./lwip/src/core/ipv6/inet6.o \
./lwip/src/core/ipv6/ip6.o \
./lwip/src/core/ipv6/ip6_addr.o \
./lwip/src/core/ipv6/ip6_frag.o \
./lwip/src/core/ipv6/mld6.o \
./lwip/src/core/ipv6/nd6.o 

C_DEPS += \
./lwip/src/core/ipv6/dhcp6.d \
./lwip/src/core/ipv6/ethip6.d \
./lwip/src/core/ipv6/icmp6.d \
./lwip/src/core/ipv6/inet6.d \
./lwip/src/core/ipv6/ip6.d \
./lwip/src/core/ipv6/ip6_addr.d \
./lwip/src/core/ipv6/ip6_frag.d \
./lwip/src/core/ipv6/mld6.d \
./lwip/src/core/ipv6/nd6.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/core/ipv6/%.o: ../lwip/src/core/ipv6/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\board" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\source" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\template\aws" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\flash\mflash" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\template" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mbedtls\port\ksdk" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\freertos_kernel\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\http_parser" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\template\ARM_CM4F" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\drivers" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\utilities" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\component\serial_manager" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\component\uart" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\serializer\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\src\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\common\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\common\include\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\common\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\demos\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\demos\dev_mode_key_provisioning\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\jsmn" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\mbedtls_utils" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\pkcs11" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\pkcs11\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\freertos\include\platform" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\include\platform" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\freertos\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\secure_sockets\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\pkcs11\mbedtls" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\wifi\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\https\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\https\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\https\src\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\aws\greengrass\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\aws\greengrass\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\crypto\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\pkcs11\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\tls\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\utils\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\src\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\demos\network_manager" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\port" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\src\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mbedtls\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mbedtls\library" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mmcau" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mdio" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\phy" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\component\lists" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\flash\mflash\frdmk64f" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\CMSIS" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

