#include"../all.h"

void pr_mask(const char* str){
	sigset_t sigset;
	int errno_save;
	errno_save = errno;
	if(sigprocmask(0,NULL,&sigset) < 0)perror("sigprocmask err");
	else{
		printf("%s ",str);
		if(sigismember(&sigset,SIGINT))printf("SIGINT ");
		if(sigismember(&sigset,SIGQUIT))printf("SIGQUIT ");
		if(sigismember(&sigset,SIGUSR1))printf("SIGUSR1 ");
		if(sigismember(&sigset,SIGALRM))printf("SIGALRM ");
		printf("\n");
	}
	errno = errno_save ;
}
static void sig_int(int signo){
	pr_mask("\nin sig_int:");
}
int main(){
	sigset_t newmask,oldmask,waitmask;
	pr_mask("program start:");
	signal(SIGINT,sig_int);
	
	sigemptyset(&waitmask);
	sigaddset(&waitmask,SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGINT);
	
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) <0)perror("sigprocmask err");
	pr_mask("in critical region:");
	
	sigsuspend(&waitmask);
	//pause();
	
	pr_mask("return from sigsuspend:");
	
	sigprocmask(SIG_SETMASK,&oldmask,NULL);
	
	pr_mask("exit:");
	
return 0;
}

#if 0
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/signal: ./a.out
program start:
in critical region: SIGINT

in sig_int: SIGINT SIGUSR1
return from sigsuspend: SIGINT
exit:
执行sigsuspend的时候，进程的信号屏蔽字被替换成了自己的参数，SIGINT信号产生后，这个函数的阻塞被打断了，
在运行SIGINT的处理函数的时候，进程的信号屏蔽字还没有被恢复，SIGINT处理函数结束后，sigsuspend继续运行，
它返回的时候才恢复进程的原来的信号屏蔽字。
#endif
