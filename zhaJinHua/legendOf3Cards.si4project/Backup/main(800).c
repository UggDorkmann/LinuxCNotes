#include"../all.h"
void* chatThread(void* arg){
    system("gnome-terminal -x ./chat.out");
    printf("chat thread exited\n");
	return NULL;
}
int clientFd[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
int main(){
	pthread_t thread_chat;
    //pthread_create(&thread_chat,NULL,chatThread,NULL);
    fd_set readfds;
    struct timeval s_timeval;
    printf("sizeof fd_set = %d\n",sizeof(fd_set));
    
    int s_fd = socket(AF_INET,SOCK_STREAM,0);
    char buf[128] = {0};
    char ip[128] = {0};
    struct sockaddr_in serv,clie;
    int cli_len = 0;
    if(s_fd == -1){
        perror("socket");
        return -1;
    }
    serv.sin_family = AF_INET;
    serv.sin_port = htons(GamePort);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    int res_bind = bind(s_fd,(struct sockaddr*)&serv,sizeof(serv));
    if(res_bind == -1){
        perror("bind");
        return -2;
    }
    listen(s_fd,8);
    while(1){
        cli_len = sizeof(clie);
        int c_fd = accept(s_fd,(SA*)&clie,&cli_len);
        if(c_fd == -1){
            perror("accept");
            return -3;
        }

        FD_ZERO(&readfds);
        FD_SET(c_fd,&readfds);
        s_timeval.tv_sec = 1;
        s_timeval.tv_usec = 0;

        
        printf("visitor: %s , c_fd = %d\n",inet_ntop(AF_INET,&clie.sin_addr,ip,128),c_fd);
        
        if(select(c_fd+1,&readfds,NULL,NULL,&s_timeval) > 0){
            memset(buf,0,sizeof(buf));
            int r = read(c_fd,buf,128);
            if(strcasecmp(buf,"exit") == 0)break;
            int i=0;
            for(i=0;i<r;i++){
                buf[i] = toupper(buf[i]);
            }
            write(c_fd,buf,r);
        }
#if 0        
        while(1){
            memset(buf,0,sizeof(buf));
            int r = read(c_fd,buf,128);
            if(strcasecmp(buf,"exit") == 0)break;
            int i=0;
            for(i=0;i<r;i++){
                buf[i] = toupper(buf[i]);
            }
            write(c_fd,buf,r);
        }
#endif
        close(c_fd);
    }
    return 0;
}
