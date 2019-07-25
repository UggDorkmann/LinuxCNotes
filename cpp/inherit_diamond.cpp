#include<iostream>
#include<cstring>
#include<cstdlib>
#include "../all.h"
using namespace std;
#define Diamond 0
#if Diamond == 1
class A{
	public:
	A(int data):m_data(data){
		cout << "A cons" << endl;
	}
	protected:
	int m_data;
};
class B:public A{
	public:
	B(int data):A(data){}
	void set(int data){
		m_data = data;
	}
	
};
class C:public A{
	public:
	C(int data):A(data){}
	int get(){
		return m_data;
	}
};
class D:public B,public C{
	public:
	D(int data):B(data),C(data){}
	
};
#else
class A{
	public:
	A(int data):m_data(data){
		cout << "A cons" << endl;
	}
	protected:
	int m_data;
};
class B:public virtual A{//修改1
	public:
	B(int data):A(data){}
	void set(int data){
		m_data = data;
	}
};
class C:public virtual A{//修改2
	public:
	C(int data):A(data){}
	int get(){
		return m_data;
	}
};
class D:public B,public C{
	public:
	D(int data):B(data),C(data),A(data){}//修改3
	/*
	如果修改3没有：
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/cpp: g++ inherit_diamond.cpp
inherit_diamond.cpp: In constructor `D::D(int)':
inherit_diamond.cpp:63: no matching function for call to `A::A()'
inherit_diamond.cpp:38: candidates are: A::A(const A&)
inherit_diamond.cpp:40:                 A::A(int)
	*/
};

#endif
int main(){
	D d(100);
	cout << d.get() << endl;
	d.set(200);
	cout << d.get() << endl;
	return 0;
}
