#include "socket.h"
#include <stdint.h>

#define ISSET(events, ev)	((uint32_t)events & (uint32_t)ev)

namespace ESP_Com
{
	enum class States : uint8_t
	{
		Initializing,
		
	};
	
	enum class Events : uint32_t	//These are flags!
	{
		Nothing	     = 0,
		StateChanged = (1 << 0),
	};
	
	
	void Socket::Work(Task& task)
	{
		States prvState = States::Initializing;
		States actState = States::Initializing;
		States nxtState = States::Initializing;
		while (true)
		{
			Events events = Events::Nothing;
			task.NotifyWait((uint32_t*)&events, 1000 / portTICK_PERIOD_MS);
			
			
			switch (actState)
			{
			case States::Initializing:
				if ISSET(events, Events::StateChanged)
				{
					//On entry.
					//Cleanup all resources
				}
				break;
				
				
				
				
				
			default:
				break;
				
			}
			
			

			if (actState != nxtState)
			{
				prvState = actState;
				actState = nxtState;
				task.Notify((uint32_t)Events::StateChanged);
			}
		}
	}
}


