#include"../all.h"
int main(int argc,char* argv[]){
	char buf[128],msg[128];
	struct sockaddr_in serv;
	int s_fd = socket(AF_INET,SOCK_STREAM,0);
	if(s_fd == -1){
		perror("socket");
		return -1;
	}
	serv.sin_family = AF_INET;
	serv.sin_port = htons(5100);
	
	inet_pton(AF_INET,argv[1],&serv.sin_addr);
	int c = connect(s_fd,(SA*)&serv,sizeof(struct sockaddr_in));
	if(c == -1){
		perror("connect");
		return -1;
	}
	while(1){
		memset(msg,0,sizeof(msg));
		printf("write to connected fd\n");
		fgets(msg,sizeof(msg),stdin);
		write(c,msg,strlen(msg));
		if(strcasecmp(msg,"exit") ==0){
			printf("all over\n");
			return 0;
		}
	}
return 0;
}
