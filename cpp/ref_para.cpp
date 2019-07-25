#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

void swap1(int & x,int & y){
	int tmp = x;
	x = y;
	y = tmp;
	return;
}
int main(){
	int a = 3;
	int b = 12;
	cout << a << "," << b << endl;
	swap1(a,b);
	cout << a << "," << b << endl;
return 0;
}
