#include<iostream>
#include<cstring>
#include<cstdlib>
#include "../all.h"
#define Explicit 1
using namespace std;
class Integer{
	public:
	Integer(){
		m_data = 100;
	}
	#if Explicit == 0
	Integer(int data){
	#else
	explicit Integer(int data){
	#endif
		m_data = data;
	}
	void p(){
		cout << m_data << endl;
	}
	private:
	int m_data;
	
};
int main(){
	Integer i;
	i.p();
	#if Explicit == 0
	i= 123;//编译器自动寻找一个参数是int的构造函数
	i.p();
	#endif
	i = (Integer)200;
	i.p();
	i = Integer(300);
	i.p();
	return 0;
}
