#include "tcpserver.h"

#define TAG	"TCPServer"

using namespace ESP_Com;

//https://github.com/espressif/esp-idf/blob/ac315adc2c76309b8b9c82e166f03891ad2031bb/examples/protocols/sockets/tcp_server/main/tcp_server.c
	


bool ESP_Com::TCPServer::Init()
{
	handle = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (handle < 0) 
	{
		ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
		return false;
	}
	int opt = 1;
	setsockopt(handle, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	return true;
}



bool ESP_Com::TCPServer::Bind(int port)
{
	struct sockaddr_storage dest_addr;
	struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
	dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
	dest_addr_ip4->sin_family = AF_INET;
	dest_addr_ip4->sin_port = htons(port);
	
	int err = bind(handle, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
	if (err != 0) {
		ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
		Close();
		return false;
	}
	return true;
}




bool ESP_Com::TCPServer::Accept(TCPClient* client)
{
	if (handle < 0) return false;
	struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
	socklen_t addr_len = sizeof(source_addr);
	int sock = accept(handle, (struct sockaddr *)&source_addr, &addr_len);
	if (sock < 0) {
		ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
		return false;
	}
	client->Init(sock);
	
	//
	//if (source_addr.ss_family == PF_INET) {
	//	inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, addr_str, sizeof(addr_str) - 1);
	//}
	//else if (source_addr.ss_family == PF_INET6) {
	//	inet6_ntoa_r(((struct sockaddr_in6 *)&source_addr)->sin6_addr, addr_str, sizeof(addr_str) - 1);
	//}
	
	
	
	
	return true;
}

bool ESP_Com::TCPServer::Listen(int backlog)
{
	int err = listen(handle, backlog);
	if (err != 0) {
		ESP_LOGE(TAG, "Error occurred during listen: errno %d", errno);
		Close();
		return false;
	}	
	return true;
}
