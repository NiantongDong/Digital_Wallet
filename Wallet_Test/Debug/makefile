################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include phy/subdir.mk
-include mmcau/subdir.mk
-include mbedtls/port/ksdk/subdir.mk
-include mbedtls/library/subdir.mk
-include lwip/src/netif/ppp/subdir.mk
-include lwip/src/netif/subdir.mk
-include lwip/src/core/ipv6/subdir.mk
-include lwip/src/core/ipv4/subdir.mk
-include lwip/src/core/subdir.mk
-include lwip/src/api/subdir.mk
-include lwip/port/subdir.mk
-include freertos/vendors/nxp/secure_sockets/lwip/subdir.mk
-include freertos/vendors/nxp/pkcs11/common/subdir.mk
-include freertos/libraries/freertos_plus/standard/utils/src/subdir.mk
-include freertos/libraries/freertos_plus/standard/tls/src/subdir.mk
-include freertos/libraries/freertos_plus/standard/pkcs11/src/subdir.mk
-include freertos/libraries/freertos_plus/standard/crypto/src/subdir.mk
-include freertos/libraries/freertos_plus/aws/greengrass/src/subdir.mk
-include freertos/libraries/c_sdk/standard/serializer/src/json/subdir.mk
-include freertos/libraries/c_sdk/standard/serializer/src/subdir.mk
-include freertos/libraries/c_sdk/standard/mqtt/src/subdir.mk
-include freertos/libraries/c_sdk/standard/https/src/subdir.mk
-include freertos/libraries/c_sdk/standard/common/taskpool/subdir.mk
-include freertos/libraries/c_sdk/standard/common/logging/subdir.mk
-include freertos/libraries/c_sdk/standard/common/subdir.mk
-include freertos/libraries/c_sdk/aws/shadow/src/subdir.mk
-include freertos/libraries/abstractions/platform/freertos/subdir.mk
-include freertos/libraries/abstractions/pkcs11/mbedtls/subdir.mk
-include freertos/libraries/3rdparty/mbedtls_utils/subdir.mk
-include freertos/libraries/3rdparty/jsmn/subdir.mk
-include freertos/libraries/3rdparty/http_parser/subdir.mk
-include freertos/freertos_kernel/portable/MemMang/subdir.mk
-include freertos/freertos_kernel/portable/GCC/ARM_CM4F/subdir.mk
-include freertos/freertos_kernel/subdir.mk
-include freertos/demos/network_manager/subdir.mk
-include freertos/demos/dev_mode_key_provisioning/src/subdir.mk
-include freertos/demos/demo_runner/subdir.mk
-include flash/mflash/frdmk64f/subdir.mk
-include flash/mflash/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Wallet_Test.axf

# Tool invocations
Wallet_Test.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\bkute\Documents\MCUXpressoIDE_11.3.0_5222\workspace\Wallet_Test\mmcau\asm-cm4-cm7" -Xlinker -Map="Wallet_Test.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T Wallet_Test_Debug.ld -o "Wallet_Test.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Wallet_Test.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Wallet_Test.axf"; # arm-none-eabi-objcopy -v -O binary "Wallet_Test.axf" "Wallet_Test.bin" ; # checksum -p MK64FN1M0xxx12 -d "Wallet_Test.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
