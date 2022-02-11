#include <sys/types.h> 
#include <sys/stat.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <signal.h>

//��Ϣ��󳤶�
#define BUE MAX_LEN64
//���������ܵ���ʶ
#define FIFO "/tmp/myfifo"

//��Ϣ��󳤶�
#define BUE MAX_LEN64
//���������ܵ���ʶ
#define FIFO "/tmp/myfifo"
//�����ź�
#define SIG_UI_QUIT 35
#define SIG PHONE QUIT 36
//����������������
static int get char() 
{
	fd_set rfds;
	struct timeval tv;
	int ch = 0;
	
	FD_ZERO (&rfds);
	FD_SET (0, &rfds);
	tv.tv_sec = 0;
	tv.tv_usec =1; //���õȴ���ʱʱ��
	
	//�������Ƿ�������
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
	//�򿪹ܵ�,ִ��shel1������ҽ�����Ϊtask phone_sig��pid
	fp = popen ("ps -e I grep 'task_phone_sig)' I awk ' (print $1)\'","r");
	fgets (buf, sizeof (buf), fp);
	if (strlen(buf) > 0)pid = atoi (buf);{	
		return pid; 
	}
}
//�źŴ�����
void sig_ deal (int sig){
	if(sig == SIG PHONE_QUIT)
	{
		printf ("task ui recv quit!n");
		exit (0);
	}
}
//�ı�ͨ��״̬
static void change state (void)
{
	if (get_phone_pid() >0) 
	{
		kill (get phonepid(), SIG PHONE QUIT) ; //�����źŸ�task phone
	}
	printf ("Send quit msg ok!\n");
}
int main(int argc, char **argv)
{
	int fd =-1;
	char buf [BUF MAX LEN] ={0};
	int len = 0;
	int ch = 0;//����SIG PHONE QUIT�źŴ�����
	signal (SIG_PHONE_QUIT, sig_deal);
		/*����1:���������ܵ�*/
	if (access (FIFO, F_OK)!= 0)
	{
		if (mkfifo (FIFO, 0666) < 0){
			perror("cannot create fifo! ");
			exit (1);
		}
	}
			/*����2:�������ܵ�,�����÷�������־*/
	if((fd = open (FIFO, O_RDONLYIO|NONBLOCK, 0)) < 0){
		perror("open fifo! ");
		exit (1); 
	}
	
	while (1)
	{
		/*��ȡ��������,��Ϊ'q',��֪ͨͨ������ı�״̬*/
		ch = get char ();
		if(ch == 'q')change_state ();
		else if(ch == 'c')
		{
			break;
		}
			/*����3:�ӹܵ��ж�ȡ��Ϣ�ַ���*/
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
	/*����4:�ر������ܵ�*/
	close (fd);
	return 0; 
}
