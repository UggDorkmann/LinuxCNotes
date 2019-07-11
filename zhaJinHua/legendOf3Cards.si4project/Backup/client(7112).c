#include"../../all.h"
static void cutOutAliveQuest(char * p,int size){
    char * anchor = strstr(p,"alive?\r\n");
    int len = strlen("alive?\r\n");
	while(anchor)
	{
		memmove(anchor,anchor+len,size-(anchor-p+len));
		anchor = strstr(p,"alive?\r\n");
	}

}
int mainProc(char* p,int size,int servFd){
    return 0;
}
int main(int argc,char* argv[]){
    char read_buf[128] = {0};
    char send_buf[128] = {0};
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
        memset(read_buf,0,sizeof(read_buf));
        int r = read(s_fd,read_buf,sizeof(read_buf));
        if(strstr(read_buf,"alive?\r\n")){
            write(s_fd,"alive=1\r\n",strlen("alive=1\r\n"));
            printf("send: alive = 1\n");
            cutOutAliveQuest(read_buf,sizeof(read_buf));
        }
        if(strlen(read_buf)>0){
            mainProc(read_buf,sizeof(read_buf),s_fd);
        }
    }
    close(s_fd);
return 0;
}

