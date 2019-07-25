#include<iostream>
using namespace std;
namespace ns1{
	void func(void){
		cout << "ns1::func" << endl;
	}
	int num = 10;
}
int num = 20;//会被放进无名命名空间中
namespace ns2{
	void func(void){
		cout << "ns2::func" <<endl;
	}
}
int main(){
	using ns1::func;
	func();
	cout << "num = "<< num << endl;
	using ns1::num;
	cout << "num = "<< num << endl;
	cout << "num = "<< ::num << endl;
	return 0;
}
