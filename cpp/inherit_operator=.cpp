#include<iostream>
#include<cstring>
#include<cstdlib>
#include "../all.h"
using namespace std;

class Base{
	public:
	int m_i;
	Base(int i = 0):m_i(i){}
	Base(const Base& that):m_i(that.m_i){
		cout << "base copy" << endl;
	}
	Base & operator=(const Base & that){
		if(&that != this){
			m_i = that.m_i;
			cout << "base operator=" << endl;
		}
		return *this;
	}
	
};
class Derived:public Base{
	public:
	Derived(int i=0):m_i(i){}
	Derived(int i1,int i2):m_i(i1),Base(i2){}
	Derived(const Derived& that):m_i(that.m_i),Base(that){}//引用的向上造型
	Derived & operator=(const Derived& that){//只有构造函数可以有初始化列表
		if(this != &that){
			m_i = that.m_i;
			Base::operator=(that);//向上造型，完全可以在Base中定义一个函数，用来处理这种需要在子类中给自己赋值的情况，而operator=在功能和名字上都有这样的便利。
			//Base(that);//不能写成这样，这样只是创建一个无名Base变量。
		}
		return *this;
	}
	int m_i;
};
int main(){
	Derived d1(10,20);
	cout << d1.m_i << "," << d1.Base::m_i << endl;
	Derived d2 = d1;
	cout << d2.m_i << "," << d2.Base::m_i << endl;
	Derived d3;
	d3 = d1;
	cout << d3.m_i << "," << d3.Base::m_i << endl;

	return 0;
}
