#include"stdio.h"
#include"stdlib.h"
#include"sys/msg.h"
#include"pthread.h"
#define msgFile "/mnt/hgfs/workspaces_vm/shensheng/tmp.txt"
struct msg_form{
	long mtype;
	char mtext[256];
};
static void * func1(void* p ){
	pthread_detach(pthread_self());
	while(1){
		printf("in func1 index is %d\n",1);
		sleep(1);
	}
	return NULL;
}
int main(){
	int msqid;
	key_t key;
	struct msg_form msg;
	
	key = ftok(msgFile,'z');
	printf("key=%d\n",key);
	msqid = msgget(key,IPC_CREAT|0777);
	printf("msqid =%d\n",msqid);
	pthread_t s_thread;
	pthread_create(&s_thread,NULL,func1,NULL);
	printf("s_thread = %x\n",s_thread);
	while(1){
		msgrcv(msqid,&msg,256,888,0);
		printf("receive msg.mtext = %s\n",msg.mtext);
		printf("receive msg.mtype = %d\n",msg.mtype);
		msg.mtype = 999;
		sprintf(msg.mtext,"Hello, I am a server\n");
		msgsnd(msqid,&msg,sizeof(msg.mtext),0);
	}
	return 0;

}