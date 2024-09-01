#include "user.h"

char readBuff[5] = {0};
unsigned int tempvalue = 0;

//1��DHT11���ú���
void DHT11_Config()
{
	//����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	//�������� PA3
	GPIO_InitTypeDef dht11struct;
	dht11struct.GPIO_Mode = GPIO_Mode_OUT;
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	dht11struct.GPIO_OType = GPIO_OType_OD;
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	//��ʼ��PA3
	GPIO_Init(GPIOA,&dht11struct);
}

//���ģʽ
void DHT11_OUTMode()
{
	//�������� PA3
	GPIO_InitTypeDef dht11struct;
	dht11struct.GPIO_Mode = GPIO_Mode_OUT;
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	dht11struct.GPIO_OType = GPIO_OType_OD;
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//��ʼ��PA3
	GPIO_Init(GPIOA,&dht11struct);
}

//����ģʽ
void DHT11_INMode()
{
	//�������� PA3
	GPIO_InitTypeDef dht11struct;
	dht11struct.GPIO_Mode = GPIO_Mode_IN;
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//��ʼ��PA3
	GPIO_Init(GPIOA,&dht11struct);
}

//DHT11��ȡ�ֽ�
unsigned char DHT11_ReadBytes()
{
	unsigned char retByte;
	for(int i = 0; i < 8;i++)
	{
		retByte = retByte << 1;
		
		//�ȴ���һ���ߵ�ƽ����
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		//�ȴ���һ���͵�ƽ����
		while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		
		//�ж��ǲ��Ǹߵ�ƽ
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
		{
			//�ӳ�30us
			delay_us(30);
		}
		//�ж�30us֮���ǲ��Ǹߵ�ƽ
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
		{
			//����ǣ��������������߼�Ϊ1
			retByte |= 0x01;
		}
		else
		{
			//������ǣ��������������߼�Ϊ0
			retByte &= 0xfe;
		}
	}
	//��������
	return retByte;
}

//DHT11 ������
char DHT11_Readdata(char *humiz,char *humix,char *tempz,char *tempx)
{
	
	tempvalue = 0;
	//����Ϊ���ģʽ
	DHT11_OUTMode();
	//����͵�ƽ20ms + �ߵ�ƽ30us
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	delay_ms(20);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	delay_us(30);

	//����DHT11Ϊ����ģʽ
	//����һ���͸ߵ�ƽ��Ϊ��Ӧ
	//DHT11_INMode();
	
	//�������ʱ�� ,�ȴ������������
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
	
		
	//����������һ�� �͵�ƽ��45us�� + �ߵ�ƽ��45us��
	while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
//	{
//		delay_us(1);
//		tempvalue++;
//		if(tempvalue > 100)
//		{
//			return 1;
//		}	
//	}
	tempvalue = 0;	
	//�ȴ��ߵ�ƽ����
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
//	{
//		//��ֹ�����������ת
//		delay_us(1);
//		tempvalue++;
//		if(tempvalue > 100)
//		{
//			return 1;
//		}
//	}
		//printf("125\r\n");
	//��ʼ��������
	for(int i = 0; i < 5;i++)
	{
		//printf("130\r\n");
		readBuff[i] = DHT11_ReadBytes();
	}
	//���ݶ�ȡ��֮�󣬰�DHT11�Ļ����ģʽ
	DHT11_OUTMode();
	if(readBuff[4] == readBuff[0] + readBuff[1] + readBuff[2] + readBuff[3])
	{
		*humiz = readBuff[0];
		*humix = readBuff[1];
		*tempz = readBuff[2];
		*tempx = readBuff[3];
		return 0;
	}
	else
	{
		return 1;
	}
}
















