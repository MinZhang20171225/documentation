#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int read_dev_data(char *name, char *buffer, int len, int *size)
{
	char file[60]="/sys/devices/w1_bus_master1/28-00000482b508/";
	int fd,i;

	strcat(file, name);
	printf("file:%s, len=%d\n", file, len);
	
	fd=open(file, O_RDONLY);
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
		printf("content:%sover", buffer);
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
	char buffer[100];

	printf("1----------------------------------------------------\n");
	
	if(read_dev_data("w1_slave", buffer, sizeof(buffer), &size)<0)
		exit(1);

	for(i=0; i<size; i++)
	{
		if((buffer[i]=='t') && (buffer[i+1]=='='))
			break;
	}

	printf("i=%d\n", i);

	if(i==size)	//没有找到
	{
		printf("don't find t=!\n");
	}
	else
	{
		buffer[i+10]='\0';
		buffer[i+9]='C';
		buffer[i+8]=' ';
		buffer[i+7]=buffer[i+6];
		buffer[i+6]=buffer[i+5];
		buffer[i+5]=buffer[i+4];
		buffer[i+4]='.';
		printf("tmp= %s!\n", buffer+i+2);
	}

	printf("0----------------------------------------------------\n");

	return 0;
}
