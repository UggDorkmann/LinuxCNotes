#include"../all.h"
int g_index;
pthread_mutex_t	fastmutex;
int g_ip;
int g_port;
void* dosth(void* p){
	while(1){
		pthread_mutex_lock(&fastmutex);
		g_ip = 1;
		usleep(rand()%100000);
		g_port = 1;
		pthread_mutex_unlock(&fastmutex);

		usleep(rand()%100000);
		g_ip = 0;
		usleep(rand()%100000);
		g_port = 0;
		usleep(rand()%100000);
	}
	return NULL;
}
void * readvar(void* p){
	while(1){
		
		pthread_mutex_lock(&fastmutex);

		if(g_ip > 0){
			printf("g_port = %d\n",g_port);
		}
		else printf("else,g_port = %d\n",g_port);
		pthread_mutex_unlock(&fastmutex);

		usleep(rand()%1000000);
	}
}
int main(){
	srand(time(0));
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,dosth,NULL);
	pthread_create(&tid2,NULL,readvar,NULL);
	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

return 0;
}
