#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__

class TcpClient
{
private:
	int fd;

public:
	TcpClient(void);	
	~TcpClient(void);

public:
	void Init(void);
	void Cleanup(void);

public:
	int Send(char *buf, int len);
	int Recv(char *buf, int len);
	bool Connect(const char *ip, int port);
	bool Block(bool block);
};


#endif//__TCP_CLIENT_H__
