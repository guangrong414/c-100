#include <stdio.h>
#include <unistd.h>


int main()
{
	pid_t pid;

	//创建子进程 父进程退出 脱离终端控制
	if(pid = fork() < 0)
	{
		perror("fork 子进程失败");
		exit(0);
	}
	else if(pid > 0)
	{
		exit(0);
	}

	//子进程 执行 使用新的会话
	//重置工作目录为"/"
	//关闭文件描述符0,1, 2
	//设置文件掩码
	//关闭父进程打开的套接字
	setsid();

	if(chdir("/") < 0)
	{
		perror("chdir");
		exit(1);
	}

	umask(0);

	for(i=0;i<MAXFILE;i++)  //关闭文件描述符(常说的输入，输出，报错3个文件)，
		//因为守护进程要失去了对所属的控制终端的联系，这三个文件要关闭
	close(i);

	//子进程中创建多个孙子进程，并在孙子进程中执行第三方程序，
	//并在子进程中监控执行结果，防止进程意外终止

	


	return 0;
}
