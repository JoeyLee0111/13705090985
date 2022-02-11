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
//下一步时间间隔
#define TIME NEXT 50
//定义信号
#define SIG_UI_QUIT 35
#define SIG PHONE QUIT 36
//定义通话状态
enum TASK PHONE STATE
{
	TASK_PHONE_STATE_NONE =0,
	TASK_PHONE_STATE_RING,
	TASK_PHONE_STATE_TALK,
	TASK_PHONE_STATE_HANGUP, 
};
int phone state = TASK PHONE STATE NONE;
//设置通话状态
void set state(int state){
	phone_state = state;
}
//获取通话状态
int get_state (void){
	return phone_state; 
}

int get_ui_pid () {
	int pid = -1;
	FILE *fp = NULL;
	char buf [12] = {0};
}
	//打开管道,执行shel1命令查找进程名为task_ui_sig的pid
	fp = popen ("ps -e I grep 'task_ui_sig(' I awk ' (print $1))'","r");
	fgets (buf, sizeof (buf), fp);
	if (strlen(buf) > 0){
		pid = atoi (buf);
	}
	return pid; 
}
//信号处理函数
void sig_deal (int sig){
	if (sig == SIG UI QUIT){
		printf ("Task ui hangup! \n");
		set state (TASK_PHONE_STATE_HANGUP) ;
	}
}
int main(int argc, char **argv)
{
	int fd =-1;
	char buf [BUF_MAX_LEN] ={0};
	int len = 0;
	int time = 0;
	/*步骤1:打开EIFO管道,并设置非阻塞标志*/
	fd=open (FIFO, O WRONLYIO NONBLOCK, 0) ;
	if (fd=-1)
	{
		printf("open error: no reading process\n") ;
		return -1; 
	}
	//设置SIG UI QUIT信号处理函数
	signal(SIG_UI_QUIT, sig_deal);
	while (1){
		
		/*模拟与其他用户处理通信协议,每隔5s进入下一状态*/
		time++;
		if (time >= TIME NEXT){
			time = 0;
			if (get_state () == TASK_PHONE_STATE RING) {
				set_state (TASK PHONE STATE TALK);
			}
			else if (get state () == TASK PHONE STATE TALK){
				set_state (TASK PHONE STATE HANGUP) ;
			}
			else
			{
				set state (TASK PHONE STATE RING) ;
				printf ("Current state is ed! n", get_state ()); 
			}
		}
			/*步骤2:获取将要发送的消息字符串*/
		if (argc == 1)
		{
			printf ("Please send something\n");
			return-1;
		}
		strcpy (buf, argv [1]);
		/*步骤3:向管道中写入字符串*/
		if ((len = write (fd, buf, sizeof (buf) ) )== -1) {
			printf ("The FIFO has not been read yet. Please try later\n");
		} 
		else
		{
			printf ("write 8s to the FIFO\n", buf) ; 
		}
		/*若当前通话状态为挂断,则退出任务,并发送信号给UI*/
		if (get state () == TASK PHONE STATE HANGUP){
			if (get_ui_pid() > 0){
				kill (get_ui pid(), SIG_UI_QUIT) ;
				printf ("Send quit msg! (n");
			}
			break;
		}
		usleep (100*1000); 
	}
	/*步骤4:关闭有名管道*/
	close (fd);
	return 0;
}

