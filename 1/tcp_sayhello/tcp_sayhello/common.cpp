#include <stdio.h>
#include <stdarg.h>


//��ӡһ����ʽ�����ַ���
void P(const char* fmt, ...)
{
	va_list args;         //����һ��va_list���͵ı������������浥������
	va_start(args, fmt);  //ʹargsָ��ɱ�����ĵ�һ������

	char * tmp = new char[strlen(fmt)+1];
	memset(tmp, 0, sizeof(tmp));
	strcpy(tmp, fmt);
	tmp[strlen(fmt)] = '\n';

	printf(tmp, *args);   //ֱ�Ӵ��ݸ�printf

	delete[] tmp;

	va_end(args);         //�����ɱ�����Ļ�ȡ
}