#include"../all.h"
int foo(){
	int a = 0;
	printf("a addr = %p\n",&a);
	return a;
}
int main(){
	//printf("res addr = %p\r",&foo());
#if 0
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/cpp: gcc return.c
return.c: In function `main':
return.c:8: invalid lvalue in unary `&'
#endif
	return 0;
}
