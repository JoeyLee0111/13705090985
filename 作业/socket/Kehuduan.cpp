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
	//定义socket
	int sock fd =0;
	//定义接收数据的内存
	char recvbuf[RECV BUF SIZE] ={0};
	//定义发送数据的内存
	char sendbuf[SEND BUF SIZE] ={0};
	//定义接收数据中长度
	int recvlen =0;
	int retlen = 0;
	int sendlen = 0;
	int leftlen =0; 
	char *ptr =NULL;
	//定义服务器的socket通讯地址
	struct sockaddr in ser addr;
	//设置服务器的socket参数
	memset(&ser addr, 0, sizeof(ser addr));
	ser addr.sin family = AF INET;
	inet aton("127.0.0.1", (struct in addr *)&ser addr.sin addr);
	ser addr.sin port = htons(SERVER PORT);
	//创建socket
	sock_fd = socket(AF INET, SOCK STREAM, 0);
	if(sock fd < 0)
	{
		printf("create socket failed\n");
		exit(1);
	} 
	//连接到服务器
	if(connect(sock fd, (struct sockaddr *)&ser addr, sizeof(ser addr)) < 0)
	{
		printf("connect socket failed'n");
		close(sock_fd);
		exit(1);
	}
	//接收数据
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
	//发送数据
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
	//关闭socket
	close(sock fd);
}
	
	
