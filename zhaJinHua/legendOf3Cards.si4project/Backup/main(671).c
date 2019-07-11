#include"../all.h"
#define maxGambler 2 //the max number of gamblers on one table
void* chatThread(void* arg){
    system("gnome-terminal -x ./chat.out");
    printf("chat thread exited\n");
	return NULL;
}
int clientFd[maxGambler];
int add_fd(int fd){
    int i = 0;
    for(i=0;i<maxGambler;i++){
        if(clientFd[i] == -1){
            clientFd[i] = fd;
            printf("clientFd[%d] = %d\n",i,fd);
            return 0;
        }
    }
    if(i==maxGambler){
        printf("clientFd is full\n");
        return -1;
    }
}
cliInfo cliInfos[maxGambler] = {0};

void judgeCloseFd(){
    int i = 0;
    for(i=0;i<maxGambler;i++){
        if(cliInfos[i].heartStopCount >= 5){
            printf("clientFd[%d] = %d is dead\n",i,clientFd[i]);
            close(clientFd[i]);
            clientFd[i] = -1;
        }
    }
}
int allSet(){// All gamblers on table?
    int i = 0;
    for(i=0;i<maxGambler;i++){
        if(clientFd[i] == -1) return 0;
    }
    return 1;
} 
int getMaxFd(){
    int ret = clientFd[0];
    int i =0 ;
    for(i=1;i<maxGambler;i++){
        if(ret < clientFd[i]) ret = clientFd[i];
    }
    return ret;
}
static void myFD_SET(fd_set * p){
    int i = 0;
    for(i=0;i<maxGambler;i++){
        FD_SET(clientFd[i],p);
    }
}
/*
    name    LetsBegin
    return  0 :  someone lost last penny
            -1 : someone is offline
*/
int LetsBegin(){
    printf("let us begin!!!\n");
    char tmpBuf[128] = {0};
    fd_set readfds;
    struct timeval s_timeval;
    s_timeval.tv_sec = 1;
    s_timeval.tv_usec = 0;
    while(1){
        FD_ZERO(&readfds);
        myFD_SET(&readfds);
        if(select(getMaxFd()+1,&readfds,NULL,NULL,&s_timeval) > 0){
            int i = 0;
            for(i=0;i<maxGambler;i++){
                if(FD_ISSET(clientFd[i],&readfds)){
                    
                    memset(tmpBuf,0,sizeof(tmpBuf));
                    int r = read(clientFd[i],tmpBuf,128);
                    int index=0;
                    for(index=0;index<r;index++){
                        tmpBuf[index] = toupper(tmpBuf[index]);
                    }
                    write(clientFd[i],tmpBuf,r);
                }
            }
        }
    }
    return 0;
}

int main(){
    int i = 0;
    for(i=0;i<maxGambler;i++)clientFd[i] = -1;
    
	pthread_t thread_chat;
    //pthread_create(&thread_chat,NULL,chatThread,NULL);
    printf("sizeof fd_set = %d\n",sizeof(fd_set));
    
    int s_fd = socket(AF_INET,SOCK_STREAM,0);
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
    listen(s_fd,maxGambler);
    while(1){
        cli_len = sizeof(clie);
        int c_fd = accept(s_fd,(SA*)&clie,&cli_len);
        if(c_fd == -1){
            perror("accept");
            return -3;
        }
        printf("visitor: %s , c_fd = %d\n",inet_ntop(AF_INET,&clie.sin_addr,ip,128),c_fd);
        add_fd(c_fd);
        if(allSet()){
            LetsBegin();
        }
        
        judgeCloseFd();
        //close(c_fd);
    }
    return 0;
}
