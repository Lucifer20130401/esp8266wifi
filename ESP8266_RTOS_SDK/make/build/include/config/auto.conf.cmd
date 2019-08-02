deps_config := \
	/root/github/esp/ESP8266_RTOS_SDK/components/app_update/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/aws_iot/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/console/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/esp8266/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/esp_http_client/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/esp_http_server/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/freertos/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/libsodium/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/log/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/lwip/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/mdns/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/mqtt/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/newlib/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/pthread/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/spiffs/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/ssl/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/tcpip_adapter/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/util/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/vfs/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/wifi_provisioning/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/wpa_supplicant/Kconfig \
	/root/github/esp/ESP8266_RTOS_SDK/components/bootloader/Kconfig.projbuild \
	/root/github/esp/ESP8266_RTOS_SDK/components/esptool_py/Kconfig.projbuild \
	/root/github/esp/ESP8266_RTOS_SDK/components/partition_table/Kconfig.projbuild \
	/root/github/esp/ESP8266_RTOS_SDK/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
