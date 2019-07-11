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
	while(1){
		static pthread_t s_thread = 0x0;
		static pthread_t s_bak = 0x1;
		if(s_thread!=s_bak)
			pthread_create(&s_thread,NULL,func1,NULL);
		s_bak = s_thread;
		sleep(1);
		printf("s_bak = %x    s_thread = %x\n",s_bak,s_thread);
	}
	return 0;

}