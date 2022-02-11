#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <pthread.h>
//线程库头文件,写多线程程序必须首先引入此头文件
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
Z_SLIST task_slist_new(int item_size, int item_maxcount);//创建下载队列函数
int task_slist_delete(Z_SLIST list, int idx);//删除下载队列函数
int task_slist_add(Z_SLIST list, const void* item);//添加下载队列函数
void* task_slist_get(Z_SLIST list, int idx);//获取消息队列函数
int task_add(char* url, char* save_path);//将下载路径加入下载队列
void *download_thread(void *arg);//实际下载线程体函数
int init_service(void);//下载服务初始化函数
int deinit_service(void);//下载服务反初始化函数
pthread_t tid = 0;//线程e-ID号
void *download_thread(void *arg);//实际下载线程体函数
int init service(void);//下载服务初始化函数
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
	pthread_create(&tid, NULL, download_thread, NULL); //创建下载线程
	return tid;
}
int deinit_service(void){
	int ret = -1;
	ret = pthread_cancel(tid);//发送终止信号给tid线程
	if (0 == ret)pthread_join(tid, NULL);//等待tid线程退出
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
	init_service();//初始化下载服务
	task_add("http://39.108.177.3:8080/images/bill.jpg", "/sdcard/xwrj");
	sleep(5);//休眠5秒
	deinit_service();//反初始化下载服务
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
