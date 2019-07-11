#include"../all.h"
int main(){
	time_t rawTime;
	struct tm* timeInfo;
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	printf("time = %s\n",asctime(timeInfo));
	printf("time = %u\n",time(NULL));
	
	return 0;
}
//1566621914
