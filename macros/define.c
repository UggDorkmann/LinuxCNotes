#include"../all.h"
#define vn(a,b) a##b
typedef struct{
	int nPort1;
	int nPort2;
	int nPort3;
}myS_;
int main(){
	myS_ g_TotalChnlInfo = {1,2,3};
	int i = 0;
	for(i=0;i<3;i++)
		printf("prot:%d\n",vn(g_TotalChnlInfo.nPort,i));
	
}
