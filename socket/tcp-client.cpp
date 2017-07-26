#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <io.h>
#include "tcp-client.h"


bool TcpClient::Open(void)
{
	if( INVALID_SOCKET == fd )
	{
		fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}
	return (INVALID_SOCKET != fd);
}
bool TcpClient::Connect(const char *ip, int port)
{
	if( 0 == ip )
	{
		return false;
	}
	if( Open() == false )
	{
		return false;
	}
    sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons( 0xffff & port );

    return (connect(fd, (SOCKADDR*)&address, sizeof(address)) != SOCKET_ERROR);
}
int TcpClient::Send(const char *buf, int len)
{
	if( 0 == buf || len < 1 )
	{
		return -1;
	}
	return send(fd, buf, len, 0);
}
int TcpClient::Recv(char *buf, int len)
{
	if( 0 == buf || len < 1 )
	{
		return -1;
	}
	return recv(fd, buf, len, 0);
}
