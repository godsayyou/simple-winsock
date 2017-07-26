#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <io.h>
#include "socket-base.h"
#pragma comment (lib, "Ws2_32.lib")

bool SocketBase::started = false;
SocketBase::SocketBase(void)
{
	if( started == false)
	{
		started = Startup();
	}
	fd = INVALID_SOCKET;
	Open();
}
SocketBase::~SocketBase(void)
{
	Close();
}
bool SocketBase::Open(void)
{
	return (INVALID_SOCKET != fd);
}
bool SocketBase::Close(void)
{
	closesocket(fd);
	fd = INVALID_SOCKET;
	return true;
}
bool SocketBase::Block(bool b)
{
	unsigned long mode = !b;
	return (ioctlsocket(fd, FIONBIO, &mode) != SOCKET_ERROR);
}
bool SocketBase::Startup(void)
{
    WSADATA wsaData;

    if ( WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) 
	{
        wprintf(L"WSAStartup failed with error: %ld\n", WSAGetLastError());
		return false;
    }
	return true;
}
void SocketBase::Cleanup(void)
{
        WSACleanup();
}
