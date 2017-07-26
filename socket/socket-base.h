#ifndef __SOCKET_BASE_H__
#define __SOCKET_BASE_H__


class SocketBase
{
protected:
	int fd;
	static bool started;
public:
	SocketBase(void);
	~SocketBase(void);
public:
	virtual bool Open(void);
	virtual bool Close(void);
	virtual bool Block(bool b);//b=1×èÈû£¬b=0·Ç×èÈû
public:
	static bool Startup(void);
	static void Cleanup(void);
};

#endif//__SOCKET_BASE_H__
