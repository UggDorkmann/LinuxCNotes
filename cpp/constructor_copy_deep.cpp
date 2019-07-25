#include<iostream>
#include<cstring>
#include<cstdlib>
#include "../all.h"
using namespace std;

class Int{
	public:
	Int(int data = 0):m_data(new int(data)){
		cout << "in cons" << endl;
	}
	Int(const Int& that):m_data(new int(*(that.m_data))){
		cout << "in deep copy" << endl;
	}
	~Int(){
		cout << "in des" << endl;
		delete m_data;
		m_data = NULL;
	}
	void p(){
		cout << "m_data = " << *m_data << endl;
	}
	int * m_data;
};

int main(){
	Int i(123);
	i.p();
	Int i2(i);
	i.p();
	return 0;
}
