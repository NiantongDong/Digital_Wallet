################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/core/altcp.c \
../lwip/src/core/altcp_alloc.c \
../lwip/src/core/altcp_tcp.c \
../lwip/src/core/def.c \
../lwip/src/core/dns.c \
../lwip/src/core/inet_chksum.c \
../lwip/src/core/init.c \
../lwip/src/core/ip.c \
../lwip/src/core/mem.c \
../lwip/src/core/memp.c \
../lwip/src/core/netif.c \
../lwip/src/core/pbuf.c \
../lwip/src/core/raw.c \
../lwip/src/core/stats.c \
../lwip/src/core/sys.c \
../lwip/src/core/tcp.c \
../lwip/src/core/tcp_in.c \
../lwip/src/core/tcp_out.c \
../lwip/src/core/timeouts.c \
../lwip/src/core/udp.c 

OBJS += \
./lwip/src/core/altcp.o \
./lwip/src/core/altcp_alloc.o \
./lwip/src/core/altcp_tcp.o \
./lwip/src/core/def.o \
./lwip/src/core/dns.o \
./lwip/src/core/inet_chksum.o \
./lwip/src/core/init.o \
./lwip/src/core/ip.o \
./lwip/src/core/mem.o \
./lwip/src/core/memp.o \
./lwip/src/core/netif.o \
./lwip/src/core/pbuf.o \
./lwip/src/core/raw.o \
./lwip/src/core/stats.o \
./lwip/src/core/sys.o \
./lwip/src/core/tcp.o \
./lwip/src/core/tcp_in.o \
./lwip/src/core/tcp_out.o \
./lwip/src/core/timeouts.o \
./lwip/src/core/udp.o 

C_DEPS += \
./lwip/src/core/altcp.d \
./lwip/src/core/altcp_alloc.d \
./lwip/src/core/altcp_tcp.d \
./lwip/src/core/def.d \
./lwip/src/core/dns.d \
./lwip/src/core/inet_chksum.d \
./lwip/src/core/init.d \
./lwip/src/core/ip.d \
./lwip/src/core/mem.d \
./lwip/src/core/memp.d \
./lwip/src/core/netif.d \
./lwip/src/core/pbuf.d \
./lwip/src/core/raw.d \
./lwip/src/core/stats.d \
./lwip/src/core/sys.d \
./lwip/src/core/tcp.d \
./lwip/src/core/tcp_in.d \
./lwip/src/core/tcp_out.d \
./lwip/src/core/timeouts.d \
./lwip/src/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/core/%.o: ../lwip/src/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\board" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\source" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\template\aws" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\flash\mflash" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\template" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mbedtls\port\ksdk" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\freertos_kernel\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\http_parser" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\template\ARM_CM4F" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\drivers" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\utilities" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\component\serial_manager" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\component\uart" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\serializer\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\src\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\common\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\common\include\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\common\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\demos\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\demos\dev_mode_key_provisioning\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\jsmn" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\mbedtls_utils" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\pkcs11" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\pkcs11\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\freertos\include\platform" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\include\platform" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\freertos\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\secure_sockets\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\pkcs11\mbedtls" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\wifi\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\https\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\https\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\https\src\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\aws\greengrass\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\aws\greengrass\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\crypto\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\pkcs11\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\tls\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\utils\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\src\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\demos\network_manager" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\port" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\src\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mbedtls\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mbedtls\library" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mmcau" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mdio" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\phy" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\component\lists" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\flash\mflash\frdmk64f" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\CMSIS" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


