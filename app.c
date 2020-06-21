#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <time.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/sysmacros.h>

#define SMOKE_DEV_PATH         "/dev/smoke_dev"
#define BUZZER_DEV_PATH		"/dev/buzzer_dev"

#define INTERVAL         50000

int main(void)
{
   int smoke_dev, smoke_data;
   int buzzer_dev, buzzer_data = 400;
   
   smoke_dev = open(SMOKE_DEV_PATH, O_RDONLY);
   buzzer_dev = open(BUZZER_DEV_PATH, O_RDWR);
   
   if(smoke_dev < 0) {
	   printf("fail to open smoke detection sensor device\n");
	   return 1;
   }

   if(buzzer_dev < 0) {
	   printf("fail to open buzzer sensor device\n");
	   return 1;
   }
   int count = 0;
   
   while(count < 200){
      
      read(smoke_dev, &smoke_data, sizeof(int));
      printf("data : %d\n", smoke_data);
      if(smoke_data > 500) {
      		write(buzzer_dev, &buzzer_data, sizeof(int)*2);
      }
      sleep(3);
   }
   
   close(smoke_dev);
   close(buzzer_dev);
   
   return 0;
}
