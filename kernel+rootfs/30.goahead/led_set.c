#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int write_dev_data(char *name, char *buffer, int len)
{
	char file[35]="/sys/class/leds/led1/";
	int fd,ret;

	strcat(file, name);
	printf("file:%s, len=%d\n", file, len);
	
	fd=open(file, O_RDWR);
	if(fd<0)
	{
		printf("Open %s failed!\n", name);
		return (-1);
	}
	printf("Open %s ok!\n", name);

	printf("write:%s\n", buffer);

	ret=write(fd, buffer, len);
	if(ret<0)
	{
		printf("Write %s failed!\n", name);
		close(fd);
		printf("closed!\n");
		return (-1);
	}
	printf("Write %s ok!\n", name);

    	close(fd);
	printf("close %s ok!\n", name);
	
	return 0;
}


int main(int argc, char *argv[])
{
	int i;
	
	printf("1----------------------------------------------------\n");

	for (i=0; i<argc; i++)
		printf("Argument %d is %s.\n", i, argv[i]);

	if(argc==1)
	{
		printf("invalid pram!\n");
		return 0;
	}

	if(!strcmp(argv[1],"-on"))  
	{  
		if(write_dev_data("trigger", "none", sizeof("none")-1)<0)
			exit(1);

		printf("set trigger=none!\n");

		if(write_dev_data("brightness", "1", 1)<0)
			exit(1);

		printf("led1 on!\n");
	}  
	else if(!strcmp(argv[1],"-off"))  
	{  
		if(write_dev_data("brightness", "0", 1)<0)
			exit(1);

		printf("led1 off!\n");
	}
	else if(!strcmp(argv[1],"-b"))  
	{  
		if(write_dev_data("trigger", "timer", sizeof("timer")-1)<0)
			exit(1);

		if(argc<3)
		{
			printf("set trigger=timer!\n");
			return 0;
		}
				
		if(write_dev_data("delay_on", argv[2], strlen(argv[2]))<0)
			exit(1);
		
		if(argc<4)
		{
			printf("set delay_on!\n");
			return 0;
		}
		
		if(write_dev_data("delay_off", argv[3], strlen(argv[3]))<0)
			exit(1);

		printf("set delay_off!\n");
	}
	else
	{
		printf("invalid pram!\n");
	}

	printf("0----------------------------------------------------\n");
	
	return 0;
}
