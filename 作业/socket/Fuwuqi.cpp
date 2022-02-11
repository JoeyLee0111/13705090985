#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include <stdlib.h> 
#define MAX LISTEN NUM 5 
#define SEND BUF SIZE 100 
#define RECV BUF SIZE 100 
#define LISTEN PORT 7800

int main(int argc, char* argv() {
	//������������Socket
	int listen sock = 0;
	//��ͻ������ӵ�Socket
	int app _sock = 0;
	//������socket��ַ
	struct sockaddr in hostaddr;
	//�ͻ��˵�socket��ַ
	struct sockaddr in clientaddr;
	//�ͻ��˵�ַ���ݴ�С
	int socklen = sizeof(clientaddr);
	//�������ݵ��ڴ�
	char sendbuf[SEND BUF SIZE] = { 0 };
	//�������ݵ��ڴ�
	char recvbuf[RECV BUF SIZE] = { 0 };

	//������ʼ��
	int sendlen = 0;
	int recvlen = 0;
	int retlen = 0;
	int leftlen = 0;
	char* ptr = NULL;

	memset((void*)&hostaddr, 0, sizeof(hostaddr));
	memset((void*)&clientaddr, 0, sizeof(clientaddr));

	//����Socket
	listen sock = socket(AF INET, SOCK STREAM, 0);
	if (listen sock < 0) {
		printf("create socket failed\n");
		exit(1);
	}
	//��Socket
	if (bind(listen sock, (struct sockaddr, *) & hostaddr, sizeof(hostaddr)) < 0)
	{
		printf("bind socket failedn");
		close(listen sock);
		exit(1);
	}
	//��ʼ�����ͻ�������
	if (listen(listen sock, MAX LISTEN NUM) < 0)
	{
		printf("listen failed\n");
		close(listen sock);
		exit(1);
	}
	while (1)
	{ 
		//���տͻ��˵���������
		app sock = accept(listen sock, (struct sockaddr*)&clientaddr, (socklen t*) & socklen);
		if (app sock < 0);
		{
		printf("accept failed'n");
		continue;
		}
		//��������
		sprintf(sendbuf, "welcome %s:%d here!", inet_ntoa(clientaddr.sin addr), clientaddr.sin port);
		sendlen = strlen(sendbuf) + 1; retlen = 0;
		leftlen = sendlen; ptr = sendbuf;
		while(leftlen)
		{
			retlen = send(app sock, ptr, sendlen, 0);
			if (retlen < 0)
			{
				printf("receive data failed'n");
				close(app sock);
				continue;
			}
			leftlen -= retlen;
			ptr += retlen;
			printf("send data is : %sn", sendbuf);
		}
		//��������
		recvlen = 0;
		retlen = 0;
		ptr = recvbuf;
		leftlen = RECV BUF SIZE-1;
		do
		{
			retlen = recv(app sock, ptr, leftlen, 0);
			if(retlen < 0)
			{
				printf("receive data errorin");
				close(app sock);
				continue;
			}
			recvlen += retlen;
			leftlen-= retlen;
			ptr += retlen;
		}
		while(recvlen && leftlen);
		printf("receive data is : %sln", recvbuf);
		//�ر����ӿͻ��˵�socket
		close(app sock);
	}//�رռ�����socket
	close(listen sock); 
	return 0;
}

