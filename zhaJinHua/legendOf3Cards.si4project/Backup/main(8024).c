#include"../all.h"
void* chatThread(void* arg){
    system("gnome-terminal -x ./waiting");
    printf("chat thread exited\n");
	return NULL;
}
int main(){
	pthread_t thread_1;
    pthread_create(&thread_1,NULL,chatThread,NULL);
    while(1){
        sleep(1);
        printf("Hello\n");
    }
    return 0;
}
