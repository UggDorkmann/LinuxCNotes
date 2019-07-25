#include<iostream>
#include<cstring>
#include<cstdlib>
#include "../all.h"
using namespace std;
#define ehanshi 0

#if ehanshi == 1
/*单例模式-饿汉式*/
class A{
	public:
	//3:提供访问单例对象的方法
	static A & getinstance(){
		return s_instance;
	}
	void print()const{
		cout << m_data << endl;
	}
	private:
	//1:将构造函数定义为私有
	A(int data=0):m_data(data){}
	int m_data;
	//2：用静态私有变量维护唯一的对象
	static A s_instance;
	
};
A A::s_instance(12345);//相当于 int tmp(3);
#else
/*单例模式-懒汉式*/
class A{
	public:
	//3:提供访问单例对象的方法
	static A& getinstance(){
		if(s_instance == NULL){
			s_instance = new A(12345);
		}
		s_counter++;
		return *s_instance;
	}
	void release(){
		if(--s_counter == 0){
			delete s_instance;
			s_instance = NULL;
		}
	}
	void print()const{
		cout << m_data << endl;
	}
	private:
	//1:将构造函数定义为私有
	A(int data=0):m_data(data){}
	A(const A& that):m_data(that.m_data){}//拷贝构造也可以使用初始化列表
	int m_data;
	//2:用静态私有变量维护唯一的对象
	static A* s_instance;
	static int s_counter;
};
A* A::s_instance = NULL;
int A::s_counter = 0;
#endif
class myclass{
	public:
	static myclass & getinstance(){//静态函数可以访问私有的构造函数
		myclass *tmp = new myclass;
		return *tmp;
	}
	static void getprivateFunc(){
#if 0		
		myprint(); //静态函数不能访问私有的普通非静态函数，由此可见构造函数也是static类型的
/*
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/cpp: g++ static_member.cpp
static_member.cpp: In static member function `static void
   myclass::getprivateFunc()':
static_member.cpp:68: cannot call member function `void myclass::myprint()'
   without object
*/
#endif
	}
	private:
	myclass(){
		cout << "in private cons" << endl;
	}
	void myprint(){
		cout << "in private print" << endl;
	}
};
int main(){
#if ehanshi == 1
	A& a1 = A::getinstance();
	A& a2 = A::getinstance();
	a1.print();
	a2.print();
	cout << "a1 addr :"<< &a1<<endl;
	cout << "a2 addr :"<< &a2<<endl;
#else
	A & a1 = A::getinstance();
	A & a2 = A::getinstance();
	a1.print();
	a1.release();
	a2.print();
	a2.release();
#endif
	myclass & mc = myclass::getinstance();
return 0;	
}
