#include"all.h"
int err_quit(const char* p){
    printf("%s\n",p);
    exit(-1);
}

int main(int argc,char** argv){
	int sockfd,n;
	char recvline[MAXLINE + 1];
	char myInfo[50] = {0};
    struct sockaddr_in servaddr,myAddr;
	int myAddrLen;
    if(argc !=2) err_quit("need 2 para");
    if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0){
        perror("socket:");
        return -1;
    }
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(1113);
    if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0){
        perror("inet_pton:");
    }
    printf("sizeof sin_addr = %d, sin_addr = %u, %x\n",sizeof(servaddr.sin_addr),
        (unsigned int)servaddr.sin_addr.s_addr,(unsigned int)servaddr.sin_addr.s_addr);
    /*
        /mnt/hgfs/workspace/shensheng/LinuxCNotes/unixNetWorkProgramming: ./a.out  127.0.0.1
        sizeof sin_addr = 4, sin_addr = 16777343, 100007f
    */
    if(connect(sockfd,(SA*)&servaddr,sizeof(servaddr))<0){
        perror("connect:");
        return -1;
    }
	memset(&myAddr,0,sizeof(myAddr));
	getsockname(sockfd,&myAddr,&myAddrLen);
	printf("getsockname,IP: %s , port : %d\n",
		inet_ntop(AF_INET,&myAddr.sin_addr,myInfo,sizeof(myInfo)),
		ntohs(myAddr.sin_port));
    if(read(sockfd,recvline,MAXLINE) >0 ){
        printf("recv:%s",recvline);
    }
        
return 0;
}
