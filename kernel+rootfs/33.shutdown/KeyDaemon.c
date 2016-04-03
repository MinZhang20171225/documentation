#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>  
#include <linux/input.h> 
#include <unistd.h>

int main(int argc, char **argv)
{
	int fd;
	int count;
	struct input_event ev_temp;  
	int power_type = 0;

	printf("Open ...\n");
	fd = open("/dev/input/event1", O_RDONLY);
	if(fd < 0)
	{
		printf("Open Failed!\n");
		return(-1);
	}
	printf("Open ok!\n");

	while(1)
	{
		count = read(fd, &ev_temp, sizeof(struct input_event));
		if(count)
		{
			printf("type: %d\tcode: %d\tvalue: %d\n", ev_temp.type, ev_temp.code, ev_temp.value);

			if(ev_temp.type == EV_KEY)
			{
				printf("key %s\n", ev_temp.value ? "Pressed" : "Released");
				
				if( (ev_temp.code == KEY_POWER) && (ev_temp.value == 1) )
				{
					printf("Power Off!\n");
					power_type = 1;
					break;
				}
				else if( (ev_temp.code == KEY_HOME) && (ev_temp.value == 1) )
				{
					printf("Reboot!\n");
					power_type = 0;
					break;
				}
			}
		}
	}

	printf("close...\n");
	close(fd);
	printf("close ok!\n");

	if(power_type)
	{
		system("poweroff");
	}
	else
	{
		system("reboot");
	}

	printf("exit KeyDaemon!\n");
	
	return(0);
}
