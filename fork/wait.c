#include"../all.h"

void pr_exit(int S){//S:status
	if(WIFEXITED(S)) printf("normal exit,status = %d\n",WEXITSTATUS(S));
	else if(WIFSIGNALED(S))printf("abnormal exit,signal number=%d%s\n",WTERMSIG(S),
#ifdef WCOREDUMP
		WCOREDUMP(S)?"(core file generated)":"");
#else
		"");
#endif
	else if(WIFSTOPPED(S)) printf("child stopped,signal number = %d\n",WSTOPSIG(S));
}
int main(){
	pid_t pid;
	int status;
	if((pid = fork() )< 0)perror("fork");
	else if(pid == 0)exit(7);
	
	if(wait(&status) != pid)perror("wait");
	pr_exit(status);
	
	if((pid = fork() )< 0)perror("fork");
	else if(pid == 0)abort();
	
	if(wait(&status) != pid)perror("wait");
	pr_exit(status);

	if((pid = fork() )< 0)perror("fork");
	else if(pid == 0){
		int a = 2/0;
		return 0;
	}
	
	if(wait(&status) != pid)perror("wait");
	pr_exit(status);
return 0;	
}
