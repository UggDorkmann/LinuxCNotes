#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"unistd.h"
#define total_num 2374

void mybuf0(char* p,int size){
	int i = 0;
	for(i=0;i<size;i++)p[i] = 0x00;
}
int main(){
	system("rm res.txt");
	FILE* p_in = fopen("china_word_utf_8_filter_2374.txt","r");
	//FILE* p_in = fopen("chinese_words.txt","r");
	
	FILE* p_ou = fopen("res.txt","a+");
	srand(time(0));
	char buf_4[16] = {0};
	char buf_1[4] = {0};
	int fd = fileno(p_in);
	int fsize = lseek(fd,0,SEEK_END);
	//printf("file size is %d\n",fsize);
	int wordNum = fsize/4;
	//SEEK_SET
	int offset = 40;
	int i=0;int j=0;
	while(i<200){
		for(j=0;j<2;j++){
			offset = rand()%total_num;
			fseek(p_in,offset*4,SEEK_SET);
			fread(buf_1,4,1,p_in);
			fwrite(buf_1,4,1,p_ou);
			mybuf0(buf_1,4);
		}
		i++;
		fprintf(p_ou,"    ");
		if(i%5==0)
			fprintf(p_ou,"\n");
	}
	
	//fread(buf_1,4,1,p_in);
	//fwrite(buf_1,4,1,p_ou);
	//offset+=4;
	//mybuf0(buf_1,4);
	//fseek(p_in,offset,SEEK_SET);
	//fread(buf_1,4,1,p_in);
	//fwrite(buf_1,4,1,p_ou);
	
	fclose(p_ou);
	fclose(p_in);
return 0;
}
