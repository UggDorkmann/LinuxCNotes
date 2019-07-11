#include"../all.h"
typedef struct{
	char name[10];
	char age;
	int ability;
	int salary;
}pesPlayer;

void genName(char* name,int size){
	memset(name,0,size);
	name[0] = 'N';
	int i = 0;
	for(i=1;i<size-1;i++){
		name[i] = rand()%26+'a';
	}
}
void genPlayer(pesPlayer* p){
	genName(p->name,sizeof(p->name));
	p->age = rand()%100+15;
	p->ability = rand()%2000 + 200;
	p->salary = 1000 * (rand()%1000);
}
void writeInfo(int fd,pesPlayer* p){
	lseek(fd,0,SEEK_END);
	write(fd,p,sizeof(pesPlayer));
	char buf[4] = {0xFE,0xDC,0xBA,0x98};
	write(fd,buf,4);
}
void writeInfos(int fd,pesPlayer p[],int num){
	int i = 0;
	for(i = 0;i<num;i++){
		genPlayer(&p[i]);
		writeInfo(fd,&p[i]);
	}
}

void readInfo(int fd,pesPlayer* p){
	char buf[24] = {0};
	read(fd,buf,sizeof(pesPlayer));
	printf("fd = %d, buf = %s\n",fd,buf);
	memcpy((char*)p,buf,sizeof(pesPlayer));
	//read(fd,(char*)p,sizeof(pesPlayer));
	lseek(fd,4,SEEK_CUR);
}
void showInfo(pesPlayer * p){
	printf("name = %s,age = %d ,ability = %d, salary = %d\n",p->name,\
		(int)(p->age),p->ability,p->salary);
}
void readInfos(int fd,pesPlayer p[],int num){
	int i = 0;
	for(i=0;i<num;i++){
		readInfo(fd,&p[i]);
		showInfo(&p[i]);
	}
}
void readThisInfo(int fd,pesPlayer* p){
	
}
void modInfo(int fd,pesPlayer* p){
	
}

void showInfos(pesPlayer p[],int num){
	int i = 0;
	for(i=0;i<num;i++){
		printf("name = %s,age = %d ,ability = %d, salary = %d\n",p[i].name,\
		(int)(p[i].age),p[i].ability,p[i].salary);
	}
}
int main(){
	srand(time(0));
	int fd = open("./data.bin",O_RDWR | O_CREAT);
	if(fd<0){
		printf("fd<0\n");
		perror("open went wrong");
	}
	printf("sizeof pesPlayer is %d\n",sizeof(pesPlayer));
	pesPlayer p[5];
	memset(&p[0],0,5*sizeof(pesPlayer));
	//writeInfos(fd,p,5);
	lseek(fd,0,SEEK_SET);
	readInfos(fd,p,5);
	showInfos(p,5);
	close(fd);
return 0;	
}
