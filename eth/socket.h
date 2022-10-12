#pragma once
#include "esp_base.h"

using namespace ESP_Base;

namespace ESP_Com
{
	
	class Socket
	{
		Task task;
		void Work(Task& task);
		
	public:
		
		Socket()
		{
			task.Bind(this, &Socket::Work);
		}
		
		~Socket()
		{
			
		}
		
		void Init(std::string name, portBASE_TYPE priority, portSHORT stackDepth)
		{
			task.Init(name, priority, stackDepth);
		}
		
		
		
	};
	
}
