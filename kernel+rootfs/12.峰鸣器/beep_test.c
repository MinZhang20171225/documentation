#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/input.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int fd, tmp;
	struct input_event event;
 
	printf("Open ...\n");
	fd = open("/dev/input/event0", O_RDWR);
	if (fd < 0) {
		printf("Open PWM Device Faild!\n");
		exit(1);
	}
      printf("Open ok!\n");
     
	event.type = EV_SND;
	event.code = SND_TONE;
	event.value = 2000;

	write(fd, &event, sizeof(struct input_event));
	printf("write ok!\n");

 	while(1)
    	{
		//输入参数
		scanf("%d", &tmp);
		printf("value = %d\n", tmp);
        
		//IO控制
		if(tmp < 0)
		{
			break;
		}
		event.value = tmp;
		write(fd, &event, sizeof(struct input_event));
		printf("write ok!\n");
    	}

	printf("close...!\n");
	close(fd);
	printf("close ok!\n");

	return 0;
}

