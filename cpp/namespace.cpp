#include<iostream>
using namespace std;
namespace ns1{
	void func(void){
		cout << "ns1::func" << endl;
	}
}
namespace ns2{
	void func(void){
		cout << "ns2::func" <<endl;
	}
}
void milan(){
	using ns2::func;
	func();
}
int main(){
	using ns1::func;
	func();
	milan();
	return 0;
}
