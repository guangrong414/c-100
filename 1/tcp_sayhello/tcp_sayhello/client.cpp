#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8000

int main()
{
	int cli_socket;

	struct sockaddr_in serv_addr;

	char msg[1024] = {0};

	FILE* fcli = NULL;

	ssize_t ret;

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);
	serv_addr.sin_port = htons(SERVER_PORT);

	if(-1 == (cli_socket = socket(AF_INET, SOCK_STREAM, 0)))
	{
		printf("socket error, error info:%s\n", strerror(errno));
		return -1;
	}

	if(-1 == connect(cli_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))
	{
		printf("connect error, error info:%s\n", strerror(errno));
		return -1;
	}

	printf("connected to server %s\n", SERVER_IP);
	printf("say something to server\n");

	while ( 1 ) //------>while.cond-2016.8.24.13.36.40
	{//----------------------------------------------->while.start-2016.8.24.13.36.40
		char* resqmsg = "thank you!";
		write(cli_socket, resqmsg, strlen(resqmsg));
		printf("send server msg:%s\n", resqmsg);
		
		
		memset(msg, 0, sizeof(msg));
		read(cli_socket, msg, sizeof(msg));
		printf("recv server say:%s\n", msg);
		//while(-1 == (ret = read(cli_socket, msg, sizeof(msg))))
		//{
		//	if(errno == EAGAIN)
		//	{
		//		sleep(1);
		//		printf("socket:%d, recv waiting...\n",cli_socket);
		//		continue;
		//	}
		//	//s 连接套接字失效
		//	//s 套接字 无效，重现建立通道
		//	else if(errno == EBADF || errno == ENOTSOCK)
		//	{

		//	}
		//	//对端拒绝连接，对端服务停止，重建连接通道
		//	else if(errno == ECONNREFUSED )
		//	{

		//	}
		//	//接收buf的指针指向了进程外的空间（程序异常），守护进程重启程序，记录日志。
		//	else if(errno == EFAULT )
		//	{

		//	}
		//	//接收到中断信号，程序停止控制
		//	else if(errno ==  EINTR )
		//	{

		//	}
		//	//传入参数无效，检查程序，程序停止控制，记录日志
		//	else if(errno == EINVAL )
		//	{

		//	}
		//	//内存无法创建， 程序停止控制，记录日志
		//	else if(errno == ENOMEM )
		//	{

		//	}

		//}

		//printf("recv server say:%s\n", msg);


	}//----------------------------------------------->while.end-2016.8.24.13.36.40
	
	return 0;
}
