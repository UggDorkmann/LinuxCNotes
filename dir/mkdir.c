#include"../all.h"
int main(){
	char buf[100] = {0};
	sprintf(buf,"touch 拜仁慕尼黑.txt",strlen("touch 拜仁慕尼黑.txt"));
	system(buf);
	return 0;
}
