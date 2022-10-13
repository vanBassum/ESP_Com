#include "tcpclient.h"

#define TAG "TCPClient"




void ESP_Com::TCPClient::SetKeepAlive(int enable, int idle, int interval, int count)
{
	if (handle < 0) return;
	//https://stackoverflow.com/questions/74053375/should-the-values-set-with-setsockopt-stay-valid-during-lifetime-of-the-socket
	// Set tcp keepalive option
	setsockopt(handle, SOL_SOCKET,  SO_KEEPALIVE,  &enable,		sizeof(int));
	setsockopt(handle, IPPROTO_TCP, TCP_KEEPIDLE,  &idle,		sizeof(int));
	setsockopt(handle, IPPROTO_TCP, TCP_KEEPINTVL, &interval,	sizeof(int));
	setsockopt(handle, IPPROTO_TCP, TCP_KEEPCNT,   &count,		sizeof(int));
}

int ESP_Com::TCPClient::Receive(void* buffer, size_t size, int flags /* = 0 */)
{
	if (handle < 0) return 0;
	int result =  recv(handle, buffer, size, flags);
	if (result <= 0)
	{
		Shutdown(0);
		Close();
	}
	return result;
}

int ESP_Com::TCPClient::Send(void* buffer, size_t size, int flags /* = 0 */)
{
	if (handle < 0) return 0;
	size_t toWrite = size;
	while (toWrite > 0) 
	{
		int written = send(handle, buffer, size, flags);
		if (written < 0) 
		{
			ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
			Shutdown(0);
			Close();
			return written;
		}
		toWrite -= written;
	}
	return size;
}

void ESP_Com::TCPClient::Init(int socketHandle)
{
	handle = socketHandle;
}

bool ESP_Com::TCPClient::Init()
{
	if (handle < 0) return false;
	handle = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (handle < 0) 
	{
		ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
		return false;
	}
	return true;
}

bool ESP_Com::TCPClient::Connect(std::string host, int port)
{
	struct sockaddr_in dest_addr;
	inet_pton(AF_INET, host.c_str(), &dest_addr.sin_addr);
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(port);
	int err = connect(handle, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
	if (err != 0) {
		ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
		return false;
	}
	return true;
}




