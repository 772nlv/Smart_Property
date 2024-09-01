#include "user.h"

//1.DHT11���ú���
void DHT11_Config()
{
	//PA3����
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef DHT11struct = {0};
	DHT11struct.GPIO_Pin = 	GPIO_Pin_3;
	DHT11struct.GPIO_Mode = GPIO_Mode_OUT;
	//��©���
	DHT11struct.GPIO_OType = GPIO_OType_OD;	
	DHT11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&DHT11struct);
	//��������ģʽ�Ļ�����������ߵ�ƽ
	//��Ϊ��ʼ�ź�ʱ�ͼӸߵ���ϣ����������ȸߵ�ƽ��ʼ
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
}
//2.DHT11����ģʽ����
void DHT11_INMode()
{
	GPIO_InitTypeDef DHT11struct = {0};
	DHT11struct.GPIO_Pin = 	GPIO_Pin_3;
	DHT11struct.GPIO_Mode = GPIO_Mode_IN;
	//��©���	
	DHT11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&DHT11struct);

}
//3.DHT11���ģʽ����
void DHT11_OUTMode()
{
		GPIO_InitTypeDef DHT11struct = {0};
	DHT11struct.GPIO_Pin = 	GPIO_Pin_3;
	DHT11struct.GPIO_Mode = GPIO_Mode_OUT;
	//��©���
	DHT11struct.GPIO_OType = GPIO_OType_OD;	
	DHT11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&DHT11struct);
	//��������ģʽ�Ļ�����������ߵ�ƽ
	//��Ϊ��ʼ�ź�ʱ�ͼӸߵ���ϣ����������ȸߵ�ƽ��ʼ
	//GPIO_SetBits(GPIOA,GPIO_Pin_3);
}
//4.DHT11���ֽں���
	unsigned char DHT11_ReadBytes()
{
	unsigned char resdata = 0;
	char i = 0 ; 
	for(i = 0 ; i < 8 ; i ++)
	{
		//����λ
		resdata = resdata << 1 ;
		//�ȶ�һλ
		//�ȴ��ߵ�ƽ����
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		//�ȴ��͵�ƽ����
		while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		//�жϸߵ�ƽʱ��
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
		{
			delay_us(30);
		}
		//30�Ժ� ���Ǹߵ�ƽ  0000 0000 | 0000 0001
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
				resdata |= 0x01 ;   //���λ����һ��1
		else
				resdata &= 0xfe;   // ���λ ���� 1111 1110
		//����λ
		//resdata = resdata << 1 ;
	}
	//��������
	return resdata;
}


//5.DHT11�����ݺ���
//������ָ�룬�����ָ��
//����ֵ0�ǳɹ�1��ʧ��
char buff[5] = "";
unsigned char DHT11_ReadData(char *humiz,char*humix,char *wtempz,char *wtempx)
{
	//��ʱ��
	//1���ģʽ +��20ms +��30us 
	DHT11_OUTMode();
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	delay_ms(20);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	delay_us(20);
	//����ģʽ ������ ���淢�� ��45us + ��45us ���������ģʽ��ָstm32�������ȴ�����dht11����������
	DHT11_INMode();
	//�ȴ��ߵ�ƽ��������ֹ��������������
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
	//���Բ�Ҫ�����ʱ�䳤��
	//������淢�͵��ǵ͵�ƽ����ô��cpu�ȴ���ֱ���͵�ƽ��ȥ
	//while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
	//��45us�ĸ�ҲԽ��ȥ
	//while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
	while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));

	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));

	//�͸ߵ�ƽʱ��ѭ����ȥ��͵������ݽ��ս׶�
	//ʪ������
	for(int i =0;i<5;i++)
	{
		buff[i] = DHT11_ReadBytes();
	}
	//DHT11_OUTMode();
	//У���
	if(buff[4] == buff[0]+buff[1]+buff[2]+buff[3])
	{		
		*humiz = buff[0];
		*humix = buff[1];
		*wtempz = buff[2];
		*wtempx = buff[3];
			//��������
			return 0;//�ɹ�
	}
	else
		return 1;//ʧ��
}


