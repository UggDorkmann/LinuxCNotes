#include"../all.h"
int main(){
	int fd = open("data.bin",O_RDWR);
	if(fd<0){
		perror("open went wrong");
	}
	FILE * pBin = fopen("data.bin","r");
	FILE * p = fopen("mydata.txt","w+");
	unsigned char buf[2] = {0};
	int n = 0;
	while(fread(buf,1,1,pBin)>0){
		n++;
		if(buf[0] >= 0x20 && buf[0] <= 0x7e){
			fprintf(p,"%c",buf[0]);
		}
		else{
			fprintf(p," %02X",buf[0]);	
		}
	}
	printf("n = %d\n",n);
	close(fd);
	
return 0;	
}
