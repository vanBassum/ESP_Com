#include "device.h"

esp_err_t ESP_Com::SPIDevice::Init(SPIBus& bus, spi_device_interface_config_t* config)
{
	return spi_bus_add_device(bus._host, config, &handle);
}



esp_err_t ESP_Com::SPIDevice::PollingTransmit(spi_transaction_t* transaction)
{
	return spi_device_polling_transmit(handle, transaction);  	//Transmit!
}