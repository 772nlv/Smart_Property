#include "user.h"

//Э��� 
//PB2 CS  �豸���ļ��Ȳ�д
//PB3 CLK PB4 MISO PB5 MOSI  Э����ļ�����
//1spi��ʼ������
//���豸�� ���ε� lora ��spiƬѡ�ź�
void SPI1_Config()
{
	//ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	//��������
	GPIO_InitTypeDef spistruct;
	spistruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	spistruct.GPIO_Mode = GPIO_Mode_AF;
	spistruct.GPIO_PuPd = GPIO_PuPd_UP;
	spistruct.GPIO_OType = GPIO_OType_PP;
	spistruct.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(GPIOB,&spistruct); 
	//3.����GPIO����Ϊspi�ӿ�
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1);
	//4.SPI��·��ʼ��
	SPI_InitTypeDef NSPISRTUCT;
	//ȫ˫��
	NSPISRTUCT.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	//����ģʽ
	NSPISRTUCT.SPI_Mode = SPI_Mode_Master;
	//����λ�Ĵ�С 8λ
	NSPISRTUCT.SPI_DataSize = SPI_DataSize_8b;
	//ʱ�Ӽ���
	NSPISRTUCT.SPI_CPOL = SPI_CPOL_Low;
	//ʱ����λ
	NSPISRTUCT.SPI_CPHA = SPI_CPHA_1Edge;
	//����λѡ��
	NSPISRTUCT.SPI_FirstBit = SPI_FirstBit_MSB;
	//Ӳ��Ƭѡ ���Ƭѡ
	NSPISRTUCT.SPI_NSS = SPI_NSS_Soft;
	//Ԥ��Ƶϵ��
	NSPISRTUCT.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	//У����ֵ
	NSPISRTUCT.SPI_CRCPolynomial = 7;
	//spi��·ʹ��
	SPI_Init(SPI1,&NSPISRTUCT);
	
	//SPI��·ʹ��
	SPI_Cmd(SPI1,ENABLE);
}
//2spi��д����
unsigned char SPI1_write_read(unsigned char data)
{
		//�������� ��עһ����־λ ������� ����1
		while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET);
			SPI_I2S_SendData(SPI1,data);
		//�������ݹ�עһ����עλ  ������� ����1
		while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==RESET);
			return SPI_I2S_ReceiveData(SPI1);
}


