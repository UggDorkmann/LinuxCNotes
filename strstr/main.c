#include"../all.h"
void informOfflineNews(int offlineFd){
    int i = 0;
    char buf[20] = {0};
    for(i=0;i<3;i++)buf[i]=0xAA;
    buf[3] = 0x01;
	sprintf(buf+4,"%04x\r\n",offlineFd);
	printf("strlen(buf) = %d\n",strlen(buf));
}
int main(){
	char msg[20] = {0xAA,0xAA,0x02,'a','b','c'};
	char buf[5] =  {0xAA,0xAA};
	
	if(strstr(msg,buf)){
		printf("msg has buf\n");
	}
	informOfflineNews(1113);
return 0;	
}
