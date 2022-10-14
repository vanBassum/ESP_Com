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
	class Socket;
	class Endpoint
	{
		struct sockaddr_storage addr; // Large enough for both IPv4 or IPv6
		
	public:
		
		socklen_t Size()
		{
			return sizeof(addr);
		}
		
		struct sockaddr* GetSockAddr()
		{
			return (struct sockaddr *)&addr;
		}
		
		void Set(int port)
		{
			struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&addr;
			dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
			dest_addr_ip4->sin_family = AF_INET;
			dest_addr_ip4->sin_port = htons(port);
		}

		void Set(std::string host, int port)
		{			
			struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&addr;
			dest_addr_ip4->sin_addr.s_addr = inet_addr(host.c_str());
			dest_addr_ip4->sin_family = AF_INET;
			dest_addr_ip4->sin_port = htons(port);
		}
	};
	
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
		bool InitTCP() { return Init(AF_INET, SOCK_STREAM, IPPROTO_IP); };
		bool InitUDP() { return Init(AF_INET, SOCK_DGRAM, IPPROTO_IP); };
		void SetKeepAlive(int enable, int idle, int interval, int count);
		void SetTimeout(TimeSpan timespan);
		int Receive(void* buffer, size_t size, int flags = 0);
		int Send(const void* buffer, size_t size, int flags = 0);
		int SendTo(Endpoint endpoint, const void* buffer, size_t size, int flags = 0);
		bool Connect(Endpoint endpoint);
		bool Bind(Endpoint endpoint);
		bool Accept(Socket* client);
		bool Listen(int backlog);
	};
	
}
