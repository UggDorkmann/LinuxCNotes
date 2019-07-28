#include"../all.h"
int main(){
	int i = 0;
	char buf[50] = {0};
	for(i=0;i<32;i++){
		memset(buf,0,sizeof(buf));
		psignal(i,buf);
	}
	for(i=0;i<32;i++){
		printf("%d: %s\n",i,strsignal(i));
	}
return 0;	
}
