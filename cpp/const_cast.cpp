#include<iostream>
#include<cstring>
#include<cstdlib>
#include "../all.h"
using namespace std;

int main(){
#if 1
	const volatile int ci = 100;
#else
	const  int ci = 100;
#endif
	int * pci = const_cast<int *>(&ci);
	*pci = 200;

	cout << "ci =" <<ci << endl;
	cout << "*pci="<<*pci<<endl;
	cout << "&ci=" << (void*)&ci << endl;
	cout << "pci=" << pci << endl;

	return 0;
}
