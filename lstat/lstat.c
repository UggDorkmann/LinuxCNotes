#include"../all.h"
int main(int argc,char** argv){
	int i = 0;
	struct stat buf;
	char* p;
	for(i=1;i<argc;i++){
		printf("%s: ",argv[i]);
		if(lstat(argv[i],&buf) < 0){
			perror("lstat");
			continue;
		}
		if(S_ISREG(buf.st_mode)) p = "regular";
		else if(S_ISDIR(buf.st_mode)) p = "DIR";
		else if(S_ISCHR(buf.st_mode)) p = "charDevice";
		else if(S_ISBLK(buf.st_mode)) p = "blockDevice";
		else if(S_ISFIFO(buf.st_mode)) p = "FIFO";
		else if(S_ISLNK(buf.st_mode)) p = "Symbolic link";
		else if(S_ISSOCK(buf.st_mode)) p = "SOCKET";
		else p = "unkown";
		printf("%s\n",p);
	}
return 0;	
}
