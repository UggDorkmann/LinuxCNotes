#include "../all.h"
jmp_buf jb;

static void intOverFlowHandler(int signo,siginfo_t* info,void* coontext){
	printf("in intOverFlowHandler\n");
	if(info->si_code == FPE_INTOVF){
		printf("int overflow\n");
		longjmp(jb,1);
	}
	else if(info->si_code == FPE_INTDIV){
		printf("div by 0\n");
		longjmp(jb,1);
	}
	else if(info->si_code == FPE_FLTDIV){
		printf("case FPE_FLTDIV\n");
	}
	else if(info->si_code == FPE_FLTOVF){
		printf("case FPE_FLTOVF\n");
	}

	else if(info->si_code == FPE_FLTUND){
		printf("case FPE_FLTUND\n");
	}

	else if(info->si_code == FPE_FLTRES){
		printf("case FPE_FLTRES\n");
	}

	else if(info->si_code == FPE_FLTINV){
		printf("case FPE_FLTINV\n");
	}

	else if(info->si_code == FPE_FLTSUB){
		printf("case FPE_FLTSUB\n");
	}
	else{
		printf("unknown case\n");
	}
	return;
}
static void div0handler(int signo){
	printf("in div0handler\n");
	longjmp(jb,1);
}
int main(){
	#if 1
	struct sigaction act;
	act.sa_handler = NULL;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = intOverFlowHandler;
	
	sigaction(SIGFPE,&act,NULL);
	#else
	signal(SIGFPE,div0handler);
	#endif

	unsigned int a = 0xffffffff;
	unsigned int b = 0xffffffff;
	unsigned int c = 0;
	if(setjmp(jb) == 0){
		c = a+b;
	}
	//整数溢出不会触发INTOVF的SIGFPE信号，可以使用下行代码进行判断（前提是数据类型是unsigned int）
	if(c<a || c<b){
		kill(getpid(),SIGFPE);
	}

	if(setjmp(jb) == 0){
		int d = 23/0;
	}
	if(setjmp(jb) == 0){
		int e = 23/0;
	}
return 0;
}
#if 0
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/signal: ./a.out
in intOverFlowHandler
unknown case
in intOverFlowHandler
div by 0
in intOverFlowHandler
div by 0
#endif

