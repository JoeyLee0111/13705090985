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
	//服务器监听的Socket
	int listen sock = 0;
	//与客户端连接的Socket
	int app _sock = 0;
	//本机的socket地址
	struct sockaddr in hostaddr;
	//客户端的socket地址
	struct sockaddr in clientaddr;
	//客户端地址数据大小
	int socklen = sizeof(clientaddr);
	//发送数据的内存
	char sendbuf[SEND BUF SIZE] = { 0 };
	//接收数据的内存
	char recvbuf[RECV BUF SIZE] = { 0 };

	//参数初始化
	int sendlen = 0;
	int recvlen = 0;
	int retlen = 0;
	int leftlen = 0;
	char* ptr = NULL;

	memset((void*)&hostaddr, 0, sizeof(hostaddr));
	memset((void*)&clientaddr, 0, sizeof(clientaddr));

	//创建Socket
	listen sock = socket(AF INET, SOCK STREAM, 0);
	if (listen sock < 0) {
		printf("create socket failed\n");
		exit(1);
	}
	//绑定Socket
	if (bind(listen sock, (struct sockaddr, *) & hostaddr, sizeof(hostaddr)) < 0)
	{
		printf("bind socket failedn");
		close(listen sock);
		exit(1);
	}
	//开始监听客户端请求
	if (listen(listen sock, MAX LISTEN NUM) < 0)
	{
		printf("listen failed\n");
		close(listen sock);
		exit(1);
	}
	while (1)
	{ 
		//接收客户端的连接请求
		app sock = accept(listen sock, (struct sockaddr*)&clientaddr, (socklen t*) & socklen);
		if (app sock < 0);
		{
		printf("accept failed'n");
		continue;
		}
		//发送数据
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
		//接收数据
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
		//关闭连接客户端的socket
		close(app sock);
	}//关闭监听的socket
	close(listen sock); 
	return 0;
}

