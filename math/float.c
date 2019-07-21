#include"../all.h"
int main(){
	float a = 0.0;
	if(a - 0.0 > 0.000000001){
		printf("a - 0.0 > 0.000000001\n");
	}
	if(a - 0.0 > 0.00000001){
		printf("a - 0.0 > 0.00000001\n");
	}
	if(a - 0.0 > 0.0000001){
		printf("a - 0.0 > 0.0000001\n");
	}
	if(a - 0.0 > 0.000001){
		printf("a - 0.0 > 0.000001\n");
	}
	if(a - 0.0 > 0.00001){
		printf("a - 0.0 > 0.00001\n");
	}
	if(a - 0.0 > 0.0001){
		printf("a - 0.0 > 0.0001\n");
	}
	float b = a - 0.0;
	printf("a = 0X%x,a = %f; b = 0X%x,b = %f\n",a,a,b,b);
	if(a == 0){
		printf("a == 0\n");
	}
	
	float c = 1;
	float d = 1.0;
	printf("c = 0X%x,d = 0X%x\n",c,d);
	//c = 0X0,d = 0X3ff00000
	
	if(d == 1){
		printf("d == 1\n");
	}
	if(d == 1.0){
	printf("d == 1.0\n");
	}
	/*
	d == 1
	d == 1.0
	*/
	return 0;
}
