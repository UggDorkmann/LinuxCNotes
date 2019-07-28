#include"../all.h"
#define using_sigsetjmp 0
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
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;
static void sig_usr1(int signo){
	time_t starttime;
	if(canjump == 0)return;
	pr_mask("starting sig_usr1:");
	alarm(3);
	starttime = time(NULL);
	while(1){
		if(time(NULL) - starttime > 5)break;
	}
	pr_mask("finishing sig_usr1:");
	canjump = 0;
	#if using_sigsetjmp == 1
	siglongjmp(jmpbuf,1);
	#else
	longjmp(jmpbuf,1);	
	#endif
}
static void sig_alrm(int signo){
	pr_mask("in sig_alrm:");
	//有的信号不需要longjmp跳走也能结束，有的信号必须使用longjmp，否则会在信号处理函数中无限循环
}
int main(){
	if(signal(SIGUSR1,sig_usr1) == SIG_ERR)perror("signal SIGUSR1");
	if(signal(SIGALRM,sig_alrm) == SIG_ERR)perror("signal SIGALRM");
	pr_mask("starting main:");
	#if using_sigsetjmp == 1
	if(sigsetjmp(jmpbuf,1)){
	#else
	if(setjmp(jmpbuf)){
	#endif
		pr_mask("ending main:");
		exit(0);
	}
	canjump = 1;
	while(1)pause();
		
return 0;	
}
#if 0
开启宏using_sigsetjmp：
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/signal: ./a.out &
[1] 363
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/signal: starting main:
kill -USR1 363
starting sig_usr1: SIGUSR1
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/signal: in sig_alrm: SIGUSR1 SIGALRM
finishing sig_usr1: SIGUSR1
ending main:

[1]+  Done                    ./a.out
关闭宏using_sigsetjmp：
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/signal: ./a.out &
[1] 409
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/signal: starting main:
kill -USR1 409
starting sig_usr1: SIGUSR1
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/signal: in sig_alrm: SIGUSR1 SIGALRM
finishing sig_usr1: SIGUSR1
ending main: SIGUSR1

[1]+  Done                    ./a.out
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/signal:

#endif
