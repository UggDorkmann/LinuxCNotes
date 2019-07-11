#include"stdio.h"
#include"stdlib.h"
#include"sys/msg.h"
#define msgFile "/mnt/hgfs/workspaces_vm/shensheng/tmp.txt"
struct msg_form{
	long mtype;
	char mtext[256];
};
int main(){
	int msqid;
	key_t key;
	struct msg_form msg;
	key = ftok(msgFile,'z');
	printf("client key = %d\n",key);
	
	msqid = msgget(key,IPC_CREAT|0777);
	printf("client msqid =%d\n",msqid);
	
	msg.mtype = 888;
	sprintf(msg.mtext,"I am client\n");
	msgsnd(msqid,&msg,sizeof(msg.mtext),0);
	
	msgrcv(msqid,&msg,256,999,0);
	printf("client  receive msg.mtext =%s\n",msg.mtext);
	printf("client  receive msg.mtype =%d\n",msg.mtype);

return 0;
}