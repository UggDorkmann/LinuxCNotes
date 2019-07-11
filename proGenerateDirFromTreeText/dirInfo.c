#include"all.h"
typedef struct s_dirInfo{
	int index;
	int layer;
	int prefixCount;
	char dirname[100];
	struct s_dirInfo * p_next;
	struct s_dirInfo * p_prev;
}dirInfo;
static void addDirInfo(dirInfo* p){
	dirInfo* add_ = malloc(sizeof(dirInfo));
	add_->p_next = NULL;
	dirInfo* tmp = p;
	dirInfo* tail = p;
	while(tmp!=NULL){
		tail = tmp;
		tmp = tmp->p_next;
	}
	tail->p_next = add_;
	add_->p_prev = tail;
}
int getmaxCount(dirInfo*p){
	dirInfo* tmp = p;
	int max = tmp->prefixCount;
	while(tmp!=NULL){
		if(max<tmp->prefixCount)max=tmp->prefixCount;
		tmp = tmp->p_next;
	}
	return max;
}
int getmaxLayer(dirInfo*p){
	dirInfo* tmp = p;
	int max = tmp->layer;
	while(tmp!=NULL){
		if(max<tmp->layer)max=tmp->layer;
		tmp = tmp->p_next;
	}
	return max;
}
static int erase0xd0xa(char*p,int size){
	int eraseSum = 0;
	if(p[size-1] == 0xa || p[size-1] == 0xd){
		eraseSum++;
		p[size-1]=0x00;
	}
	if(p[size-2] == 0xa || p[size-2] == 0xd){
		eraseSum++;
		p[size-2]=0x00;
	}
	return eraseSum;
}
void linkDirName(dirInfo* p,char * name){
	dirInfo* p_head = NULL;
	dirInfo* tmp = p;
	char * tmp_name = name;
	while(tmp!=NULL){
		p_head = tmp;
		tmp = tmp->p_prev;
	}
	int i = 0;
	while(p_head != p->p_next){
		memcpy(tmp_name,p_head->dirname,strlen(p_head->dirname));
		int eraseSum = erase0xd0xa(tmp_name,strlen(tmp_name));
		tmp_name[strlen(tmp_name)]='/';
		tmp_name[strlen(tmp_name)]=0x00;
		tmp_name += (strlen(tmp_name));
		p_head = p_head->p_next;		
	}
}
dirInfo* getCurrent(dirInfo* p){
	dirInfo * tmp = p;
	while(tmp!=NULL){
		if(tmp->prefixCount == -1)break;
		tmp = tmp->p_next;
	}
	return tmp->p_prev;
}
dirInfo* getPeerNode(dirInfo* p,int count){//find from tail to head
	dirInfo* tmp = getCurrent(p);
	while(tmp->prefixCount != count){
		tmp = tmp->p_prev;
	}
	return tmp;
}
static void myBuf0(char* p ,int size){
	int i=0;
	for(i=0;i<size;i++){
		p[i] = 0x00;
	}
}
void clearBehind(dirInfo* p){
	dirInfo* tmp = p->p_next;
	while(tmp!=NULL){
		tmp->layer = -1;
		tmp->prefixCount = -1;
		myBuf0(tmp->dirname,100);//tmp->dirname
		tmp = tmp->p_next;
}
}
dirInfo* getDI(int amount){
	if(amount<=0)return NULL;
	dirInfo* p = malloc(sizeof(dirInfo));
	p->p_next = NULL;
	p->p_prev = NULL;
	int i = 0;
	for(i=0;i<amount-1;i++){
		addDirInfo(p);
	}
	return p;
}
dirInfo* getByIndex(int i,dirInfo*p){
	dirInfo* tmp = p;
	while(tmp->index!=i){
		tmp = tmp->p_next;
		if(tmp==NULL)break;
	}
	return tmp;
}
dirInfo* getByPC(int count,dirInfo*p){
	dirInfo* tmp = p;
	while(tmp->prefixCount!=count){
		tmp = tmp->p_next;
		if(tmp==NULL)break;
	}
	return tmp;
}
char* getNameByPC(int count,dirInfo*p){
	dirInfo* tmp = p;
	while(tmp->prefixCount!=count){
		tmp = tmp->p_next;
		if(tmp==NULL)break;
	}
	return tmp->dirname;
}
dirInfo* getblank(dirInfo*p){
	dirInfo * tmp = p;
	while(tmp->layer!=-1){
		tmp = tmp->p_next;
	}	
	return tmp;
}
dirInfo* getTail( dirInfo*p){
	dirInfo* tmp = p;
	dirInfo* tail =p;
	while(tmp!=NULL){
		tail = tmp;
		tmp = tmp->p_next;
	}
	return tail;
}
void initDI(dirInfo* p){
	int i = 0;int j = 0;
	dirInfo * tmp = p;
	while(tmp!=NULL){
		tmp->index = i; i++;
		tmp->layer = -1;
		tmp->prefixCount = -1;
		for(j=0;j<100;j++)tmp->dirname[j]=0x00;
		tmp = tmp->p_next;
}
}
void destroyDI(dirInfo*p){
	dirInfo * tmp = p;
	dirInfo * des = p;
	while(des!=NULL){
	//	printf("in destroy\n");
		tmp = tmp->p_next;
		free(des);
		des = tmp;
	}
}
void printAll(dirInfo*p){
	dirInfo* tmp = p;
	while(tmp!=NULL){
	printf("index= %d  layer= %d  prefixCount= %d  ",tmp->index,tmp->layer,tmp->prefixCount);
	if(strlen(tmp->dirname)==0){
		printf("dirname strlen =0\n");
	}
	else
		printf("dirname is %s\n",tmp->dirname);
		printf("%p ->next is %p   ->prev is %p\n",tmp,tmp->p_next,tmp->p_prev);
		tmp = tmp->p_next;
	}
}
