#include<iostream>
#include<cstring>
#include<cstdlib>
#include "../all.h"
using namespace std;

int main(){
	char text[] = "1234\00012345678\000123456\000";
	struct t{
		char type[5];
		char acc[9];
		char pass[7];
	};
	t* p = reinterpret_cast<t*>(text);
	cout << p->type << endl;
	cout << p->acc << endl;
	cout << p->pass << endl;

	return 0;
}
