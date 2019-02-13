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
#include <pthread.h> 

#define MAXLINE 256
#define PORT	8889
#define QUEUESIZE 500

int i32ExitStatus = -999;
int statusExit = 0;	// 退出标志位

// 共享内存结构体
typedef struct {
	int i32MessNum;
	//unsigned char u8Msg[1024];
	int i32MsgLen;
//	int i32MessCheckNum;
	unsigned char u8Msg[1024];
}ST_MESSAGEBOX;

// 创建一个双向队列，用于存储数据
ST_MESSAGEBOX stMsgBoxQue[QUEUESIZE];
unsigned int wReadPoint = 0;
unsigned int wWritePoint = 0;


/*进程退出函数*/
void process_out(int signo)
{
	exit(EXIT_SUCCESS);
}
 
/*socket write 函数*/
void DealProcess(char *argc)
{
	pthread_t tidRecv = (pthread_t)argc;
//	printf("DealProcess tidRecv = %lu", tidRecv);
	ST_MESSAGEBOX stMsgBox;
	int i32TempMessageIndex = 0;

	printf("DealProcess pthread ID = %lu\n", pthread_self());

	stMsgBox.i32MessNum = 0;
	stMsgBox.i32MsgLen = 0;
	memset(stMsgBox.u8Msg, 0, sizeof(unsigned char) * 1024);
	
	while(1) {

		unsigned int i32TempWritePoint = wWritePoint;


		if(wReadPoint % QUEUESIZE != i32TempWritePoint) {
			// 队列不空
			memcpy(&stMsgBox, &stMsgBoxQue[wReadPoint], sizeof(ST_MESSAGEBOX));
			wReadPoint = (wReadPoint + 1)%QUEUESIZE;

			char DataBuff[1024] = {0x0};

			memcpy(DataBuff, stMsgBox.u8Msg, sizeof(unsigned char) * stMsgBox.i32MsgLen);

			int TempNum = -99;
			sscanf(DataBuff+124, "%dri", &TempNum);
	//
			double TempAdd = TempNum + TempNum;

			double TempSub = TempNum - TempNum;

			double Tempmult = TempNum * TempNum;

			double TempDev = TempNum/TempNum;


			i32TempMessageIndex++;
//			printf("i32MsgIndex = %d\n", i32TempMessageIndex);
		} else {
//			printf("queue is NULL\n");
			
//			int ret = pthread_kill(tidRecv, SIGQUIT);
//
//			printf("ret = %d\n", ret);
//			if(ret == ESRCH) {
//				printf("EXIT!\n");
//				break;
//			}
			continue;
		}

		int ret = pthread_kill(tidRecv, 0);

		printf("ret = %d\n", ret);
		if(ret == ESRCH) {
			printf("EXIT!\n");
			break;
		}

	}

	printf("DealMessage count = %d\n", i32TempMessageIndex);

//	pthread_exit((void *) 0);
	return 0;	
}
 
/*socket read 函数*/
void read_func(char *arg)
{
	int connectfd = (int)arg;
	char readbuff[MAXLINE] = {0x0};
	int n = 0;
	int i32MessageIndex = 0;		// 记录消息个数

	//printf("Line %d\n", __LINE__);
	printf("read Func pthread ID = %lu\n", pthread_self());
	// 创建临时用于存放数据的结构体
	ST_MESSAGEBOX stMsgBox;			
	stMsgBox.i32MessNum = 0;
	stMsgBox.i32MsgLen = 0;
	memset(stMsgBox.u8Msg, '\0', sizeof(unsigned char) * 1024);
 
	memset(&readbuff,0,sizeof(readbuff));
	
	while(1)
	{
		n = recv(connectfd, readbuff, MAXLINE, 0);  /*recv 在这里是阻塞运行*/
		if(n > 0) 			/*客户端有数据发送过来*/
		{

			stMsgBox.i32MessNum = i32MessageIndex;
			stMsgBox.i32MsgLen = n;
			memcpy(stMsgBox.u8Msg, readbuff, sizeof(unsigned char) * n);
			i32MessageIndex++;
			unsigned int wTempReadPoint = wReadPoint;
			if((wWritePoint + 1) % QUEUESIZE == wTempReadPoint) {
				// 队列满
				continue;
			}

			memcpy(&stMsgBoxQue[wWritePoint % QUEUESIZE], &stMsgBox, sizeof(ST_MESSAGEBOX));
			wWritePoint = (wWritePoint + 1) % QUEUESIZE;
			

			stMsgBox.i32MessNum = 0;
			stMsgBox.i32MsgLen = 0;
			memset(stMsgBox.u8Msg, 0, sizeof(unsigned char) * 1024);

		}
		else if(n == 0)		/*客户端断开了连接*/
		{
			break;
		}
	};

	printf("RecvMessage count = %d\n", i32MessageIndex);

	printf("wReadPoint = %d\n", wReadPoint);

	// 线程退出
	pthread_exit((void *)0);
}
 
 
int main(void)
{
	int listenfd,connectfd;
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
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); /*INADDR_ANY 可以监听任意IP */
	//server_addr.sin_addr.s_addr = inet_addr("192.168.2.230");
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
	
	if( (connectfd = accept(listenfd, (struct sockaddr*)&client_addr, &addrlen)) == -1) {
		printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
		return -1;
	}
 
//	signal(SIGCHLD, SIG_IGN); /*忽略SIGCHLD，避免僵尸进程*/

	// 创建新的线程
	pthread_t tidRecv, tidDeal;

	pthread_create(&tidRecv, NULL, read_func, (void*) connectfd);
	//pthread_join(tidRecv, NULL);
//	pthread_detach(tidRecv);
		
//	DealProcess(tidRecv);
//	printf("tidRecv = %d\n", tidRecv);

	pthread_create(&tidDeal, NULL, DealProcess, (void *)tidRecv);
	
	pthread_join(tidRecv, NULL);


	pthread_join(tidDeal, NULL);

	return 0;	
}
