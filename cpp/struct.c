#include"../all.h"
struct a{
	int data;
	int len;
};
typedef struct{
	char m_a[5];
	char m_b[9];
	char m_c[7];
	
}tmpS;
int main(){
	//a aa; //C++允许这样定义一个类型，否则所有class前面都要加typedef。C必须要用typedef
	char text[] = "1234\00012345678\000123456";//在C和C++的字符串中都要用三个八进制数字（最大512）表示一个字符
	tmpS * p = (tmpS*)text;
	printf("p->m_a = %s\np->m_b = %s\np->m_c = %s\n",p->m_a,p->m_b,p->m_c);
	return 0;	
}
