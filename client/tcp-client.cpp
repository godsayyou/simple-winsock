#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <io.h>
#include "tcp-client.h"

#pragma comment (lib, "Ws2_32.lib")


TcpClient::TcpClient(void)
{
	Init();
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}
TcpClient::~TcpClient(void)
{
	Cleanup();
	closesocket(fd);
}

void TcpClient::Init(void)
{
    WSADATA wsaData;

    if ( WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) 
	{
        wprintf(L"WSAStartup failed with error: %ld\n", WSAGetLastError());
    }
}
void TcpClient::Cleanup(void)
{
        WSACleanup();
}

int TcpClient::Send(char *buf, int len)
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
bool TcpClient::Connect(const char *ip, int port)
{
	if( 0 == ip )
	{
		return false;
	}
    sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons( 0xffff & port );

    return (connect(fd, (SOCKADDR*)&address, sizeof(address)) != SOCKET_ERROR);
}
bool TcpClient::Block(bool block)
{
	unsigned long mode = block;
	return (ioctlsocket(fd, FIONBIO, &mode) != SOCKET_ERROR);
}
