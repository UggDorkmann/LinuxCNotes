#include<iostream>
#include<cstring>
#include<cstdlib>
#include "../all.h"
using namespace std;

class A{
	public:
	A(int data = 0){
		cout << "cons" << endl;
		m_data = data;
	}
	A(const A& that){
		cout << "cpy cons" << endl;
		m_data = that.m_data;
	}
	int m_data;
};
class B{
	public:
	A m_a;
};
int main(){
	A a1(123);
	A a2(a1);
	cout << a1.m_data <<endl;
	cout << a2.m_data << endl;
	
	B b1;
	b1.m_a.m_data = 456;
	B b2(b1);
	cout << b1.m_a.m_data << endl;
	cout << b2.m_a.m_data << endl;
	return 0;
}
