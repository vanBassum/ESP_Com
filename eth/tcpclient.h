#pragma once

#include "esp_base.h"
#include "socket.h"

using namespace ESP_Base;

namespace ESP_Com
{

	class TCPClient : public Socket
	{
		void Cleanup();

	public:
		bool Init();
		void Init(int socketHandle);
		void SetKeepAlive(int enable, int idle, int interval, int count);
		int Receive(void* buffer, size_t size, int flags = 0);
		int Send(void* buffer, size_t size, int flags = 0);
		bool Connect(std::string host, int port);
	};
	
}
