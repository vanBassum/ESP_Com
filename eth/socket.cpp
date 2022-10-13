#include "socket.h"



ESP_Com::Socket::~Socket()
{
	if (handle < 0) return;
	Close();
}


void ESP_Com::Socket::Shutdown(int how)
{
	if (handle < 0) return;
	shutdown(handle, how);
}


void ESP_Com::Socket::Close()
{
	if (handle < 0) return;
	close(handle);
	handle = -1;
}
