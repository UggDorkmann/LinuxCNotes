#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
int main(){
	bool b = false;
	cout << "b = " << b << ",size = " << sizeof(b) << endl;
	b = 123;
	cout << "b = " << b << ",size = " << sizeof(b) << endl;
	
	cout << boolalpha << "b= " << b << ",size= "<< sizeof(b) << endl;
	b = 3-3;
	cout << boolalpha << "b= " << b << ",size= "<< sizeof(b) << endl;
	return 0;
}
#if 0
/mnt/hgfs/shareDir/shensheng/LinuxCNotes/cpp: ./a.out
b = 0,size = 1
b = 1,size = 1
b= true,size= 1
b= false,size= 1

#endif
