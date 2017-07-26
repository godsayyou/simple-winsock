#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "tcp-server.h"

int main(void)
{
	TcpServer server;
	TcpServer worker;

	if( server.Bind("127.0.0.1", 8888) == false )
	{
		printf("bind@0.0.0.0:8888 failed\n");
		perror("bind");
		return getchar();
	}
	printf("bind@0.0.0.0:8888\n");
	if( server.Listen(5) == false )
	{
		printf("Listen@1 falied\n");
		fflush(stdout);
		return getchar();
	}
	printf("Listen@1\n");
	if( server.Accept(worker) == false)
	{
		printf("Accept@worker failed\n");
		fflush(stdout);
		return getchar();
	}
	printf("Accept@worker\n");
	worker.Block(false);
	while(1)
	{
		char buf[32] = {0};
		if( worker.Recv(buf, sizeof(buf)-1) > 0)
		{
			worker.Send(buf, strlen(buf));
			printf("recv:%s\n", buf);
			fflush(stdout);
		}
		worker.Send("this is server", 17);
		//getchar();
		Sleep(10);
	}

	return 0;
}
