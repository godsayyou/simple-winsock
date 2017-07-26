#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__
#include "socket-base.h"

class TcpServer : public SocketBase
{
private:
	bool listening;

public:
	TcpServer(void);	
	~TcpServer(void);

public:
	bool Open(void);
	bool Close(void);
	bool ReuseAddress(bool reuse);
	bool Bind(const char *ip, int port);
	bool Listen(int backlog);
	bool Accept(class TcpServer& worker);
	int Send(const char *buf, int len);
	int Recv(char *buf, int len);
};


#endif//__TCP_SERVER_H__
