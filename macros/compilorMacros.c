#include"../all.h"
static void ssp(){
	printf("line:%d,file:%s,time:%s,func name:%s\n",
		__LINE__,__FILE__,__TIME__,__FUNCTION__);
	//时间是编译发生的时间，一般来说没有意义
}
int main(){
	ssp();
return 0;
}
