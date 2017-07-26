#include <stdio.h>
#include "tcp-client.h"

int main(void)
{
	TcpClient client;

	if( client.Connect("127.0.0.1", 8888) == false )
	{
		perror("connect failed!\n");
	}
	client.Block(true);

	while(1)
	{
		char buf[32] = {0};

		printf("test\n");
		if( client.Recv(buf, sizeof(buf)-1) > 0 )
		{
			printf("buf:%s\n", buf);
			fflush(stdout);
		}
		if( client.Send("hello server\0", 15) )
		{
			printf("send to server\n");
		}
		getchar();
	}

	return 0;
}