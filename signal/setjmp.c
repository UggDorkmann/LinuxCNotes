#include"../all.h"
void a();
void b();
void c();

jmp_buf jb;
void a(){
	b();
	printf("in a()\n");
}
void b(){
	c();
	printf("in b()\n");
}
void c(){
	printf("in c()\n");
	longjmp(jb,1);
}
int main(){
	int res = setjmp(jb);
	if(res == 0){
		printf("in main\n");
		a();
	}
	res = setjmp(jb);
	printf("res = %d\n",res);
	return 0;
	
}
/*
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/signal: ./a.out
in main
in c()
res = 0
*/
#if 0
setjmp用于保存当前AR到jb变量中；
而longjmp用于设置当前AR为jb，并跳转到调用setjmp()；
其结果就相当于回到了setjmp()刚执行完毕，只是偷偷的修改了setjmp的返回值。
setjmp()第一次调用时总是返回0，而通过longjmp(jb,r)跳转后其返回值总是被修改为r，并且r不能为0。
这样程序中就很容易根据setjmp()的返回值来判断是否是longjmp()导致了跳转才执行到此。
#endif
