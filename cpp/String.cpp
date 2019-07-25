#include<iostream>
#include<cstring>
#include<cstdlib>
#include "../all.h"
using namespace std;
class String{
public:
	String(const char* src =""){
		m_str = new char[strlen(src) + 1];
		memcpy(m_str,src,strlen(src));
		m_str[strlen(src)] = 0;
	}
	String(const String& that){
		delete[] m_str;
		m_str = new char[strlen(that.m_str)+1];
		memcpy(m_str,that.m_str,strlen(that.m_str));
		m_str[strlen(that.m_str)] = 0;
	}
	String& operator=(const String& that){
		if(&that != this){
			delete [] m_str;
			m_str = new char[strlen(that.m_str)+1];
			memcpy(m_str,that.m_str,strlen(that.m_str));
			m_str[strlen(that.m_str)] = 0;
		}
		return *this;
	}
	~String(){
		delete [] m_str;
		m_str = NULL;
	}
	char* c_str(){
		return m_str;
	}
	char * m_str;
};
int main(){
	String s = "hello";
	cout << s.c_str() << endl;
	String s2(s);
	cout << s2.c_str() << endl;
	String s3("milan");
	cout << s3.c_str() << endl;
	s3 = s;
	cout << s3.c_str() << endl;
	return 0;
}
