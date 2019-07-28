#include"../all.h"
int main(){
	sigset_t set,oset,pset;
	sigemptyset(&set);
	sigaddset(&set,2);
	int sm = sigprocmask(SIG_SETMASK,&set,&oset);
	if(sm<0)perror("sigprocmask");
	while(1){
		sleep(2);
		int sp = sigpending(&pset);
		if(sp<0)perror("sigpending");
		int is = sigismember(&pset,2);
		if(is == 1)printf("pending...\n");
		else printf("no pending\n");
	}
return 0;	
}
