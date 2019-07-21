#include"all.h"
int main(int argc,char** argv){
    int listenfd,connfd;
    socklen_t cliLen = 0;
    int reuse = 0;
    struct sockaddr_in servaddr,cliAddr;
    char buff[MAXLINE] = {0};
    char buffCliInfo[20] = {0};
	char myInfo[20] = {0};
	int myInfoLen = 0;
    time_t ticks;

    listenfd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(1113);
    
    /* codes below deal with "bind: Address already in use"*/
    /*bind 普遍遭遇的问题是试图绑定一个已经在使用的端口,
    它由 TCP 套接字状态TIME_WAIT 引起。该状态在套接字关闭后约保留 2 到 4 分钟。
    在 TIME_WAIT 状态退出之后，套接字被删除，该地址才能被重新绑定而不出问题。
    等待 TIME_WAIT 结束可能是令人恼火的一件事，特别是如果您正在开发一个套接字服务器，
    就需要停止服务器来做一些改动，然后重启。幸运的是，有方法可以避开 TIME_WAIT状态。
    可以给套接字应用 SO_REUSEADDR 套接字选项，以便端口可以马上重用。*/
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0){
        perror("setsockopet error\n");
    }

    int b=bind(listenfd,(SA*)&servaddr,sizeof(servaddr));
    if(b < 0){
        perror("bind");
        return ERR_BIND;
    }
    listen(listenfd,5);
    printf("before while(1)\n");
    while(1){
        
        connfd = accept(listenfd,(SA*)&cliAddr,&cliLen);
	/*
	程序第一次运行的时候会发生下面的奇怪情况，加上getpeername是万无一失的。
	before while(1)
	connfd = 4
	connection from 0.0.0.0 , port : 0
	getpeername,connection from 127.0.0.1 , port : 32775
	connfd = 4
	connection from 127.0.0.1 , port : 32776
	getpeername,connection from 127.0.0.1 , port : 32776
	*/
        printf("connfd = %d\n",connfd);
		memset(buffCliInfo,0,sizeof(buffCliInfo));
        printf("connection from %s , port : %d\n",
            inet_ntop(AF_INET,&cliAddr.sin_addr,buffCliInfo,sizeof(buffCliInfo)),
            ntohs(cliAddr.sin_port));
		
		memset(&cliAddr,0,sizeof(cliAddr));
		memset(buffCliInfo,0,sizeof(buffCliInfo));
		getpeername(connfd,&cliAddr,&cliLen);
		printf("getpeername,connection from %s , port : %d\n",
            inet_ntop(AF_INET,&cliAddr.sin_addr,buffCliInfo,sizeof(buffCliInfo)),
            ntohs(cliAddr.sin_port));

		memset(myInfo,0,sizeof(myInfo));
		getsockname(listenfd,&servaddr,&myInfoLen);
		printf("getsockname,IP: %s , port : %d\n",
            inet_ntop(AF_INET,&servaddr.sin_addr,myInfo,sizeof(myInfo)),
            ntohs(servaddr.sin_port));
		
        ticks = time(NULL);
        snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
        write(connfd,buff,strlen(buff));
        close(connfd);
    }
return 0;
}

