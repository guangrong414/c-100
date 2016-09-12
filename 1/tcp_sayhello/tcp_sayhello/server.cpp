#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>

#define SERVER_PORT 8000

void * work(void* arg );


int main(void* )
{
	int lis_socket;
	struct sockaddr_in addr;

	

	lis_socket = socket(AF_INET, SOCK_STREAM, 0);


	memset(&addr, 0, sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(SERVER_PORT);

	if(-1 == bind(lis_socket, (const struct sockaddr * )&addr, sizeof(struct sockaddr_in)))
	{
		printf("bind Ê§°Ü£¬Ê§°ÜÐÅÏ¢:%s\n", strerror(errno));
		return -1;
	}

	if(-1 == listen(lis_socket, 128))
	{
		printf("listen Ê§°Ü£¬Ê§°ÜÐÅÏ¢:%s\n", strerror(errno));
		return -1;
	
	}

	printf("server listenning...\n");

	while ( 1 ) //------>while.cond-2016.8.23.15.16.42
	{//----------------------------------------------->while.start-2016.8.23.15.16.42
		int cli_socket;
		struct sockaddr_in cil_addr;
		pthread_t tid; 
		int cli_addr_len = sizeof(struct sockaddr);

		if(-1 == (cli_socket = accept(lis_socket, (struct sockaddr *)&cil_addr, ( socklen_t * )&cli_addr_len)))
		{
			printf("accept Ê§°Ü£¬Ê§°ÜÐÅÏ¢:%s\n", strerror(errno));
			return -1;
		}

		printf("get new conn, client socket:%d\n", cli_socket);
		pthread_create(&tid, NULL, work, (void*)&cli_socket);

	}//----------------------------------------------->while.end-2016.8.23.15.16.42



		return 0;
}


void * work(void* arg )
{
	int clifd = *(int* )arg;
	char msg[1024] = {0};
	char* pWelcome = "Welcome you are log in";
	ssize_t ret;

	printf("welcome! work thread:%u client socket:%d\n", pthread_self(), clifd);

	//·¢ËÍÊý¾Ý
	while(1)
	{
			//while(-1 == (ret = write(clifd, pWelcome, strlen(pWelcome)+1)))
			//{
			//	if(errno == EAGAIN || errno ==  EWOULDBLOCK)
			//	{
			//		sleep(1);
			//		printf("socket:%d, send waiting\n", clifd);
			//		continue;
			//	}
			//	/*else if(errno ==  ECONNRESET)
			//	{
			//	printf("socket:%d, send waiting\n", clifd);
			//	}*/
			//}
			//printf("send client %d resquest:%s\n",clifd, pWelcome);
			//memset(msg, 0, sizeof(msg));
			//while(-1 == (ret = read(clifd, msg, sizeof(msg))))
			//{
			//	if(errno == EAGAIN || errno ==  EWOULDBLOCK)
			//	{
			//		sleep(1);
			//		printf("socket:%d, send waiting\n", clifd);
			//		continue;
			//	}
			//}
			//printf("recv client %d resquest:%s\n",clifd, msg);

		read(clifd, msg, sizeof(msg));
		printf("recv client %d resquest:%s\n",clifd, msg);

		write(clifd, pWelcome, strlen(pWelcome));
		printf("send client %d resquest:%s\n",clifd, pWelcome);


	}


	return ((void*) 0);
}
