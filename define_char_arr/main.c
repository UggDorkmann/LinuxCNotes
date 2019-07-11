#include"../all.h"
#define questOnline {0xAA,0xAA,0x06,0x06,0}
int main(){
	char buf[5] = {0xAA,0xAA,0x06,0x06,0};
	printf("strlen(buf) = %d\n",strlen(buf));
	char buf2[5] = questOnline;
	printf("strlen(buf2) = %d\n",strlen(buf2));
	//printf("strlen(questOnline) = %d\n",strlen(questOnline));//error
return 0;
}
