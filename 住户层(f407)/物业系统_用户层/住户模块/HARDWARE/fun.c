#include "user.h"

char humi[3] = "";							//ʪ������:����һ���ֽ� С��һ���ֽ�
char temp[3] = "";							//�¶����� ����һ���ֽ� С��һ���ֽ�
unsigned short int guangnum =0;	//����ֵ
int beep = 1;
uint8_t datapack[11] = {0};							//��������ҵ������ݰ�
short int check_num = 0;								//У��λ
//��ʼ�����ݰ�
void init_pack(){
		datapack[0] = 0xFE;									//֡ͷ
		datapack[1] = 201;									//ס�����
		datapack[2] = 6;										//���ݳ���
		datapack[3] = temp[0];							//�¶�����
		datapack[4] = temp[1];							//�¶�С��
		datapack[5] = humi[0];							//ʪ������
		datapack[6] = humi[1];							//ʪ������
		datapack[7] = guangnum/100;					//����ǰ��λ
		datapack[8] = guangnum%100;					//���պ���λ
		datapack[9] = check_num;						//У��λ
		datapack[10] = 0xFF;								//֡β
}
//�������
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

	//�¶ȴ���30ʱ���ȿ���
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
		printf("�¶�:%d.%d��C\r\n",temp[0],temp[1]);
		printf("ʪ��:%d.%d%%\r\n",humi[0],humi[1]);
		printf("����:%dlx\r\n",guangnum);
}



