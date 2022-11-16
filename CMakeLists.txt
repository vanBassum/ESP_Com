#Created by VisualGDB. Right-click on the component in Solution Explorer to edit properties using convenient GUI.

idf_component_register(
										SRCS esp_com.cpp eth/socket.cpp spi/bus.cpp spi/device.cpp
										INCLUDE_DIRS . eth syslog spi
										REQUIRES ESP_Base)
