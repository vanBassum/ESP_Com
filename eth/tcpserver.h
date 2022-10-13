#pragma once

#include "esp_base.h"
#include "socket.h"
#include "tcpclient.h"


using namespace ESP_Base;

namespace ESP_Com
{
	
	class TCPServer : public Socket
	{
	public:
		bool Init();
		bool Bind(int port);
		bool Accept(TCPClient* client);
		bool Listen(int backlog);
			
	};
	
}
