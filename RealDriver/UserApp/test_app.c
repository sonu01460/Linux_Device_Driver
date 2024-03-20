#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int8_t read_buf[1024];
int8_t write_buf[1024];

int main()
{
    int fd;
    char option ;
    printf("************************************\n");
    printf("******sonu_prajapat_driver *********\n");

    fd =open("/dev/ext_device",O_RDWR);
    if(fd<0){
        printf("unable to open the device file\n");
        return 0;
    }

    while(1)
    {
        printf("************************************\n");
        printf("please enter the option \n");
        printf("  Write 1     \n");
        printf("  Read  2    \n");
        printf("  exit  3     \n");
        printf("************************************\n");
        scanf("%c",&option);
        printf("your option is %c\n",option);
        switch(option)
        {
            case '1':
                    printf("enter the string to write to driver:");
                    scanf(" %[^\t\n]s",write_buf);
                    printf("writing data to driver..n");
                    write(fd,write_buf,strlen(write_buf)+1);
                    printf("Done\n");
                    break;

            case '2':
                    printf("Data reading..\n");
                    read(fd,read_buf,1024);
                    printf("Done\n");
                    printf("data = %s\n\n",read_buf);
                    break;
            case '3':
                    close(fd);
                    exit(1);
                    break;

            default:
             printf("Please enter vlaid option %c\n",option);
             break;
        }
    }
    close(fd);
}