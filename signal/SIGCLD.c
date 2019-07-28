#include"../all.h"
static void sig_cld(int signo){
	pid_t pid;
	int status;
	printf("sigcld received\n");
	if(signal(SIGCLD,sig_cld) == SIG_ERR){
		perror("signal");
	}
	pid = wait(&status);
	if(pid<0)perror("wait");
	printf("pid = %d\n",pid);
}

int main(){
	pid_t pid;
	if(signal(SIGCLD,sig_cld) == SIG_ERR){
		perror("signal");
	}
	pid = fork();
	if(pid<0)perror("fork");
	else if(pid==0){
		sleep(2);
		_exit(0);
	}
	pause();
	exit(0);
return 0;	
}
#if 0
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/signal: ./a.out
sigcld received
pid = 30727
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/signal:
#endif

