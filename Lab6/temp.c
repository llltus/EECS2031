#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ifttt.h"

#define  BUFSIZE  128

char addr[60];

int main(int argc, char *argv[])
{
	double temp;
    double trigger;
    double max = 0;
    double min = 0;
	int i, j;
    int fd;
	int ret;
    time_t second;

	char buf[BUFSIZE];
	char tempBuf[5];
    char tempnum[20];
    char maxBuf[20];
    char minBuf[20];

    if(argc != 2){
    printf("please enter serial number of the sensor");
    return 1;
    }else{
    sprintf(addr, "/sys/bus/w1/devices/%s/w1_slave",argv[1]);
    }


	while (1){
	fd = open(addr, O_RDONLY);

	if(fd == -1){
		printf("open device file error\n");
		return 1;
	}

	while(1){
		ret = read(fd, buf, BUFSIZE);
		if(ret == 0){
			break;	
		}
		if(ret == -1){
			printf("read file error");
			close(fd);
			return 1;
		}
	}

	for(i=0;i<sizeof(buf);i++){
		if(buf[i] == 't'){
			for(j=0;j<sizeof(tempBuf);j++){
				tempBuf[j] = buf[i+2+j]; 	
			}
		}	
	}

	temp = (float)atoi(tempBuf) / 1000;

    if(max==0 && min==0){
        max = temp;
        min = temp;
        trigger = temp;
        gcvt(max,3,maxBuf);
        gcvt(min,3,minBuf);
        gcvt(temp,3,tempnum);
        ifttt("https://maker.ifttt.com/trigger/temp_change/with/key/XgUKMIYlggF6VnWUxPG55", maxBuf, minBuf, tempnum);
    }

    if(temp>max){
        max = temp;
    }
    if(temp<min){
        min = temp;
    }
    if(trigger-temp>1 || temp-trigger>1){
        gcvt(max,3,maxBuf);
        gcvt(min,3,minBuf);
        gcvt(temp,3,tempnum);
        ifttt("https://maker.ifttt.com/trigger/temp_change/with/key/XgUKMIYlggF6VnWUxPG55", maxBuf, minBuf, tempnum);
        trigger = temp;
    }
    
    printf("current tempreture: %.3f C\n",temp);

    second = time(NULL);
    while(difftime(time(NULL),second)<1);

	close(fd);
	}
	return 0;
}
