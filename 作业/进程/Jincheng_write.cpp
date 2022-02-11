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
//��һ��ʱ����
#define TIME NEXT 50
//�����ź�
#define SIG_UI_QUIT 35
#define SIG PHONE QUIT 36
//����ͨ��״̬
enum TASK PHONE STATE
{
	TASK_PHONE_STATE_NONE =0,
	TASK_PHONE_STATE_RING,
	TASK_PHONE_STATE_TALK,
	TASK_PHONE_STATE_HANGUP, 
};
int phone state = TASK PHONE STATE NONE;
//����ͨ��״̬
void set state(int state){
	phone_state = state;
}
//��ȡͨ��״̬
int get_state (void){
	return phone_state; 
}

int get_ui_pid () {
	int pid = -1;
	FILE *fp = NULL;
	char buf [12] = {0};
}
	//�򿪹ܵ�,ִ��shel1������ҽ�����Ϊtask_ui_sig��pid
	fp = popen ("ps -e I grep 'task_ui_sig(' I awk ' (print $1))'","r");
	fgets (buf, sizeof (buf), fp);
	if (strlen(buf) > 0){
		pid = atoi (buf);
	}
	return pid; 
}
//�źŴ�����
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
	/*����1:��EIFO�ܵ�,�����÷�������־*/
	fd=open (FIFO, O WRONLYIO NONBLOCK, 0) ;
	if (fd=-1)
	{
		printf("open error: no reading process\n") ;
		return -1; 
	}
	//����SIG UI QUIT�źŴ�����
	signal(SIG_UI_QUIT, sig_deal);
	while (1){
		
		/*ģ���������û�����ͨ��Э��,ÿ��5s������һ״̬*/
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
			/*����2:��ȡ��Ҫ���͵���Ϣ�ַ���*/
		if (argc == 1)
		{
			printf ("Please send something\n");
			return-1;
		}
		strcpy (buf, argv [1]);
		/*����3:��ܵ���д���ַ���*/
		if ((len = write (fd, buf, sizeof (buf) ) )== -1) {
			printf ("The FIFO has not been read yet. Please try later\n");
		} 
		else
		{
			printf ("write 8s to the FIFO\n", buf) ; 
		}
		/*����ǰͨ��״̬Ϊ�Ҷ�,���˳�����,�������źŸ�UI*/
		if (get state () == TASK PHONE STATE HANGUP){
			if (get_ui_pid() > 0){
				kill (get_ui pid(), SIG_UI_QUIT) ;
				printf ("Send quit msg! (n");
			}
			break;
		}
		usleep (100*1000); 
	}
	/*����4:�ر������ܵ�*/
	close (fd);
	return 0;
}

