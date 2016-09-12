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
		memset(msg, 0, sizeof(msg));
		while(-1 == (ret = read(cli_socket, msg, sizeof(msg))))
		{
			if(errno == EAGAIN)
			{
				sleep(1);
				printf("socket:%d, recv waiting...\n",cli_socket);
				continue;
			}
			//s �����׽���ʧЧ
			//s �׽��� ��Ч�����ֽ���ͨ��
			else if(errno == EBADF || errno == ENOTSOCK)
			{

			}
			//�Զ˾ܾ����ӣ��Զ˷���ֹͣ���ؽ�����ͨ��
			else if(errno == ECONNREFUSED )
			{

			}
			//����buf��ָ��ָ���˽�����Ŀռ䣨�����쳣�����ػ������������򣬼�¼��־��
			else if(errno == EFAULT )
			{

			}
			//���յ��ж��źţ�����ֹͣ����
			else if(errno ==  EINTR )
			{

			}
			//���������Ч�������򣬳���ֹͣ���ƣ���¼��־
			else if(errno == EINVAL )
			{

			}
			//�ڴ��޷������� ����ֹͣ���ƣ���¼��־
			else if(errno == ENOMEM )
			{

			}

		}

		printf("recv server say:%s\n", msg);

		char* resqmsg = "thank you!";
		write(cli_socket, resqmsg, strlen(resqmsg));
		printf("send server msg:%s\n", resqmsg);
	}//----------------------------------------------->while.end-2016.8.24.13.36.40
	
	return 0;
}
