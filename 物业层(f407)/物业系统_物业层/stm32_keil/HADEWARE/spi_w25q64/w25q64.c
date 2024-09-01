#include "user.h"

//����ָ����ֵ
#define W25X_ManufactDeviceID    0x90 
//����Ƭѡ����
#define W25X_ChipErase           0x60   //����h������
//��״̬�Ĵ���
#define W25X_ReadStatusReg       0x05
//������
#define W25X_ReadData            0x03
//дʹ��
#define W25X_WriteEnable         0x06
//д��ʹ��
#define W25X_WriteDisable        0x04 
//ҳ��� ����д����
#define W25X_PageProgram         0x02
//�����
#define W25X_BlockErase          0xD8 
//��������  
#define W25X_SectorErase         0x20
//��
#define W25X_NULL                0x00

//1���豸��ʼ������
void W25Q64_Config()
{
	//1��SPI��ʼ��
	SPI_Config();
	
	//2������lora PE1���͵�ƽѡ�� ���ߵ�ƽ
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
    GPIO_InitTypeDef loratruct;
    //���ź���
    loratruct.GPIO_Pin = GPIO_Pin_1;
    //���ģʽ
    loratruct.GPIO_Mode = GPIO_Mode_OUT;
    //�������
    loratruct.GPIO_OType = GPIO_OType_PP;
	//��������
	loratruct.GPIO_PuPd = GPIO_PuPd_UP;
	//�����ٶ�
    GPIO_Init(GPIOE,&loratruct);
	GPIO_SetBits(GPIOE,GPIO_Pin_1);

	//��ʼ�����豸��Ƭѡ����
	GPIO_InitTypeDef w25qtruct;
    //���ź���
    w25qtruct.GPIO_Pin = GPIO_Pin_2;
    //���ģʽ
    w25qtruct.GPIO_Mode = GPIO_Mode_OUT;
    //�������
    w25qtruct.GPIO_OType = GPIO_OType_PP;
	//��������
	w25qtruct.GPIO_PuPd = GPIO_PuPd_UP;
	//�����ٶ�
	w25qtruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(GPIOB,&w25qtruct);
	//Ƭѡ�źŸ��ߵ�ƽ����ʱ��ѡ��
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
}
//��ȡ�豸ID����
unsigned short W25Q64_ReadID()
{
	//1��׼������
	unsigned short id = 0;
	//2��Ƭѡ
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//��ʼд�������ĸ��ֽ�
	SPI1_Write_Read(W25X_ManufactDeviceID);
	SPI1_Write_Read(W25X_NULL);
	SPI1_Write_Read(W25X_NULL);
	SPI1_Write_Read(W25X_NULL);
	//��ʼ�� ���� 2���ֽ�
	id |= SPI1_Write_Read(W25X_NULL);
	id = id << 8;
	id |= SPI1_Write_Read(W25X_NULL);
	
	//ȡ��Ƭѡ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	//���ض����Ľ��
	return id;
		
}
//д����ʹ�ܺ���
void W25Q64_Write_Enable()
{
	
	//Ƭѡ
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//��������
	SPI1_Write_Read(W25X_WriteEnable);
	//ȡ��Ƭѡ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
}

//���оƬæµ���͵ȴ�
//�����æµ������������0
//���оƬ�Ƿ�æµ����
unsigned char W25Q64_Check_Busy()
{
	unsigned char stat = 0; 
	do{
		//Ƭѡ
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//�������������ؼĴ�������ȡ״̬
	//д ��������
	SPI1_Write_Read(W25X_ReadStatusReg);	
	//��
	stat = SPI1_Write_Read(W25X_NULL);
	//ȡ��Ƭѡ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	}while(stat & 0x01);
	return 0;

}
//ȫ������ 1 ffff
//��������оƬ���� ��ʱ�ܳ�
void W25Q64_Erase_All_Chip()
{
	W25Q64_Write_Enable();
	W25Q64_Check_Busy();
	//Ƭѡ
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//���Ͳ���оƬ������
	SPI1_Write_Read(W25X_ChipErase);
	//ȡ��Ƭѡ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	//�ж�оƬ�Ƿ�æ��
	W25Q64_Check_Busy();
	

}
//д�豸��������дĳ��λ��
//ÿ�����256�ֽ�
unsigned int W25Q64_Read_Data(unsigned int wordaddr,unsigned char buff[],unsigned char len)
{
	//1��Ƭѡ
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	
	//2�����Ͷ����ݵ������оƬ
	SPI1_Write_Read(W25X_ReadData);
	
	//3��������
	//��Ҫ�����ݵĵ�ַ���͸�оƬ ��ַ��24λ �Ӹ����ͷ�����
	SPI1_Write_Read((wordaddr >> 16) & 0xff);
	SPI1_Write_Read((wordaddr >> 8) & 0xff);
	SPI1_Write_Read((wordaddr >> 0) & 0xff);
	
	//������
	int i = 0;
	for(i = 0; i < len ;i++)
	{
		buff[i] = SPI1_Write_Read(W25X_NULL);
	}
	//4��ȡ��Ƭѡ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	
	//5�����ض����������ֽڸ���
	return i;
}

//һ��дһҳ 256�ֽ�
//���豸ĳ��λ�õ����ݺ���
int W25Q64_Write_Data(unsigned int writeaddr,char *pbuff,unsigned short byteNum)
{
	//2��дʹ��
	W25Q64_Write_Enable();
	//1��Ƭѡ
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	
	//3����������
	SPI1_Write_Read(W25X_PageProgram);
	
	//4���ѵ�ַ����ȥ
	//��Ҫ�����ݵĵ�ַ���͸�оƬ ��ַ��24λ �Ӹ����ͷ�����
	SPI1_Write_Read((writeaddr >> 16) & 0xff);
	SPI1_Write_Read((writeaddr >> 8) & 0xff);
	SPI1_Write_Read((writeaddr >> 0) & 0xff);
	
	//5��ѭ��д����
	int i = 0;
	for(i = 0;i < byteNum;i++)
	{
		SPI1_Write_Read(pbuff[i]);
	}
	
	//7��ȡ��Ƭѡ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	//6������Ƿ�æµ
	W25Q64_Check_Busy();
	return i;
}































