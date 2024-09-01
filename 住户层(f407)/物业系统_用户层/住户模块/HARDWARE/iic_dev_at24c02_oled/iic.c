#include "user.h"
//PB6 :SCL PB7:SDA
//����ģʽ
void IIC_INMODE()
{
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOB,&iicstruct);
}
//���ģʽ
void IIC_OUTMODE()
{
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOB,&iicstruct);
}

//1 ��ʼ������
void IIC_Config()
{
	//ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//����
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	iicstruct.GPIO_Mode = GPIO_Mode_OUT;
	iicstruct.GPIO_OType = GPIO_OType_OD;
	//�ⲿ����������
	iicstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	iicstruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOB,&iicstruct);
	//��ʼ��
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
}


//2 ��ʼ�źź���
void IIC_Start()
{	
	//1 ʱ���ź�Ϊ�߲��� + �������ǴӸߵ���
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	//2.������Ч�ԣ�ʱ����Ϊ�͵�ƽ��ʱ�� ���ɼ��������ϵ����ݣ�������ݿ��Ըı�
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}


//3 ��ֹ�źź���
void IIC_Stop()
{
	//
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	//ʱ��������
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
	//����������
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	//��ֹ�źŽ����Ժ������߶��Ǹ� ����
}


//4����һ���ֽں���
//��Ҫ���͵����ݰ�λ���д��� һ�δ���һ���ֽ� ��λ����
void IIC_Send_Byte_Data(unsigned char data)
{	
	unsigned char i =0;
	for(i =0;i<8;i++)
	{	
			//�ȴ��ݸ�λ MSB LSB
			//�ȴ�һλ
			GPIO_ResetBits(GPIOB,GPIO_Pin_6);
			delay_us(1);
			if((data>>(7-i)) & 0x01)
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
			else
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
			delay_us(2);
			GPIO_SetBits(GPIOB,GPIO_Pin_6);
			delay_us(4);
			//		data & 0x01; �õ����λ�����ݲ�����
			//ѭ���˴�
	}
	//������������ʱ�� ʱ����Ϊ�͵�ƽ �������ϵ�����  ���治���ȡ
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
}


//5��ȡһ���ֽں���
//���淢������Ҳ���ȷ���λ���������Ƚ��ո�λ���ݣ����պ�λ����������
unsigned char IIC_Get_Byte_Data()
{	
	
	//�����洢���淢�͹���������
	unsigned char data =0;
	unsigned char i = 0;
	for(i =0;i<8;i++)
	{		
			//���ƶ�λ��
			data <<= 1;
			//ʱ����Ϊ�͵�ƽ �������ϵ����ݿ��Ա仯
			GPIO_ResetBits(GPIOB,GPIO_Pin_6);
			delay_us(1);
			//����������
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
			delay_us(1);
			//ʱ��������
			GPIO_SetBits(GPIOB,GPIO_Pin_6);
			delay_us(1);

			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
					data |= 0x01;
			else
					data &= 0xfe;

			GPIO_ResetBits(GPIOB,GPIO_Pin_6);
			delay_us(4);
	}
	return data;
}


//6��ȡ��Чλ����ȡack�źţ����� 
//��ȡ�����淢�͵ĵ͵�ƽΪ0  ��˵��8bit���ݴ���ɹ�
unsigned char IIC_Get_ACK()
{	
	//��ʾ����ʱ����Ϊ�͵�ƽ
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	//��ǰ����������
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(1);
	//����ʱ���ߣ�ʱ����Ϊ�ߵ�ƽ��ʱ��Ŷ�ȡ����
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	//�����͵�ƽ�ųɹ������淢�����Ǹߵ�ƽ�����������������ߵģ�����ʧ�ܵ�
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
		return 1;
	else
	{	//����������ʱ�� ����ʱ����Ϊ��
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
		return 0;
	}
	//������Ϊ�͵�ƽʱ����0

}


//7 ����NACK�źź��� 1

void IIC_Send_ACK(unsigned char ack)
{
		//ʱ��������
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
	//��������
		if(ack == NACK)
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
		else
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		//ʱ����Ϊ�ߵ�ƽ ����������
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
		delay_us(4);
		//����������ʱ�� ����ʱ����Ϊ��
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
}
void iic_outputmode()
{
		GPIO_InitTypeDef iicstruct;
		iicstruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		//���ģʽ
		iicstruct.GPIO_Mode = GPIO_Mode_OUT;
		//�������
		iicstruct.GPIO_OType = GPIO_OType_PP;
		//�������
		iicstruct.GPIO_Speed = GPIO_Speed_100MHz;
		iicstruct.GPIO_PuPd = GPIO_PuPd_UP;
		//���ų�ʼ����
		GPIO_Init(GPIOB,&iicstruct);
}
