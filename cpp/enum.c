#include "../all.h"
typedef enum{Coke,Milk,water,wine,blood} drinkEnum;//对枚举类型使用typedef是没有必要的。
enum{spade,heart,club,diamond};
int main(){
	enum {spring,summer,autumn,winter} ;
	printf("summer = %d\n",summer);
	printf("water = %d\n",water);
	printf("diamond = %d\n",diamond);
	printf("sizeof drinkEnum = %d\n",sizeof(drinkEnum));//4
	
	drinkEnum de = 100;
	printf("summer = %d\n",summer);
#if 0
	printf("addr:%p,addr:%p,addr:%p\n",&spring,&summer,&autumn);
	/*
	enum.c: In function `main':
	enum.c:14: invalid lvalue in unary `&'
	enum.c:14: invalid lvalue in unary `&'
	enum.c:14: invalid lvalue in unary `&'
	*/
#endif
	struct {int a;int b;} player;
	player.a = 15;
	player.b = 16;

return 0;
}
