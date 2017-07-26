#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <io.h>
#include "tcp-server.h"


TcpServer::TcpServer(void)
{
	listening = false;
}
TcpServer::~TcpServer(void)
{
	listening = false;
}
bool TcpServer::Open(void)
{
	if( INVALID_SOCKET == fd )
	{
		fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}
	return (INVALID_SOCKET != fd);
}
bool TcpServer::Close(void)
{
	closesocket(fd);
	fd = INVALID_SOCKET;
	listening = false;
	return true;
}
bool TcpServer::ReuseAddress(bool reuse)
{
	return (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) != SOCKET_ERROR);
}
bool TcpServer::Bind(const char *ip, int port)
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
    address.sin_port = htons( 0xffff & port);

    return (bind(fd,(SOCKADDR*)&address, sizeof(address)) != SOCKET_ERROR);
}
bool TcpServer::Listen(int backlog)
{
    listening = (listen(fd, backlog) != SOCKET_ERROR);
	return listening;
}
bool TcpServer::Accept(TcpServer& worker)
{
	int len = 0;
	sockaddr_in address;

	if( false == listening )
	{
		return false;
	}
	if( worker.fd != INVALID_SOCKET )
	{
		closesocket(worker.fd);
	}
	len = sizeof(address);	
	worker.fd = accept(fd,(SOCKADDR*)&address, &len);
	return (INVALID_SOCKET != worker.fd);
}
int TcpServer::Recv(char *buf, int len)
{
	if( 0 == buf || len < 1 || listening )
	{
		return -1;
	}
	return recv(fd, buf, len, 0);
}
int TcpServer::Send(const char *buf, int len)
{
	if( 0 == buf || len < 1 || listening )
	{
		return -1;
	}
	return send(fd, buf, len, 0);
}
