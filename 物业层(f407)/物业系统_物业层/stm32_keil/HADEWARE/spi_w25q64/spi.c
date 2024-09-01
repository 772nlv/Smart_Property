#include "user.h"



//PB2 Cs  -->�豸���ļ�����
//PB3 CLK  PB4 MISO PB5 MOSI ����>Э���

//���豸�� ����Lora�� SPi�ź�Ƭѡ�ź�


//SPI��ʼ������
void SPI_Config()
{
	//1������ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	//2����������
	GPIO_InitTypeDef spistruct;
	spistruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5;
	//����ģʽ 
	spistruct.GPIO_Mode = GPIO_Mode_AF;
	//����ģʽ
//	spistruct.GPIO_OType = GPIO_OType_PP;
	//��������
	spistruct.GPIO_PuPd = GPIO_PuPd_UP;
	//��Ӧ�ٶȡ�����������
	spistruct.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(GPIOB,&spistruct);
	
	//3.�������á���GPIO���ó�SPI
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1);
	
	
	//4.SPI��·��ʼ��
	SPI_InitTypeDef SPI1struct;
	//ȫ˫��
	SPI1struct.SPI_Direction  = SPI_Direction_2Lines_FullDuplex;
	//����ģʽ
	SPI1struct.SPI_Mode = SPI_Mode_Master;
	//����λ�Ĵ�С
	SPI1struct.SPI_DataSize = SPI_DataSize_8b;
	//ʱ�Ӽ���
	SPI1struct.SPI_CPOL = SPI_CPOL_Low;
	//ʱ����λ
	SPI1struct.SPI_CPHA = SPI_CPHA_1Edge;
	//����λѡ��
	SPI1struct.SPI_FirstBit = SPI_FirstBit_MSB;
	//���Ƭѡ
	SPI1struct.SPI_NSS = SPI_NSS_Soft;
	//������ѡ�񡪡�Ԥ��Ƶϵ�� Ϊ2
	SPI1struct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	//У����ֵ����Ĭ��Ϊ7
	SPI1struct.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPI1,&SPI1struct);
	
	//5.SPI��·ʹ��
	SPI_Cmd(SPI1,ENABLE);
	
}


//����ֵ�Ƕ���������
//�����Ƿ��͵�����
//SPI��д����
unsigned char SPI1_Write_Read(unsigned char senddata)
{
	//�������ݣ���ע��־λ����������һ������֮�� ���1
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET){}
		SPI_I2S_SendData(SPI1,senddata);
	
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET){}
		return SPI_I2S_ReceiveData(SPI1);
}

































