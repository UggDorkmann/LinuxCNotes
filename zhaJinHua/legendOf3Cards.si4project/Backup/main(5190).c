#include"../all.h"
#define maxGambler 2 //the max number of gamblers on one table
#define onlineWaitingTime 3 //onlineWaitingTime seconds without a reply, you are dead one time
#define heartStopCountTime 5 //you have heartStopCountTime times to crawl out of your grave
void* chatThread(void* arg){
    system("gnome-terminal -x ./chat.out");
    printf("chat thread exited\n");
	return NULL;
}
cliInfo cliInfos[maxGambler] = {0};

int add_fd(int fd){
    int i = 0;
    for(i=0;i<maxGambler;i++){
        if(cliInfos[i].fd == -1){
            cliInfos[i].fd = fd;
            printf("clientFd[%d] = %d\n",i,fd);
            return 0;
        }
    }
    if(i==maxGambler){
        printf("clientFd is full\n");
        return -1;
    }
}


void judgeCloseFd(){
    int i = 0;
    for(i=0;i<maxGambler;i++){
        if(cliInfos[i].heartStopCount >= heartStopCountTime){
            printf("clientFd[%d] = %d is dead\n",i,cliInfos[i].fd);
            close(cliInfos[i].fd);
            cliInfos[i].fd = -1;
        }
    }
}
int allSet(){// All gamblers on table?
    int i = 0;
    for(i=0;i<maxGambler;i++){
        if(cliInfos[i].fd == -1) return 0;
    }
    return 1;
} 
int getMaxFd(){
    int ret = cliInfos[0].fd;
    int i =0 ;
    for(i=1;i<maxGambler;i++){
        if(ret < cliInfos[i].fd) ret = cliInfos[i].fd;
    }
    return ret;
}
static void myFD_SET(fd_set * p){
    int i = 0;
    for(i=0;i<maxGambler;i++){
        FD_SET(cliInfos[i].fd,p);
    }
}
static void clearCliHeartStopCount(){
    int i = 0;
    for(i=0;i<maxGambler;i++){
        cliInfos[i].heartStopCount = 0;
    }
}
static void setCliCheckOnlineTime(){
    int i = 0;
    for(i=0;i<maxGambler;i++){
        cliInfos[i].checkOnlineTime = time(NULL);
    }
}
void addHeartCheck(unsigned char * sendBuf,int len){
    memcpy(sendBuf+len,"alive?\r\n",strlen("alive?\r\n"));
}
void clearTable(){

}
void informOfflineNews(int offlineFd){
    
}
static void cutOutReply(char* p,int size){
    char * anchor = strstr(p,"alive=1\r\n");
    int len = strlen("alive=1\r\n");
    while(anchor)
    {
        memmove(anchor,anchor+len,size-(anchor-p+len));
        anchor = strstr(p,"alive=1\r\n");
    }
}
int msgProc(char * p,int size){

    return 0;
}
static void ignoreBrokenPipe(){
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigaction( SIGPIPE, &sa, NULL );

}
/*
    name    LetsBegin
    return  0 :  someone lost last penny
            -1 : someone is offline
*/
int LetsBegin(){
    printf("let us begin!!!\n");
    char readBuf[128] = {0};
    fd_set readfds , writefds;
    struct timeval s_timeval;
    s_timeval.tv_sec = 1;
    s_timeval.tv_usec = 0;

    char sendBuf[100] = {0};
    
    clearCliHeartStopCount();
    setCliCheckOnlineTime();
    ignoreBrokenPipe();
    
    while(1){
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        myFD_SET(&readfds);
        myFD_SET(&writefds);
        if(select(getMaxFd()+1,&readfds,&writefds,NULL,&s_timeval) > 0){
            int i = 0;
            for(i=0;i<maxGambler;i++){//read
                if(FD_ISSET(cliInfos[i].fd,&readfds)){
                    memset(readBuf,0,sizeof(readBuf));
                    int r = read(cliInfos[i].fd,readBuf,sizeof(readBuf));
                    if(r>0){
                        printf("read : %s\n",readBuf);
                        if(time(NULL) - cliInfos[i].checkOnlineTime > onlineWaitingTime){
                            if(strstr(readBuf,"alive=1\r\n")){
                                printf("client %d is alive,his fd = %d\n",i,cliInfos[i].fd);
                                cliInfos[i].checkOnlineTime = time(NULL);
                                cliInfos[i].heartStopCount = 0;
                            }
                            cutOutReply(readBuf,sizeof(readBuf));
                            msgProc(readBuf,sizeof(readBuf));
                        }
                    }
                }
                //
                //when a client is offline,he can't send anything,judgement above cannot be executed
                //in another hand,when a client reply something without a onlineCheck frame,codes moved here can also record that.
                if(time(NULL) - cliInfos[i].checkOnlineTime > onlineWaitingTime){
                    cliInfos[i].heartStopCount++;
                    if(cliInfos[i].heartStopCount > heartStopCountTime){
                        printf("a dude is offline\n");
                        clearTable();
                        informOfflineNews(cliInfos[i].fd);
                        return -1;
                    }
                }
            }
            for(i=0;i<maxGambler;i++){//write
                if(FD_ISSET(cliInfos[i].fd,&writefds)){
                    if(time(NULL) - cliInfos[i].checkOnlineTime > onlineWaitingTime){
                        addHeartCheck(sendBuf,strlen(sendBuf));
                    }    
                    if(strlen(sendBuf)){
                        write(cliInfos[i].fd,sendBuf,sizeof(sendBuf));
                        printf("send : %s\n",sendBuf);
                        memset(sendBuf,0,sizeof(sendBuf));
                    }
                }
            }
            //if(time(NULL) - checkOnline > 3)
        }
    }
    return 0;
}

int main(){
    int i = 0;
    for(i=0;i<maxGambler;i++)cliInfos[i].fd = -1;
    
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
            if(LetsBegin() == -1){
                judgeCloseFd();
            }
        }
    }
    return 0;
}
