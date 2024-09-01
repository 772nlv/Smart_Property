#include "user.h"

char humi[3] = "";							//湿度数组:整数一个字节 小数一个字节
char temp[3] = "";							//温度数组 整数一个字节 小数一个字节
unsigned short int guangnum =0;	//光照值
int beep = 1;
uint8_t datapack[11] = {0};							//发送至物业层的数据包
short int check_num = 0;								//校验位
//初始化数据包
void init_pack(){
		datapack[0] = 0xFE;									//帧头
		datapack[1] = 201;									//住户编号
		datapack[2] = 6;										//数据长度
		datapack[3] = temp[0];							//温度整数
		datapack[4] = temp[1];							//温度小数
		datapack[5] = humi[0];							//湿度整数
		datapack[6] = humi[1];							//湿度整数
		datapack[7] = guangnum/100;					//光照前两位
		datapack[8] = guangnum%100;					//光照后两位
		datapack[9] = check_num;						//校验位
		datapack[10] = 0xFF;								//帧尾
}
//检测数据
void getdata()
{
	char flg = -1;
	flg = DHT11_ReadData(humi,humi+1,temp,temp+1);
	guangnum = getADC_average(0,5);
	check_num = temp[0] +temp[1] +humi[0] +humi[1] +guangnum/100 +guangnum%100;
	init_pack();
	if(guangnum>2000)	
	{  
		LED_TurnOn(2);
	}
	if(guangnum<2000)	
	{  
		LED_TurnOff(2); 
	}

	//温度大于30时风扇开启
	if(temp[0]<30)	
	{  
		Fan_TurnOff();
		beep =1;
	}
		if(temp[0]>=30)
	{
		Fan_TurnOn();
		if(beep)
		{
		Beep_Alarm();
		beep = 0;
		}
	}
		printf("温度:%d.%d°C\r\n",temp[0],temp[1]);
		printf("湿度:%d.%d%%\r\n",humi[0],humi[1]);
		printf("光照:%dlx\r\n",guangnum);
}



