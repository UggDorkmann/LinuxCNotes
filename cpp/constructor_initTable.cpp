#include<iostream>
#include<cstring>
#include<cstdlib>
#include "../all.h"
using namespace std;
/*
使用初始化列表的3种情况:
1 类类型的成员没有无参构造函数
2 有const修饰的成员
3 有引用符修饰的成员
*/
class Student{
	public:
	Student(const string & name,int age,int no){
		cout << "constructor" << endl;
		m_name = name;
		m_age = age;
		m_no = no;
	}
	void who(){
		cout << "I am " << m_name << ",age:"<< m_age << ",number:" << m_no <<endl;
	}
	private:
	string m_name;
	int m_age;
	int m_no;
	
};
int g_int = 200;
class Student2{
	public:
#if 0
	Student2(){
		m_student("Tom",11,1)
	}
/*
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/cpp: g++ constructor_initTable.cpp
constructor_initTable.cpp: In constructor `Student2::Student2()':
constructor_initTable.cpp:32: no matching function for call to `Student::
   Student()'
constructor_initTable.cpp:6: candidates are: Student::Student(const Student&)
constructor_initTable.cpp:16:                 Student::Student(const
   std::string&, int, int)
constructor_initTable.cpp:33: no match for call to `(Student) (const char[4],
   int, int)'
constructor_initTable.cpp:34: parse error before `;' token
*/
#elif 0
	Student2():m_student("Tom",11,1){
		m_int = g_int;
	}
/*
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/cpp: g++ constructor_initTable.cpp
constructor_initTable.cpp: In constructor `Student2::Student2()':
constructor_initTable.cpp:50: assignment of read-only data-member `
   Student2::m_int'
*/
#elif 0
	Student2():m_student("Tom",11,1),m_int(g_int){
		m_ref = g_int;
	}
/*
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/cpp: g++ constructor_initTable.cpp
constructor_initTable.cpp: In constructor `Student2::Student2()':
constructor_initTable.cpp:59: uninitialized reference member `Student2::m_ref'
*/
#else
	Student2():m_student("Tom",11,1),m_int(g_int),m_ref(g_int){}
#endif
	int & m_ref;
	const int m_int;
	Student m_student;
};
int main(){
	Student s("shensheng",27,11);
	s.who();
	return 0;
}
