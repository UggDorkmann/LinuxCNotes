#include"all.h"
int main(int argc,char** argv){
    int listenfd,connfd;
    socklen_t cliLen = 0;
    int reuse = 0;
    struct sockaddr_in servaddr,cliAddr;
    char buff[MAXLINE] = {0};
    char buffCliInfo[20] = {0};
    time_t ticks;

    listenfd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(1113);
    
    /* codes below deal with "bind: Address already in use"*/
    /*bind �ձ���������������ͼ��һ���Ѿ���ʹ�õĶ˿�,
    ���� TCP �׽���״̬TIME_WAIT ���𡣸�״̬���׽��ֹرպ�Լ���� 2 �� 4 ���ӡ�
    �� TIME_WAIT ״̬�˳�֮���׽��ֱ�ɾ�����õ�ַ���ܱ����°󶨶��������⡣
    �ȴ� TIME_WAIT ���������������ջ��һ���£��ر�����������ڿ���һ���׽��ַ�������
    ����Ҫֹͣ����������һЩ�Ķ���Ȼ�����������˵��ǣ��з������Աܿ� TIME_WAIT״̬��
    ���Ը��׽���Ӧ�� SO_REUSEADDR �׽���ѡ��Ա�˿ڿ����������á�*/
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
        printf("connfd = %d\n",connfd);
        printf("connection from %s , port : %d\n",
            inet_ntop(AF_INET,&cliAddr.sin_addr,buffCliInfo,sizeof(buffCliInfo)),
            ntohs(cliAddr.sin_port));
        ticks = time(NULL);
        snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
        write(connfd,buff,strlen(buff));
        close(connfd);
    }
return 0;
}

