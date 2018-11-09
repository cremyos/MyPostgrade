#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/wait.h>
 
#define MAXLINE 256
#define PORT	8889

static int i32ExitStatus = -999;

// 共享内存结构体
typedef struct {
	int i32Flag;
	//unsigned char u8Msg[1024];
	int i32MsgLen;
//	int i32MessCheckNum;
	unsigned char u8Msg[1024];
}ST_MESSAGEBOX;




/*进程退出函数*/
void process_out(int signo)
{
	exit(EXIT_SUCCESS);
}
 
/*socket write 函数*/
void DealProcess(int pid)
{
	int shmid = -99;
	int i32MessageIndex = 0;		// 记录消息个数

	shmid = shmget((key_t)8888, sizeof(ST_MESSAGEBOX), 0666|IPC_CREAT);
	void *shm = shmat(shmid, (void *)0, 0);
	
	ST_MESSAGEBOX *Msgbox = (ST_MESSAGEBOX*)shm;

	printf("Deal id = %d\n",pid);

	wait(&i32ExitStatus);
 
	while(1)
	{
		unsigned char readBuff[1024] = {0x0};
		unsigned char TempData[10] = {0x0};
		if(Msgbox->i32Flag == 1) {
			memcpy(readBuff, Msgbox->u8Msg, sizeof(unsigned char) * Msgbox->i32MsgLen);
//			printf("Message Len = %d\n", Msgbox->i32MsgLen);
			Msgbox->i32Flag = 0;
			Msgbox->i32MsgLen = 0;
			i32MessageIndex ++;
			printf("DealMessageIndex = %d\n", i32MessageIndex);

			// 取数据
			memcpy(TempData, readBuff + 124, sizeof(char) * 4);
			int i32TempNum = -99;
			sscanf(TempData, "%dri", &i32TempNum);

			// 运算操作
			int i32Sum = i32TempNum + i32TempNum;
			int i32Multi = i32TempNum * i32TempNum;
			int i32Devide = i32TempNum/3;
			int i32Sub = i32TempNum - i32TempNum;
		}
		
	}

//	printf("DealProcessfunc Messagecount = %d\n", i32MessageIndex);

	shmdt(shm);	
	shmctl(shmid, IPC_RMID, 0);

//	exit(EXIT_SUCCESS); /*进程退出*/
	
}
 
/*socket read 函数*/
void read_func(int pid, int fd)
{
	char readbuff[MAXLINE] = {0x0};
	int n = 0;
	int shmid = -99;
	int i32MessageIndex = 0;		// 记录消息个数

	shmid = shmget((key_t)8888, sizeof(ST_MESSAGEBOX), 0666|IPC_CREAT);
	void *shm = shmat(shmid, (void *)0, 0);
	
	ST_MESSAGEBOX *Msgbox = (ST_MESSAGEBOX*)shm;
	Msgbox->i32Flag = 0;
	//Msgbox->i32MessCheckNum = 0;

	printf("read id = %d \n",pid);
 
	memset(&readbuff,0,sizeof(readbuff));
	
	while(1)
	{
		n = recv(fd, readbuff, MAXLINE, 0);  /*recv 在这里是阻塞运行*/
		if(n > 0) 			/*客户端有数据发送过来*/
		{
			i32MessageIndex ++;
//			printf("server recv dataIndex =  %d\n", i32MessageIndex);

			if(Msgbox->i32Flag == 0) {
				memcpy(Msgbox->u8Msg, readbuff, sizeof(unsigned char) * n);
				Msgbox->i32Flag = 1;
				Msgbox->i32MsgLen = n;
//				Msgbox->i32MessCheckNum = i32MessageIndex;
			}
		}
		else if(n == 0)		/*客户端断开了连接*/
		{
			break;
		}
	};

	printf("RecvMessage count = %d\n", i32MessageIndex);
	shmdt(shm);
	
	exit(EXIT_SUCCESS); /*进程退出*/
}
 
 
int main(void)
{
	int listenfd,connetfd;
	int on = 1;
	int addrlen = 0;
	pid_t pid, pid_child, pid_Recv, pid_Deal;
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
	
	if( (connetfd = accept(listenfd, (struct sockaddr*)&client_addr, &addrlen)) == -1) {
		printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
		return -1;
	}
 
	signal(SIGCHLD, SIG_IGN); /*忽略SIGCHLD，避免僵尸进程*/
	pid = fork();
	if(pid == -1) {
		printf("fork err \n");
	} else if(pid == 0) {
	
		pid_child = fork(); 
		if(pid_child == 0) {  	
			pid_Deal = getpid(); 	/* 获取子进程ID*/
			DealProcess(pid_Deal);
		} else {
			pid_Recv = getpid(); 	
			read_func(pid_Recv, connetfd);
		}
	}
	
}
