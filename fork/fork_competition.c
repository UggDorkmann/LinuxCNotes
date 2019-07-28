#include"../all.h"
#define changjing 3

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;

static void
sig_usr(int signo)	/* one signal handler for SIGUSR1 and SIGUSR2 */
{
	sigflag = 1;
}

void
TELL_WAIT(void)
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		perror("signal(SIGUSR1) error");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		perror("signal(SIGUSR2) error");
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);

	/* Block SIGUSR1 and SIGUSR2, and save current signal mask */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		perror("SIG_BLOCK error");
}

void
TELL_PARENT(pid_t pid)
{
	kill(pid, SIGUSR2);		/* tell parent we're done */
}

void
WAIT_PARENT(void)
{
	//while (sigflag == 0) //这句话有没有输出一样，sigsuspend自带阻塞功能
		sigsuspend(&zeromask);	/* and wait for parent */
	/*
	The sigsuspend call temporarily replaces the signal mask for  the  pro-
    cess with that given by mask and then suspends the process until a sig-
    nal is received.
	*/
	sigflag = 0;

	/* Reset signal mask to original value */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		perror("SIG_SETMASK error");
}

void
TELL_CHILD(pid_t pid)
{
	kill(pid, SIGUSR1);			/* tell child we're done */
}

void
WAIT_CHILD(void)
{
	//while (sigflag == 0)//这句话有没有输出一样，sigsuspend自带阻塞功能
		sigsuspend(&zeromask);	/* and wait for child */
	sigflag = 0;

	/* Reset signal mask to original value */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		perror("SIG_SETMASK error");
}

static void charatatime(char * str){
	char * p;
	int c;
	setbuf(stdout,NULL);
	for(p=str;(c=*p++)!=0;){
		usleep(1);
		putc(c,stdout);
	}
}
int main(){
	pid_t pid;
	#if changjing == 1
	pid = fork();
	if(pid<0)perror("fork");
	else if(pid == 0)charatatime("output from child\n");
	else charatatime("output from parent!\n");
	#elif changjing == 2
	TELL_WAIT();
	pid = fork();
	if(pid<0)perror("fork");
	else if(pid == 0){
		WAIT_PARENT();
		charatatime("output from child\n");
	}
	else{
		charatatime("output from parent!\n");
		TELL_CHILD(pid);
		wait(NULL);
	}
	#elif changjing == 3
	TELL_WAIT();
	pid = fork();
	if(pid<0)perror("fork");
	else if(pid == 0){
		charatatime("output from child\n");
		TELL_PARENT(getppid());
	}
	else{
		WAIT_CHILD();
		charatatime("output from parent!\n");
		wait(NULL);
	}
	#endif
	
return 0;	
}
#if 0
场景1：
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/fork: ./a.out
oouuttppuutt  ffrroomm  pcahrielndt
!
场景2：
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/fork: ./a.out
output from parent!
output from child
场景3：
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/fork: ./a.out
output from child
output from parent!
#endif
