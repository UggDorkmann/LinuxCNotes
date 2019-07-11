#include"../all.h"
typedef struct{
	char name[24];
	int age;
	struct{
		int shoot;
		char nat[30];
	}property;
	
}myS_;
static void ssp(myS_ * p){
	printf("in ssp\n");
	printf("p->name size is %d\n",sizeof(p->name));
	printf("p->property.nat size is %d\n",sizeof(p->property.nat));
}
int main(){
	myS_ mys;
	ssp(&mys);
	
	return 0;
}
