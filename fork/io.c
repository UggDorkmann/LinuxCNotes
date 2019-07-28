#include"../all.h"
int globvar = 6;
char buf[] = "a write to stdout\n";
int main(){
	int var;
	pid_t pid;
	var = 88;
	write(1,buf,sizeof(buf)-1);
	printf("before fork\n");
	if((pid = fork()) < 0)perror("fork");
	else if(pid == 0){
		globvar++;
		var++;
	}
	else sleep(2);
	printf("pid = %ld,globvar= %d,var = %d\n",(long)getpid(),globvar,var);
	return 0;
}
#if 0
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/fork: gcc io.c
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/fork: ./a.out
a write to stdout
before fork
pid = 1708,globvar= 7,var = 89
pid = 1707,globvar= 6,var = 88
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/fork: ./a.out > tmp.txt
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/fork: cat tmp.txt
a write to stdout
before fork
pid = 1713,globvar= 7,var = 89
before fork
pid = 1712,globvar= 6,var = 88



#endif
