#include"../all.h"
int main(){
	printf("Hello\n");
	system("rm tmp.txt");
	freopen("tmp.txt","a+",stdout);
	printf("line:%d\n",__LINE__);
	//FILE* p = fopen("tmp.txt","a+");
	//fflush(p);
	//fclose(p);
return 0;	
}
