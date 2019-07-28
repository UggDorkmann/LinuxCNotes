#include"../all.h"
unsigned long long count;
struct timeval end;
pid_t pid;
void checktime(char * str){
	struct timeval tv;
	gettimeofday(&tv,NULL);
	if(tv.tv_sec >= end.tv_sec && tv.tv_usec > end.tv_usec){
		printf("%s count = %lld\n",str,count);
		if(pid>0){
			wait(NULL);
			exit(0);
		}
		else exit(0);
	}
}
int main(int argc,char** argv){
	char* s;
	int nzero,ret;
	int adj = 0;
	setbuf(stdout,NULL);
	
#if defined(NZERO)
	nzero = NZERO;
#elif defined(_SC_NZERO)
	nzero = sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif
	//printf("NZERO= %d\n",nzero);
	if(argc == 2)adj = strtol(argv[1],NULL,10);
	gettimeofday(&end,NULL);
	end.tv_sec+=5;
	pid = fork();
	if(pid < 0)perror("fork");
	else if(pid == 0){
		s = "child";
		printf("current nice value in child is %d,adjusting by %d\n",nice(0),adj);
		errno = 0;
		if((ret = nice(adj)) == -1 && errno != 0)perror("nice");
		printf("now child nice value is %d\n",ret);
	}
	else{
		s = "parent";
		printf("current nice value in parent is %d\n",nice(0));
	}
	while(1){
		if(++count == 0)perror("counter wrap");
		checktime(s);
	}
	if(pid > 0){
		wait(NULL);
	}
return 0;	
}
#if 0

/mnt/hgfs/shareDir/shensheng/LinuxCNotes/fork: ./a.out
current nice value in child is 0,adjusting by 0
now child nice value is 0
current nice value in parent is 0
child count = 10852254
parent count = 11094083
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/fork: ./a.out 20
current nice value in child is 0,adjusting by 20
current nice value in parent is 0
now child nice value is 19
parent count = 19651987
child count = 2008511

#endif
