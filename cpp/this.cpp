#include<iostream>
#include<cstring>
#include<cstdlib>
#include "../all.h"
using namespace std;
class Counter{
	public:
	Counter(int data=0):m_data(data){}
	Counter & add(){
		m_data++;
		return *this;
	}
	int m_data;
	mutable int m_data2;//mutable修饰的变量可以在常函数中修改
	int sum(int a,int b)const{
		m_data2++;
#if 0
		m_data++;
/*
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/cpp: g++ this.cpp
this.cpp: In member function `int Counter::sum(int, int) const':
this.cpp:15: increment of data-member `Counter::m_data' in read-only structure
*/
#endif
		return a+b+1;
	}
	void funcConst()const{
		cout << "in funcConst" << endl;
	}
	void funcNormal(){
		cout << "in funcNormal" << endl;
	}
	//void func()const{} 和 void func(){} 构成重载
	void func()const{
		cout << "in func const" << endl;
	}
#if 1
	void func(){
		cout << "in func" << endl;
	}
#endif
};
int main(){
	Counter c;
	c.add().add().add();
	cout << c.m_data << endl;
	
	Counter a;
	a.funcConst();
	a.funcNormal();//普通对象调用const和非const函数都可以
	
	const Counter a2;//const对象只能调用const函数
	a2.funcConst();
	
	const Counter & a_ref = a;//const引用只能调用const函数
	a_ref.funcConst();
	
	const Counter* a_p = &a;//const指针只能调用const函数
	a_p->funcConst();
#if 0
	a2.funcNormal();
	a_ref.funcNormal();
	a_p->funcNormal();
/*
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/cpp: g++ this.cpp
this.cpp: In function `int main()':
this.cpp:53: passing `const Counter' as `this' argument of `void
   Counter::funcNormal()' discards qualifiers
this.cpp:54: passing `const Counter' as `this' argument of `void
   Counter::funcNormal()' discards qualifiers
this.cpp:55: passing `const Counter' as `this' argument of `void
   Counter::funcNormal()' discards qualifiers
*/
#endif
	a2.func();
	a.func();
	return 0;
}
