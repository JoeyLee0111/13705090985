#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <pthread.h>
//�߳̿�ͷ�ļ�,д���̳߳���������������ͷ�ļ�
#define MAX URLLEN (200)
#define MAX PATH LEN (100) 
#define MAX_TASK-CNT (10)
typedef struct{
	void** items;
	int item_maxcount;
	int item_count;
	int item_size;
}	_Z_SLIST;
typedef void* Z_SLIST;
typedef struct DOWNLOAD_TASK 
{
	char url[MAX URLLEN];
	char save_path[MAX_PATHLEN];
}_downloadtask;
static Z_SLIST task_slist =NULL;
Z_SLIST task_slist_new(int item_size, int item_maxcount);//�������ض��к���
int task_slist_delete(Z_SLIST list, int idx);//ɾ�����ض��к���
int task_slist_add(Z_SLIST list, const void* item);//������ض��к���
void* task_slist_get(Z_SLIST list, int idx);//��ȡ��Ϣ���к���
int task_add(char* url, char* save_path);//������·���������ض���
void *download_thread(void *arg);//ʵ�������߳��庯��
int init_service(void);//���ط����ʼ������
int deinit_service(void);//���ط��񷴳�ʼ������
pthread_t tid = 0;//�߳�e-ID��
void *download_thread(void *arg);//ʵ�������߳��庯��
int init service(void);//���ط����ʼ������
int deinit_msg(void); 
int init_msg(void);
Z_SLIST task_slist_new(int item_size, int item_maxcount){
	__Z_SLIST* list = NULL;
	int itemstotalsize = item size * item maxcount;
	list = (__Z_SLIST*)malloc(sizeof(__Z_SLIST));
	list->items = (void**)malloc(itemstotalsize);
	list->item_count =0;
	list->item_maxcount =item_maxcount;
	list->item_size = item_size;
	return (Z_SLIST)list; 
}
void *download_thread (void* arg){
	__download_task* task = NULL;
	while(1){
		task =(download_task*)task_slist_get(task_slist, 0);
		if (task != NULL){printf("New download task: In");
		printf("Downloading... url=%s\n", task->url);
		sleep(1);
		printf("Finish! save_path=%s\n\n", task->save_path);
		task_slist_delete(task_slist, 0);
		}
		sleep(1);
	}
	return NULL;
} 
int init_service(void){
	task_slist = task_slist_new(sizeof(download_task), MAX_TASK_CNT);
	pthread_create(&tid, NULL, download_thread, NULL); //���������߳�
	return tid;
}
int deinit_service(void){
	int ret = -1;
	ret = pthread_cancel(tid);//������ֹ�źŸ�tid�߳�
	if (0 == ret)pthread_join(tid, NULL);//�ȴ�tid�߳��˳�
	}
	return ret;
}
int init_msg(void){
	msg_id = msgget ((key_t)1234, 0666 | IPC_CREAT);
	return msg_id;
}
int deinit_msg(void){
	return msgctl (msg_id, IPC_RMID, 0);
} 
int main(){
	init_service();//��ʼ�����ط���
	task_add("http://39.108.177.3:8080/images/bill.jpg", "/sdcard/xwrj");
	sleep(5);//����5��
	deinit_service();//����ʼ�����ط���
	deinit_service();
	return 0; 
}
void* task_slist_get(Z_SLIST list, int idx){
	__Z_SLIST* 1 =(Z_SLIST*)list;
	if(!(idx >= 0 && idx < 1->item_count)){
		return NULL;
	}
	return (void*)( (char*)1->items + idx * 1->item_size);
}
