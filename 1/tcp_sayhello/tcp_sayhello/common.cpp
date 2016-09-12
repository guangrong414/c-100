#include <stdio.h>
#include <stdarg.h>


//打印一个格式化的字符串
void P(const char* fmt, ...)
{
	va_list args;         //定义一个va_list类型的变量，用来储存单个参数
	va_start(args, fmt);  //使args指向可变参数的第一个参数

	char * tmp = new char[strlen(fmt)+1];
	memset(tmp, 0, sizeof(tmp));
	strcpy(tmp, fmt);
	tmp[strlen(fmt)] = '\n';

	printf(tmp, *args);   //直接传递给printf

	delete[] tmp;

	va_end(args);         //结束可变参数的获取
}