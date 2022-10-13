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
	protected:
		int handle = -1;
		
	public:
		~Socket();
		///0	Further receives are disallowed
		///1	Further sends are disallowed
		///2	Further sends and receives are disallowed(like close())
		///		https://beej.us/guide/bgnet/html/#close-and-shutdownget-outta-my-face
		void Shutdown(int how);
		void Close();
		
		
		
		
		
		
	};
	
}
