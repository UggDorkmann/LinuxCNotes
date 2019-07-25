#include"../all.h"

#if 0
int i = 0;
int main(){
	i++;
	printf("i = %d\n",i);
	if(i>3)return 0;
	else main();
}
#endif
static int statLines(const char* filename){
	//realLines = lines - 只有\r\n的行
	int lines = 0;
	int realLines = 0;
	FILE* p = fopen(filename,"r");
	char buf[400] = {0};
	int newLineChar = 1;
	while(( fgets((char*)buf,sizeof(buf),p) )>0){
		int i = 0;
		for(i=0;i<strlen(buf);i++){
			if(buf[i] == '\n'){
				lines++;
			}
			if(i>0 && buf[i] == '\n' && buf[i-1] == '\r'){
				newLineChar = 2;
			}
			if(buf[i] == '\n' && strlen(buf) > newLineChar){
				realLines++;
			}
		}
		memset(buf,0,sizeof(buf));
	}
	//if(newLineChar==2)printf("换行符是：\\r\\n\n");
	//else printf("换行符是：\\n\n");
	//printf("lines = %d\nrealLines = %d\n",lines,realLines);
	fclose(p);
	return realLines;
}
int totalLines = 0;

static int findFilesToStat(const char* pathname){
	DIR* dir = opendir(pathname);
	struct dirent *ptr;
	char newPathName[200] = {0};
	struct stat sStat;
	while((ptr = readdir(dir)) != NULL){
		sprintf(newPathName,"%s/%s",pathname,ptr->d_name);
		//printf("pathname = %s , newPathName = %s\n",pathname,newPathName);
		lstat(newPathName,&sStat);
		if(S_ISREG(sStat.st_mode) && strstr(ptr->d_name,".c") ){
			char cmd[240] = {0};
			sprintf(cmd,"wc -l %s",newPathName);
			system(cmd);
			totalLines += statLines(newPathName);
		}
		else if(S_ISDIR(sStat.st_mode) && memcmp(ptr->d_name,"..",2)!=0 && memcmp(ptr->d_name,".",1)!=0
			&& strstr(ptr->d_name,"si4project")==NULL){
			//printf("%s is a dir\n",newPathName);
			findFilesToStat(newPathName);
		}
	}
	closedir(dir);
	return totalLines;
}

int main(){
	int lines = findFilesToStat("/mnt/hgfs/shareDir/shensheng/LinuxCNotes");
	//statLines("./statLinesOfFiles.c");
	printf("lines = %d\n",lines);

return 0;	
}
