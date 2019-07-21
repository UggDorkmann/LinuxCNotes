#include"../all.h"
int main(){
	system("cal > test.txt && wc test.txt && cat test.txt");
	truncate("test.txt",200);
	system("wc test.txt && cat test.txt");
	truncate("test.txt",20);
	system("wc test.txt && cat test.txt");

	return 0;
}
