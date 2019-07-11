#include"../all.h"
int g_index;
pthread_mutex_t	fastmutex;
void* dosth(void* p){
	int index = 0;
	int i = 0;
	pthread_mutex_lock(&fastmutex);
	while(g_index<10000){
		g_index++;
		index = g_index;
		i++;
		printf("%x : i = %d,index = %d,g_index = %d\n",(unsigned int)pthread_self(),i,index,g_index);
	}
	pthread_mutex_unlock(&fastmutex);
	printf("@@@@@@@@@@@@@@@@\n");
	printf("%x : i is %u\n",(unsigned int)pthread_self(),i);
	return NULL;
}
int main(){
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,dosth,NULL);
	pthread_create(&tid2,NULL,dosth,NULL);
	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

return 0;
}
