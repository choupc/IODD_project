#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
	int fd;
	fd = open("/dev/tq2440_7seg", 0);	//開啟七段顯示器的driver

	if(fd < 0){				//開啟失敗
		perror("open device 7seg error");
		exit(1);
	}
	printf("hello hungyi\n");		//開啟成功

	for(;;);

	return 0;
}
