#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h>
#include <arpa/inet.h>
#define SHOW_DATA _IOR('S', 0x01, unsigned short)
#define TEMPERARURE _IOR('T', 0x01, unsigned short)
#define HUMIDITY _IOR('H', 0x02, unsigned short)

#define u16 unsigned short
#define IIC_NUM 0
#define SPI_NUM 1
#define BEEP_NUM 2
#define FAN_NUM 3
#define LED_NUM 4
#define KEY_NUM 5

u16 iic_data_change(u16 data)
{
	u16  temp_buf;
	temp_buf = data<<8;
	data = (data>>8 | temp_buf);
	return data;
}

int fd[16];
int beep_status = 0;
int fan_status = 0;
int led_status = 0;
int key_irq_value = 2;
int main(void)
{
	//KEY
	fd[KEY_NUM] = open("/dev/drv_key0", O_RDWR);
	if(fd[KEY_NUM] < 0)
	{
		printf("open drv_key0 err\r\n");
		exit(1);
	}
	//IIC
	fd[IIC_NUM] = open("/dev/drv_si7006", O_RDWR);
	if(fd[IIC_NUM] < 0)
	{
		printf("open drv_si7006 err\r\n");
		exit(1);
	}
	//SPI
	fd[SPI_NUM] = open("/dev/drv_74hc595", O_RDWR);
	if(fd[SPI_NUM] < 0)
	{
		printf("open drv_74hc595 err\r\n");
		exit(1);
	}
	//BEEP
	fd[BEEP_NUM] = open("/dev/drv_beep", O_RDWR);
	if(fd[BEEP_NUM] < 0)
	{
		printf("open drv_beep err\r\n");
		exit(1);
	}
	//FAN
	fd[FAN_NUM] = open("/dev/drv_fan", O_RDWR);
	if(fd[FAN_NUM] < 0)
	{
		printf("open drv_fan err\r\n");
		exit(1);
	}
	//LED
	fd[LED_NUM] = open("/dev/drv_led0", O_RDWR);
	if(fd[LED_NUM] < 0)
	{
		printf("open drv_led0 err\r\n");
		exit(1);
	}

	
	pid_t pid = fork();
	if(0 > fork)
	{
		perror("fork\r\n");
	}
	else if(pid == 0)
	{	
		//子进程
		while(1)
		{
			int ret = read(fd[KEY_NUM],&key_irq_value,sizeof(int));
			if(ret < 0)
			{
				perror("read\r\n");
				return 0;
			}

			//key1 控制灯的开关
			if(key_irq_value == 0)
			{
				if(led_status)
				{	
					led_status = 0;
				}	
				else
				{	
					led_status = 1;
				}
				write(fd[LED_NUM],&led_status,sizeof(led_status));
			}
			//key3 控制beep
			else
			{
				if(beep_status)
				{	
					beep_status = 0;
				}	
				else
				{	
					beep_status = 1;
				}
				write(fd[BEEP_NUM],&beep_status,sizeof(beep_status));
			}
		}
		return 0;
	}

	//父进程
	else
	{
	
		u16 IIC_data;//读取之后小数在前，整数在后
		double temp;
		double humi;
		
		char idex = 0;
		char num = 0;
		u16 SPI_data;//num在前，idex在后
		char * SPI_temp_data;
		SPI_temp_data = (char *)malloc(10);
		//每循环5k次，测一次温度
		int while_count = 0;
		while(1)
		{	
	
		while(!while_count)
		{
			//IIC读取温湿度
			ioctl(fd[IIC_NUM], TEMPERARURE, &IIC_data);
			IIC_data = iic_data_change(IIC_data);
			temp = (IIC_data*175.72)/65536 - 46.85; 
			
			//湿度
			/*ioctl(fd[IIC_NUM], HUMIDITY,&IIC_data);
			IIC_data = iic_data_change(IIC_data);
			humi = (IIC_data*125)/65536 - 6;
			printf("app:humi = %f\r\n",humi);
			*/

			
			while_count = 5000;
			//温度大于32°打开风扇
			if(temp >= 32)
			{
				fan_status = 1;
				write(fd[FAN_NUM], &fan_status, sizeof(fan_status));
			}
			//温度大于35°打开BEEP和Motor
			if(temp >= 35)
			{
				beep_status = 1;
				write(fd[BEEP_NUM], &beep_status, sizeof(beep_status));
			}
			
			}
			

			//SPI数码管显示温度
			sprintf(SPI_temp_data, "%f", temp);
			
			for(int i = 2;i<=4;i++)
			{
				SPI_temp_data[i] = SPI_temp_data[i+1];
			}

			int n = 4;
			while(n)
			{
				idex = 0x01<<(4 - n);
				num = SPI_temp_data[4 - n] - 48;
				SPI_data = (num<<8 | idex);
				ioctl(fd[SPI_NUM], SHOW_DATA, SPI_data);
				n--;
			}
			while_count--;
		}
		
		}
	close(fd[IIC_NUM]);
	close(fd[SPI_NUM]);
	close(fd[FAN_NUM]);
	close(fd[BEEP_NUM]);
	close(fd[KEY_NUM]);
	return 0;
}
