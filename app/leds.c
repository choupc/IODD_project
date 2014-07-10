#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
	int fd;
	fd = open("/dev/tq2440_7seg", 0);

	if(fd < 0){
		perror("open device 7seg error");
		exit(1);
	}
	printf("hello hungyi\n");

	for(;;);

	return 0;
}
