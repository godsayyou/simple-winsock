#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__
#include "socket-base.h"

class TcpClient : public SocketBase
{
public:
	bool Open(void);
	bool Connect(const char *ip, int port);
	int Send(const char *buf, int len);
	int Recv(char *buf, int len);
};


#endif//__TCP_CLIENT_H__
