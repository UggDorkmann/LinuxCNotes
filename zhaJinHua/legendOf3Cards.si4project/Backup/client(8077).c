#include"../../all.h"
int main(int argc,char* argv[]){
    char read_buf[128],msg[128];
    SA4 serv;
    int s_fd = socket(AF_INET,SOCK_STREAM,0);
    if(s_fd == -1){
        perror("socket");
        return -1;
    }
    serv.sin_family = AF_INET;
    serv.sin_port = htons(GamePort);
    inet_pton(AF_INET,argv[1],&serv.sin_addr);
    
    int res_connect = connect(s_fd,(SA*)&serv,sizeof(SA4));
    if(res_connect == -1){
        perror("connect");
        return -1;
    }
    while(1){
        memset(msg,0,sizeof(msg));
        memset(read_buf,0,sizeof(read_buf));
        gets(msg);
        write(s_fd,msg,strlen(msg));
        if(strcasecmp(msg,"exit") == 0) break;
        int r = read(s_fd,read_buf,128);
        printf("read:%s\n",read_buf);
    }
    close(s_fd);
return 0;
}

