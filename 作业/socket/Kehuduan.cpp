#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <unistd.h>
#define MAX LISTEN NUM 5 
#define SEND BUF SIZE 100 
#define RECV BUF SIZE 100 
#define SERVER PORT 7800
int main(int argc, char *argvt]) 
{
	//����socket
	int sock fd =0;
	//����������ݵ��ڴ�
	char recvbuf[RECV BUF SIZE] ={0};
	//���巢�����ݵ��ڴ�
	char sendbuf[SEND BUF SIZE] ={0};
	//������������г���
	int recvlen =0;
	int retlen = 0;
	int sendlen = 0;
	int leftlen =0; 
	char *ptr =NULL;
	//�����������socketͨѶ��ַ
	struct sockaddr in ser addr;
	//���÷�������socket����
	memset(&ser addr, 0, sizeof(ser addr));
	ser addr.sin family = AF INET;
	inet aton("127.0.0.1", (struct in addr *)&ser addr.sin addr);
	ser addr.sin port = htons(SERVER PORT);
	//����socket
	sock_fd = socket(AF INET, SOCK STREAM, 0);
	if(sock fd < 0)
	{
		printf("create socket failed\n");
		exit(1);
	} 
	//���ӵ�������
	if(connect(sock fd, (struct sockaddr *)&ser addr, sizeof(ser addr)) < 0)
	{
		printf("connect socket failed'n");
		close(sock_fd);
		exit(1);
	}
	//��������
	recvlen =0;
	retlen = 0;
	ptr = recvbuf;
	leftlen = RECV BUF SIZE-1;
	do
	{
		retlen = recv(sock fd, ptr, leftlen, 0);
		if(retlen < 0)printf("receive data errorln");
		{	
			close(sock_fd);
			exit(1); 
		}
		recvlen += retlen;
		leftlen -= retlen;
		ptr += retlen;
	}
	while(recvlen && leftlen);
	printf("receive data is : %sln", recvbuf);
	//��������
	sprintf(sendbuf, "hello server");
	sendlen = strlen(sendbuf) + 1;
	retlen = 0;
	leftlen = sendlen;
	ptr = sendbuf; 
	while(leftlen)
	{
		tretlen = send(sock fd, ptr, sendlen, 0);
		if(retlen < 0) 
		{
			printf("send data errorln");
			close(sock fd);
			exit(1);
		}
		leftlen -= retlen;
		ptr += retlen;
	}
	printf("send data is : %s\n", sendbuf);
	//�ر�socket
	close(sock fd);
}
	
	
