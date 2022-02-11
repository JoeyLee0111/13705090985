#include <sys/types.h> 
#include <sys/stat.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <signal.h>

//消息最大长度
#define BUE MAX_LEN64
//定义有名管道标识
#define FIFO "/tmp/myfifo"

//消息最大长度
#define BUE MAX_LEN64
//定义有名管道标识
#define FIFO "/tmp/myfifo"
//定义信号
#define SIG_UI_QUIT 35
#define SIG PHONE QUIT 36
//非阻塞检测键盘输入
static int get char() 
{
	fd_set rfds;
	struct timeval tv;
	int ch = 0;
	
	FD_ZERO (&rfds);
	FD_SET (0, &rfds);
	tv.tv_sec = 0;
	tv.tv_usec =1; //设置等待超时时间
	
	//检测键盘是否有输入
	if (select(1, &rfds, NULL, NULL, &tv) > 0) 
	{
		ch = getchar();
	}
	return ch;
}
int get_phone_pid () 
{
	int pid = -1;
	FILE *fp = NULL;char buf [12] = {0};
	//打开管道,执行shel1命令查找进程名为task phone_sig的pid
	fp = popen ("ps -e I grep 'task_phone_sig)' I awk ' (print $1)\'","r");
	fgets (buf, sizeof (buf), fp);
	if (strlen(buf) > 0)pid = atoi (buf);{	
		return pid; 
	}
}
//信号处理函数
void sig_ deal (int sig){
	if(sig == SIG PHONE_QUIT)
	{
		printf ("task ui recv quit!n");
		exit (0);
	}
}
//改变通话状态
static void change state (void)
{
	if (get_phone_pid() >0) 
	{
		kill (get phonepid(), SIG PHONE QUIT) ; //发送信号给task phone
	}
	printf ("Send quit msg ok!\n");
}
int main(int argc, char **argv)
{
	int fd =-1;
	char buf [BUF MAX LEN] ={0};
	int len = 0;
	int ch = 0;//设置SIG PHONE QUIT信号处理函数
	signal (SIG_PHONE_QUIT, sig_deal);
		/*步骤1:创建有名管道*/
	if (access (FIFO, F_OK)!= 0)
	{
		if (mkfifo (FIFO, 0666) < 0){
			perror("cannot create fifo! ");
			exit (1);
		}
	}
			/*步骤2:打开有名管道,并设置非阻塞标志*/
	if((fd = open (FIFO, O_RDONLYIO|NONBLOCK, 0)) < 0){
		perror("open fifo! ");
		exit (1); 
	}
	
	while (1)
	{
		/*获取键盘输入,若为'q',则通知通话任务改变状态*/
		ch = get char ();
		if(ch == 'q')change_state ();
		else if(ch == 'c')
		{
			break;
		}
			/*步骤3:从管道中读取消息字符串*/
		while (1)
		{
			memset (buf, 0, sizeof (buf));
			if((len = read (fd, buf, sizeof (buf))) > 0){
				printf("read &s from FIFO n", buf);
				break;			
			}
			printf ("no data yet n");
			sleep (1) ;
		}
	}
	/*步骤4:关闭有名管道*/
	close (fd);
	return 0; 
}
