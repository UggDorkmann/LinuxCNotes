#include"../all.h"
int main(int argc,char** argv){
	if(argc!=2){
		printf("2 paras,no more,no less\n");
		return -2;
	}
	if(access(argv[1],F_OK) < 0){
		perror("no such file");
		return -1;
	}
	else{
		printf("it exists\n");
	}
	int fd = open("test.txt",0);
		
	return 0;
	//exit(0);
}
