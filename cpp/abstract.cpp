#include<iostream>
#include<cstring>
#include<cstdlib>
#include "../all.h"
using namespace std;
#define chunVFunc 1
#if chunVFunc == 0
class Base{
	public:
	int m_data;
	void virtual print(int data){
		cout << data << endl;
	}
};
class Derived:public Base{
	public:
	int m_data;
	void print(int data){
		cout << "in derived" << endl;
	}
};
int main(){
	Base b;
	Derived d;
	b.print(12);
	d.print(23);
	Base* pb = &d;
	pb->print(56);
	return 0;
}
#else
class Base{
	public:
	int m_data;
	virtual void  print(int data){
		cout << data << endl;
	}
	virtual void  print2(int a){}
};
class Derived:public Base{
	public:
	int m_data;
	void print(int data){
		cout << "in derived" << endl;
	}
	void  print2(int a){
		cout << "in derived,print2" << endl;
	}
};
int main(){
	Derived d;
	d.print(23);
	Base* pb = &d;
	pb->print(56);
	return 0;
}

#endif
