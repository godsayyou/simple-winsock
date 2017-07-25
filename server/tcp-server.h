#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

class TcpServer
{
private:
	int fd;
	bool listening;

public:
	TcpServer(void);	
	~TcpServer(void);

public:
	void Init(void);
	void Cleanup(void);

public:
	bool Block(bool block);
	bool ReuseAddress(bool reuse);
	bool Bind(const char *ip, int port);
	bool Listen(int backlog);
	bool Accept(class TcpServer& worker);
	int Send(char *buf, int len);
	int Recv(char *buf, int len);

private:
	bool OpenSocket(void);
};


#endif//__TCP_SERVER_H__
