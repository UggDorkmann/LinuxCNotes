#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

extern "C"{
	int jueduizhi(int a,int b){
	if(a>b)return a-b;
	return b-a;
	}
	int add3nums(int a,int b,int c){
		return a+b+c;
	}
}
