#include<iostream>
#include<cstring>
#include<cstdlib>
#include "../all.h"
using namespace std;
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
int main(){
	Student s("shensheng",27,11);
	s.who();
	return 0;
}
