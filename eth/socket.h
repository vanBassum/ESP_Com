#pragma once

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "esp_netif.h"
#include "esp_log.h"

#include "esp_base.h"

using namespace ESP_Base;

namespace ESP_Com
{
	
	class Socket
	{
		int handle = -1;
		
	public:
		~Socket();
		///0	Further receives are disallowed
		///1	Further sends are disallowed
		///2	Further sends and receives are disallowed(like close())
		///		https://beej.us/guide/bgnet/html/#close-and-shutdownget-outta-my-face
		void Shutdown(int how);
		void Close();
		
		bool Init(int domain, int type, int protocol);	//	AF_INET, SOCK_STREAM, IPPROTO_IP
		void SetKeepAlive(int enable, int idle, int interval, int count);
		int Receive(void* buffer, size_t size, int flags = 0);
		int Send(void* buffer, size_t size, int flags = 0);
		bool Connect(std::string host, int port);
		bool Bind(int port);
		bool Accept(Socket* client);
		bool Listen(int backlog);
		
		
	};
	
}
