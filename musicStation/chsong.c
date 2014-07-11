#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>
#include "lookdir.h"
//#include "tq2440_7seg.h"

void *get_pthread(void *arg);
void *print_pthread(void *arg);
void print();
int fd_pipe[2];
int fd_fifo;
int fd1;
Songstruct *listptr;

int main(int argc,int *argv[])
{
  	pid_t pid,pid1;
  	char buf[100];
  	unlink("/my_fifo");
  	mkfifo("/my_fifo",O_CREAT|0666);
  	/*FIFO和PIPE功用一樣，差別在於PIPE只能用在有父子關係的process，而FIFO無此限制。
  	且FIFO會建立一個file作為process之間的溝通介面。*/
  	perror("mkfifo");
  	if(pipe(fd_pipe)<0){perror("pipe error\n");exit(-1);}
  	/*當兩個不同的Process要溝通時，我們可以用pipe來達成。簡單來說，pipe就像是一條水管，
  	連接兩個Process，其中一端寫入資料到水管，另一端便可從水管中讀出此資料。*/
  	
  	/*呼叫pipe()來建立pipe，其參數int fd_pipe[2]是用來回傳兩個file descriptors，fd_pipe[0]代表的是pipe的讀取端，
  	fd_pipe[1]則是pipe的寫入端。*/
  	
	pid=fork();
  	if(pid<0)
  	{
    		perror("fork");
  	}else if(pid==0){		//child
		/*pid1=fork();
		if(pid1<0)
		{
			perror("fork");
		}
		else if(pid1==0)
		{
			execlp("./leds","./leds",NULL);
		}else
		{
    			close(fd_pipe[0]);
   			dup2(fd_pipe[1],1);
    			printf("child1\n");
			fd_fifo=open("/my_fifo",O_RDWR);
			printf("child2\n");
			execlp("mplayer","mplayer","-slave","-quiet","-input","file=/my_fifo","/opt/Kalimba.mp3",NULL);
		}*/
		close(fd_pipe[0]);
		/*由於fork會使fd_pipe[0],fd_pipe[1]產生兩份，記得把不必要的Descriptor關閉，可避免不當的操作。*/
   		dup2(fd_pipe[1],1);
   		/*dup2(fd_pipe[1],1)可以把它想成複製fd_pipe[1]且當作是標準輸出(stdout)*/
   		/*0:stdin 1:stdout 2:stderr */
    		printf("child1\n");
		fd_fifo=open("/my_fifo",O_RDWR);
		printf("child2\n");
		execlp("mplayer","mplayer","-slave","-quiet","-input","file=/my_fifo","/opt/Kalimba.mp3",NULL);
		/*slave端輸入的指令會存到my_fifo裡面，child process再從my_fifo讀出指令並執行相對應的動作*/
  	}
	else{		//parent
		fd1 = open("/dev/tq2440_7seg", 0);		//開啟七段顯示器
		if(fd1 < 0){
			perror("open device 7seg error");
			exit(1);
		}
		pthread_t tid1;
		pthread_t tid2;
		fd_fifo=open("/my_fifo",O_RDWR);
		pthread_create(&tid1,NULL,get_pthread,NULL);
		pthread_create(&tid2,NULL,print_pthread,NULL);
		pthread_join(tid1,NULL);
		pthread_join(tid2,NULL);
  	}
  	return 0;
}

void *get_pthread(void *arg){		/*get_pthread會讀取slave端輸入的指令，並做相對應的ioctl*/
	char buf[100];
	listptr=lookdir("/opt");
	//_7seg_info_t segment;
	while(1){
   		printf("thread1\n");
   		printf("please input your cmd:");
   		
   		fflush(stdout);

   		printf("\nlistptr->songname=%s\n",listptr->song_name);
		printf("listptr->nextPtr->songname=%s\n",listptr->nextPtr->song_name);

   		fgets(buf,sizeof(buf),stdin);
		if(strlen(buf)==6)		//pause\0
		{
			ioctl(fd1, 1, NULL);
		}
		else if(strlen(buf)>=8)		//loadfile\0
		{
			ioctl(fd1, 2, NULL);
		}
		printf("after fgets.............listptr->songname=%s\n",listptr->song_name);

		buf[strlen(buf)] = '\0';
		printf("*%s*\n", buf);
		if(write(fd_fifo, buf, strlen(buf)) != strlen(buf))
			perror("write");

  	}
}

void *print_pthread(void *arg)
{
  char buf[100];
  close(fd_pipe[1]);
  int size=0;
  while(1)
  {
     printf("thread2");
     size=read(fd_pipe[0],buf,sizeof(buf));
     buf[size]='\0';
     //sleep(3);
     printf("the msg read from pipe is %s\n",buf); 
  }
}
void print(){
   printf("listptr->song_name=%s\n",listptr->song_name);
}
/*child process把輸出訊息透過pipe傳給parent process，parent process再用print_pthread講訊息印出*/
