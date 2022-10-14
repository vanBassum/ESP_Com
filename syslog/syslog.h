#pragma once
#include "esp_base.h"
#include "../eth/socket.h"
#include "message.h"
#include <cstdio>
#include <cstdarg>
#include <vector>

using namespace ESP_Base;

namespace ESP_Com
{
	
	namespace Syslog
	{
		class Client
		{
			Endpoint ep ;
			Socket listener ;
			
		public :

		    void Init(std::string host, int port = 514)
			{
				ep.Set(host, port);
				listener.InitUDP();
			}

			void Send(Message message)
			{
				std::string raw = message.ToString();
				listener.SendTo(ep, raw.c_str(), raw.length());
				
			}
			
			
			
			
		};
		
	}
}
