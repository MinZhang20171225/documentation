#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
/sys/class/leds/led1 20
brightness      delay_on        max_brightness  subsystem       uevent
delay_off       device          power           trigger
content:none nand-disk mmc0 [timer] size=29
6e 6f 6e 65 20 6e 61 6e 64 2d 64 69 73 6b 20 6d 6d 63 30 20 5b 74 69 6d 65 72 5d 20 0a
content:500 size=4
35 30 30 0a 
content:0 size=2
30 0a 
*/
//output led1's state

int read_dev_data(char *name, char *buffer, int len, int *size)
{
	char file[35]="/sys/class/leds/led1/";
	int fd,i;

	strcat(file, name);
	printf("file:%s, len=%d\n", file, len);
	
	fd=open(file, O_RDWR);
	if(fd<0)
	{
		printf("Open %s failed!\n", name);
		return (-1);
	}
	printf("Open %s ok!\n", name);

	*size=read(fd, buffer, len);
	if(*size<=0)
	{
		printf("Read %s failed!\n", name);
		close(fd);
		printf("closed!\n");
		return (-1);
	}
	printf("Read %s ok! size=%d\n", name, *size);

    	close(fd);
	printf("close %s ok!\n", name);

	if(*size>0)
	{
		buffer[*size]='\0';
		printf("content:%s", buffer);
		for(i=0; i<*size; i++)
		{
			printf("%02x ", buffer[i]);
		}
		printf("\n");
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	int size,i;
	char buffer[60];

	printf("1----------------------------------------------------\n");
	
	if(read_dev_data("trigger", buffer, sizeof(buffer), &size)<0)
		exit(1);
	
	for(i=0; i<size; i++)
	{
		if(buffer[i]=='[')
			break;
	}

	printf("i=%d\n", i);

	if(i==size)	//没有找到[
	{
		printf("don't find [!\n");
	}
	else if(strncmp(buffer+i+1, "none", sizeof("none")-1)==0)	//brightness
	{
		if(read_dev_data("brightness", buffer, sizeof(buffer), &size)<0)
			exit(1);

		if(buffer[0]=='0')
			printf("led1 off!\n");
		else
			printf("led1 on!\n");
	}
	else if(strncmp(buffer+i+1, "timer", sizeof("timer")-1)==0)	//delay_on delay_off
	{
		printf("led1 blink!\n");

		if(read_dev_data("delay_on", buffer, sizeof(buffer), &size)<0)
			exit(1);

		printf("delay_on=%s!\n", buffer);

		if(read_dev_data("delay_off", buffer, sizeof(buffer), &size)<0)
			exit(1);

		printf("delay_off=%s!\n", buffer);
	}
	else
	{
		printf("unknow trigger type!\n");
	}
	
	printf("0----------------------------------------------------\n");

	return 0;
}
