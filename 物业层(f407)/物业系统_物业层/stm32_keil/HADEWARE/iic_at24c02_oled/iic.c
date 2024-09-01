#include "user.h"


//IIC�ӿڳ�ʼ�� SCL: PB6  SDA:PB7
void IIC_Config()
{
//����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	//�������� PA3
	GPIO_InitTypeDef IICstruct;
	IICstruct.GPIO_Mode = GPIO_Mode_OUT;
	IICstruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
	IICstruct.GPIO_OType = GPIO_OType_OD;
	//�ⲿ�Ѿ�����������
	IICstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	IICstruct.GPIO_Speed = GPIO_Low_Speed;
	//��ʼ��PA3
	GPIO_Init(GPIOB,&IICstruct);
}

void IIC_INMODE()
{
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOB,&iicstruct);
}
void IIC_OUTMODE()
{
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Mode = GPIO_Mode_OUT;
	iicstruct.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIOB,&iicstruct);
}

//��ʼ�ź�
void IIC_Start()
{
	//ʱ���ź�Ϊ�߲��� +  ���������ɸߵ���
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	
	//������Ч�ԣ�ʱ����Ϊ�͵�ƽ��ʱ�����ݲ��ɼ�
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}

//ֹͣ�ź�
void IIC_Stop()
{
	//�����źţ�ʱ�����ڸߵ�ƽ���������£��������ɵ͵���
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);	
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
	//SCL ��
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	//����״̬
//	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
//	delay_us(2);
}

//����һ���ֽں���
//��Ҫ���͵�����һ�����ֽڴ��䣬����ͨ�ţ�ÿ�δ���һ��λ
void IIC_Send_Byte(unsigned char data)
{
	unsigned char i = 0 ;
	for(i = 0 ; i < 8 ; i ++)
	{
		//�ȴ��ݵ��Ǹ�λ MSB LSB
		//�ȴ�һλ
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		//������ʱ
		delay_us(1); 
		
		//  data & 0x01
		if((data >>(7 - i))& 0x01)
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
		else
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
		delay_us(4);
		// data >> 1 & 0x01
	//ѭ��8��
	}	
	//������������ʱ��  ʱ����Ϊ�͵�ƽ �������ϵ����� ���治���ȡ
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
}
	
//IIC��ȡ����
unsigned char IIC_Get_Byte()
{
	IIC_INMODE();
	//����ģʽ-
	//�����洢���淢�͹���������
	unsigned char dat = 0 ;
	unsigned char i = 0 ;
	for(i = 0 ; i < 8 ; i++)
	{
		//���ƶ�λ��
		dat = dat << 1;
		//ʱ����Ϊ�͵�ƽ �������ϵ����� ���Ա仯
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
		delay_us(1);
		
		//ʱ��������
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
		//�����淢�͹���������
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
			dat |= 0X01;
		else
			dat &= 0xfe;
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(4);
	}
	//���ģʽ
	IIC_OUTMODE();
	//��������
	return dat;
}

//��ȡACK�ź�
unsigned char IIC_Get_ACK()
{
	//ʱ���ߵ͵�ƽ
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	//����������ǰ����Ϊ�ߵ�ƽ
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(1);
	
	//ʱ��������
	GPIO_SetBits(GPIOB,GPIO_Pin_6);	
	delay_us(1);
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
		return 1;//����ʧ��
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_6); 
		delay_us(1);
		return 0;
	}
		
}


//����һ���ߵ�ƽ�źţ���Ӧ���ź�
void IIC_SEND_ACK(unsigned char ack)
{
	//SCL�͵�ƽ
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	if(ack == NACK)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_7);//SDA�ߵ�ƽ����Ӧ���ź�
		delay_us(1);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_7);//SDA�͵�ƽ��Ӧ���ź�
		delay_us(1);
	}
	//����SCL�����ݿɶ�
	GPIO_SetBits(GPIOB,GPIO_Pin_6);	
	delay_us(1);

	//����SCL������״̬
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
	
}


































