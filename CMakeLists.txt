#Created by VisualGDB. Right-click on the component in Solution Explorer to edit properties using convenient GUI.

idf_component_register( SRCS			esp_com.cpp 
										eth/tcpserver.cpp 
										eth/socket.cpp 
										eth/tcpclient.cpp

						INCLUDE_DIRS	. 
										eth

						REQUIRES		ESP_Base)
