/* time -p ./a.out */
#include"../all.h"
int main(){
	int i = 0;
	srand(time(0));
	while(i<100){
		i++;
		usleep(rand()%100);
	}
	return 0;
}
