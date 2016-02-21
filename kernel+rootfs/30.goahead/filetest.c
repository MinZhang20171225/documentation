#include <stdio.h>
#include <string.h>

static int writePassWord(char *path, char *passwd, char len)
{
	char buf[256];
	char size;
	FILE *fp;
	int ret;
	long offset;

	fp = fopen(path, "r+");
	if(fp == NULL) {
        printf("Can't open %s\n", path);
        return -1;
    }
	
	while(1)
	{
		if(fgets(buf, sizeof(buf), fp) == NULL)
		{
			printf("can't find admin\n");
			ret=-2;
			break;
		}
		//查找正确行
		if(strncmp(buf, "user name=admin", sizeof("user name=admin")-1)==0)
		{
			printf(buf);
			size=strlen(buf);
			printf("size=%d\n", size);
			
			memcpy(buf+25, passwd, len);
			printf(buf);
			
			//写入新的密码
			offset=0-size;
			ret=fseek(fp, offset, SEEK_CUR);
			if(ret<0)
			{
				printf("fseek failed %d\n", offset);
				ret=-3;
			}
			else
			{
				fputs(buf, fp);
				ret=0;
			}
			
			break;
		}
	}

	fclose(fp);
	printf("close fp!\n");

	return ret;
}

int main(int argc, char *argv[])
{
	int ret;
	
	printf("1----------------------------------------------------\n");

	ret = writePassWord("/home/gq213/auth.txt", "12345678901234567890123456789012", 32);
	printf("ret=%d\n", ret);
	
	printf("0----------------------------------------------------\n");

	return 0;
}
