#include"all.h"
#include"dirInfo.c"
dirInfo* head;
int getPrefixCount(const char*p,int size){
	int i=0;
	int ret = 0;
	for(i=0;i<size;i++){
		if(p[i]==0xffffffa4){
			ret = i-3;//i=3,ret=0  i=7,ret=4
		}
	}
	return ret;
}
void digDirName(char* dest,char* src,int size){
	int i = 0;int j=0;
	for(i=0;i<size-1;i++){
		if(src[i] == 0xffffffa4){
			for(;i<size-1;i++){
				dest[j] = src[i+1];
				j++;
			}
			break;
		}		
	}
	dest[j] = 0;
}
int main(){
	head = getDI(10);
	initDI(head);
	FILE* p_file = fopen("tmp.txt","a+");
	char line[1000] = {0};
	int i = 0,j=0;
	int sec = 0;
	while(fgets(line,sizeof(line),p_file)!=0){
		sec++;
		int count = getPrefixCount(line,strlen(line));
#if 1
		if(count>getmaxCount(head)){
			printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
			dirInfo* p = getblank(head);
			p->prefixCount = count;
			digDirName(p->dirname,line,strlen(line));
			p->layer = getmaxLayer(head)+1;
			char finalName[1000] = {0};
			linkDirName(p,finalName);
			printf("dirName is: %s\n",finalName);
			mkdir(finalName,0x664);
		}
		else if(count == getmaxCount(head)){
		#if 1
			printf("@@@@@@@@@@@@@@@@@@@@@@@\n");
			dirInfo* p = getCurrent(head);//depend on prefixCount(-1)
			digDirName(p->dirname,line,strlen(line));
			char finalName[1000] = {0};
			linkDirName(p,finalName);
			printf("dirName is: %s\n",finalName);
			mkdir(finalName,0x664);
		#endif
		}
		else{
		#if 1
			printf("@@@@@@@@@@@@@@@@@@@@@@@\n");
			dirInfo* p = getPeerNode(head,count);//find from tail to head
			digDirName(p->dirname,line,strlen(line));
			clearBehind(p);//in dirInfo.c
			char finalName[1000] = {0};
			linkDirName(p,finalName);
			printf("dirName is: %s\n",finalName);
			mkdir(finalName,0x664);
		#endif
		}
#endif
		if(sec>40){
			printf("wrong\n");
			break;
		}
	}
	fclose(p_file);
	destroyDI(head);

return 0;
}
