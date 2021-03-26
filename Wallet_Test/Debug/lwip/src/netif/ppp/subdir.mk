################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/netif/ppp/auth.c \
../lwip/src/netif/ppp/ccp.c \
../lwip/src/netif/ppp/chap-md5.c \
../lwip/src/netif/ppp/chap-new.c \
../lwip/src/netif/ppp/chap_ms.c \
../lwip/src/netif/ppp/demand.c \
../lwip/src/netif/ppp/eap.c \
../lwip/src/netif/ppp/eui64.c \
../lwip/src/netif/ppp/fsm.c \
../lwip/src/netif/ppp/ipcp.c \
../lwip/src/netif/ppp/ipv6cp.c \
../lwip/src/netif/ppp/lcp.c \
../lwip/src/netif/ppp/lwip_ecp.c \
../lwip/src/netif/ppp/magic.c \
../lwip/src/netif/ppp/mppe.c \
../lwip/src/netif/ppp/multilink.c \
../lwip/src/netif/ppp/ppp.c \
../lwip/src/netif/ppp/pppapi.c \
../lwip/src/netif/ppp/pppcrypt.c \
../lwip/src/netif/ppp/pppoe.c \
../lwip/src/netif/ppp/pppol2tp.c \
../lwip/src/netif/ppp/pppos.c \
../lwip/src/netif/ppp/upap.c \
../lwip/src/netif/ppp/utils.c \
../lwip/src/netif/ppp/vj.c 

OBJS += \
./lwip/src/netif/ppp/auth.o \
./lwip/src/netif/ppp/ccp.o \
./lwip/src/netif/ppp/chap-md5.o \
./lwip/src/netif/ppp/chap-new.o \
./lwip/src/netif/ppp/chap_ms.o \
./lwip/src/netif/ppp/demand.o \
./lwip/src/netif/ppp/eap.o \
./lwip/src/netif/ppp/eui64.o \
./lwip/src/netif/ppp/fsm.o \
./lwip/src/netif/ppp/ipcp.o \
./lwip/src/netif/ppp/ipv6cp.o \
./lwip/src/netif/ppp/lcp.o \
./lwip/src/netif/ppp/lwip_ecp.o \
./lwip/src/netif/ppp/magic.o \
./lwip/src/netif/ppp/mppe.o \
./lwip/src/netif/ppp/multilink.o \
./lwip/src/netif/ppp/ppp.o \
./lwip/src/netif/ppp/pppapi.o \
./lwip/src/netif/ppp/pppcrypt.o \
./lwip/src/netif/ppp/pppoe.o \
./lwip/src/netif/ppp/pppol2tp.o \
./lwip/src/netif/ppp/pppos.o \
./lwip/src/netif/ppp/upap.o \
./lwip/src/netif/ppp/utils.o \
./lwip/src/netif/ppp/vj.o 

C_DEPS += \
./lwip/src/netif/ppp/auth.d \
./lwip/src/netif/ppp/ccp.d \
./lwip/src/netif/ppp/chap-md5.d \
./lwip/src/netif/ppp/chap-new.d \
./lwip/src/netif/ppp/chap_ms.d \
./lwip/src/netif/ppp/demand.d \
./lwip/src/netif/ppp/eap.d \
./lwip/src/netif/ppp/eui64.d \
./lwip/src/netif/ppp/fsm.d \
./lwip/src/netif/ppp/ipcp.d \
./lwip/src/netif/ppp/ipv6cp.d \
./lwip/src/netif/ppp/lcp.d \
./lwip/src/netif/ppp/lwip_ecp.d \
./lwip/src/netif/ppp/magic.d \
./lwip/src/netif/ppp/mppe.d \
./lwip/src/netif/ppp/multilink.d \
./lwip/src/netif/ppp/ppp.d \
./lwip/src/netif/ppp/pppapi.d \
./lwip/src/netif/ppp/pppcrypt.d \
./lwip/src/netif/ppp/pppoe.d \
./lwip/src/netif/ppp/pppol2tp.d \
./lwip/src/netif/ppp/pppos.d \
./lwip/src/netif/ppp/upap.d \
./lwip/src/netif/ppp/utils.d \
./lwip/src/netif/ppp/vj.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/netif/ppp/%.o: ../lwip/src/netif/ppp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\board" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\source" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\template\aws" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\flash\mflash" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\template" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mbedtls\port\ksdk" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\freertos_kernel\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\http_parser" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\template\ARM_CM4F" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\drivers" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\utilities" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\component\serial_manager" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\component\uart" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\serializer\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\aws\shadow\src\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\common\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\common\include\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\common\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\demos\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\demos\dev_mode_key_provisioning\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\jsmn" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\mbedtls_utils" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\3rdparty\pkcs11" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\pkcs11\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\freertos\include\platform" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\include\platform" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\freertos\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\platform\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\secure_sockets\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\pkcs11\mbedtls" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\abstractions\wifi\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\https\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\https\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\https\src\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\aws\greengrass\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\aws\greengrass\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\crypto\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\pkcs11\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\tls\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\freertos_plus\standard\utils\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\include\types" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\src\private" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\libraries\c_sdk\standard\mqtt\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\freertos\demos\network_manager" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\port" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\src" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\lwip\src\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mbedtls\include" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mbedtls\library" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mmcau" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mdio" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\phy" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\component\lists" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\flash\mflash\frdmk64f" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\CMSIS" -I"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


