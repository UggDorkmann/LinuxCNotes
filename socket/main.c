#include"../all.h"
#define blockEnable 0
static int set_cloexec(int fd)//关闭子进程无用文件描述符
{
	int val;

	val = fcntl(fd, F_GETFD);
	if (val == -1)
		return -1;

	val |= FD_CLOEXEC;
	if (fcntl(fd, F_SETFD, val) == -1)
		return -1;
	else
		return 0;
}
int set_non_block(int fd)
{
	int flags_block_t;

	if((flags_block_t = fcntl(fd, F_GETFL, 0)) < 0) 
	{
		return -1;
	}
	if(fcntl(fd, F_SETFL, flags_block_t | O_NONBLOCK))
	{	
		return -1;
	}
	return 0;		
}

int main()
{
	printf("in main\n");
	printf("%d\n",__LINE__);
	int serv_port = 5100;
	int listenfd;  
	struct sockaddr_in servaddr;
	int opt = 1; 

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
	{
		perror("socket");
		return -1;
	}
	if (set_non_block(listenfd) < 0)
	{
		close(listenfd);
		perror("set non_block");
		return -1;		
	}

	if (set_cloexec(listenfd) < 0)
	{
		close(listenfd);
		perror("set cloexec error\n");
		return -1;
	}
	printf("%d\n",__LINE__);

	//SO_REUSEADDR 允许在bind（）过程中本地地址可重复使用
	setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt)); 

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(serv_port);
	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr)) < 0)
	{
		close(listenfd);
		perror("bind error");
		return -1;
	}
		printf("%d\n",__LINE__);

	if (listen(listenfd, 10) < 0)
	{
		close(listenfd);
		perror("listen error");
		return -1;
	}
	////
		printf("%d\n",__LINE__);

	int connect_fd;
	socklen_t client_len;
	struct sockaddr_in client_addr;
	char flags_block;
	char *p_ipaddr;

	client_len = sizeof(struct sockaddr);
	while(1){
		connect_fd = accept(listenfd, (struct sockaddr *)&client_addr, &client_len);
		if(connect_fd>0){
			printf("%d\n",__LINE__);

			if(set_cloexec(connect_fd) < 0)
			{
				perror("set_cloexec error");
				close(connect_fd);
				return -1;
			}

			/* 设置SOCKET文件句柄为非阻塞模式 */
			if((flags_block = fcntl(connect_fd, F_GETFL, 0))<0) 
			{	
				perror("ERROR get mode");
				close(connect_fd);
				return -1; 
			}			
#if blockEnable //codes below are effective			
			if(fcntl(connect_fd, F_SETFL, flags_block | O_NONBLOCK))
			{	
				perror("ERROR set mode"); 
				close(connect_fd);
				return -1;
			}	
#endif
			p_ipaddr = (char *)inet_ntoa(((struct sockaddr_in*)(&client_addr))->sin_addr);		//获取客户端IP
			char recvBuf[200] = {0};
			while(1){
				memset(recvBuf,0,sizeof(recvBuf));
				int len = recv(connect_fd,recvBuf,sizeof(recvBuf),0);
				if(len>0) printf("recv:%s\n",recvBuf);
				else if(len==0){
					printf("len == 0\n");// client is offline
					break;
				}
				else printf("len < 0\n");//if blockEnable==0 ,this line will never be executed
			}
		}
	}
	////
	return 0;
}
