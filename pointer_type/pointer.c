#include"../all.h"
typedef int (* func_a)(int);
static int mySum(int para){
	int i = 0;
	int res = 0;
	for(i=0;i<=para;i++){
		res += i;
	}
	return res;
}
int main(){
	int (* p_arr)[10] = NULL;
	int arr[10] = {1,2,3,4,5,6,7,8,9,0};
	func_a a = mySum;
	printf("sum of 100 = %d\n",a(100));
	int (* p_func_arr)(int);
return 0;	
}
