#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
int main(){
	int a = 10;
	int & refA = a;
	refA++;
	cout << a << endl;
	int & ref2 = refA;
	cout << ref2 << endl;

	return 0;
}