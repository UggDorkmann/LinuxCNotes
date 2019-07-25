#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

struct a{
	int data;
	int& foo(){
		return data;
	}
};
int sum1(int x,int y){
	int sum = x+y;
	return sum;
}
int& sum2(int x,int y){
	int sum = x+y;
	return sum;
}
int main(){
	a aa = {0};
	cout << aa.data << endl;
	aa.foo() = 123;
	cout << aa.data << endl;
	int x = 3,y = 4;
	cout << sum1(x,y) << endl;
	cout << sum2(x,y) << endl;
return 0;
}
