#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<signal.h>
 
#define MAXLINE 256
#define PORT	8889
 
/*进程退出函数*/
void process_out(int signo)
{
	exit(EXIT_SUCCESS);
}
 
/*socket write 函数*/
void write_func(int pid, int fd)
{
	char* write = "I am server";
	
	printf("write id = %d\n",pid);
 
	signal(SIGUSR1,process_out);  /* 注册信号SIGUSR1，该信号由read 进程发送过来。*/
	while(1)
	{
		sleep(1);
		send(fd,write,strlen(write)+1,0);
	}
}
 
/*socket read 函数*/
void read_func(int pid, int fd)
{
	char readbuff[MAXLINE];
	int n = 0;
 
	printf("read id = %d \n",pid);
 
	memset(&readbuff,0,sizeof(readbuff));
	
	while(1)
	{
		n = recv(fd, readbuff, MAXLINE, 0);  /*recv 在这里是阻塞运行*/
		if(n > 0) 			/*客户端有数据发送过来*/
		{
			printf("server recv data: %s \n",readbuff);
		}
		else if(n == 0)		/*客户端断开了连接*/
		{
			break;
		}
	};
	
	kill(pid, SIGUSR1); /*发送信号SIGUSR1 到write进程*/
	exit(EXIT_SUCCESS); /*进程退出*/
}
 
 
int main(void)
{
	int listenfd,connetfd;
	int on = 1;
	int addrlen = 0;
	pid_t pid, pid_child, pid_send;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
 
 
	if ((listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		printf("create socket err \n");
	}
	
	/*设置服务端地址*/
	addrlen = sizeof(struct sockaddr_in);
	memset(&server_addr, 0, addrlen);
	server_addr.sin_family = AF_INET;    /*AF_INET表示 IPv4 Intern 协议*/
	//server_addr.sin_addr.s_addr = htonl(INADDR_ANY); /*INADDR_ANY 可以监听任意IP */
	server_addr.sin_addr.s_addr = inet_addr("192.168.2.230");
	server_addr.sin_port = htons(PORT);  /*设置端口*/
 
	/*对套接字进行设置*/
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)   
	{
		printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
		exit(0);
	}
 
	/*绑定地址结构到套接字描述符*/
	if( bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
	{
		printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
		exit(0);
	}
	
	/*设置监听队列，这里设置为10，表示可以同时处理10个客户端的连接*/
	if( listen(listenfd, 10) == -1)
	{
		printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
		exit(0);
	}
	
	printf("wait client accpt \n");
	while(1)
	{
		/*接收客户端的连接，这里会阻塞，直到有客户端连接*/
		if( (connetfd = accept(listenfd, (struct sockaddr*)&client_addr, &addrlen)) == -1)
		{
			printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
			continue;
		}
 
		signal(SIGCHLD, SIG_IGN); /*忽略SIGCHLD，避免僵尸进程*/
		pid = fork();
		if(pid == -1)
		{
			printf("fork err \n");
		}
	
		if(pid == 0)					/* 子进程*/
		{
			pid_child = fork(); 
			if(pid_child == 0)  		/*孙子进程*/
			{
				pid_send = getpid(); 	/*获取孙子进程ID*/
				read_func(pid_send, connetfd);
			}
			else
			{
				pid_send = getpid(); 	/* 获取子进程ID*/
//				write_func(pid_send,connetfd);
			}
		}
 
	}
}
