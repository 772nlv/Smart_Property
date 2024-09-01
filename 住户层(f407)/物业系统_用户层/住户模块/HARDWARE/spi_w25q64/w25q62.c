#include "user.h"
//�豸��
//1.��ȡ�豸id����
//2.��������оƬ����
//3.�����ݣ��Ǹ��ֽ�   ������  ���೤  ����ֵ�����˶��ٸ��ֽ�
//ok
//4.д���ݣ�������д  дʲô  ��д�೤  ���أ�ʵ��д�˶೤
//һ�������ݺ��� һ��д���ݺ���
//linux api  51 stm32 qt 
//�����ݺ�д���ݶ����������
unsigned char SPI1_write_read(unsigned char data);
//id����
unsigned char idnum[2] = "" ;
unsigned char sbuff[128] = "" ;
unsigned char sbuff1[128] = "" ;
unsigned char dundun = 0 ;
//��������
//�豸id
#define W25X_ManufactDeviceID	0x90 

//����Ƭѡ����
#define W25X_ChipErase			0x60   //����h������
//��״̬�Ĵ���
#define W25X_ReadStatusReg		0x05
//������
#define W25X_ReadData			0x03
//дʹ��
#define W25X_WriteEnable		0x06
//д��ʹ��
#define W25X_WriteDisable		0x04 
//ҳ��� ����д����
#define W25X_PageProgram		0x02
//�����
#define W25X_BlockErase			0xD8 
//��������  
#define W25X_SectorErase		0x20
//�ڶ��㺯��
//w25q126��д�����������ȥ����ģ���������

//1��ʼ������
void w25q128_init()
{
		//PE1���øߵ�ƽ  lora ���ε�
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
		GPIO_InitTypeDef GPIOEstruct;
		GPIOEstruct.GPIO_Pin = GPIO_Pin_1;
		GPIOEstruct.GPIO_Speed = GPIO_Speed_2MHz;
		GPIOEstruct.GPIO_PuPd = GPIO_PuPd_UP ;
		GPIOEstruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIOEstruct.GPIO_OType = GPIO_OType_PP;
		GPIO_Init(GPIOE,&GPIOEstruct);
	
		//��ѡ��  //loraҪƬѡ���ߡ�ˢ������ѡ��
		GPIO_SetBits(GPIOE,GPIO_Pin_1);
	
		//1.spi��ʼ��  //
		SPI1_Config();
		//2.Ƭѡ��flash  ʱ��ҲҪ��ʼ������
		GPIO_InitTypeDef GPIOstruct;
		//��д����
		GPIOstruct.GPIO_Pin = GPIO_Pin_2;
		//��д�ٶ�
		GPIOstruct.GPIO_Speed = GPIO_Speed_50MHz;
		//��д����
		GPIOstruct.GPIO_PuPd = GPIO_PuPd_UP ;
		//��дģʽ
		GPIOstruct.GPIO_Mode = GPIO_Mode_OUT;
		//����������ߵ�ƽҲ��������͵�ƽ
		GPIOstruct.GPIO_OType = GPIO_OType_PP;
		GPIO_Init(GPIOB,&GPIOstruct);
		//3Ƭѡ�ǵ͵�ƽ��Ч  ����Ƭѡ �����ߵ�ƽ
		GPIO_SetBits(GPIOB,GPIO_Pin_2);
}

 

//��д���ݺ���  

//��ȡ�豸id����  
//16λ
//0xef16��������оƬid��

//˼·��Ƭѡ - д����(��������) - ������ - ����Ƭѡ

//2.���豸���ݺ���
uint16_t W25Q_read_id(unsigned char *num1,unsigned char *num2)
{
		uint16_t id = 0 ;
		//1.Ƭѡ�����Ƭѡ
	
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		//2.��������豸id
		//90�����Ҫ�����ĸ��ֽڹ�ȥ  32λ  ����2���ֽ� 
		//���ͺ����Ͷ����ݺ���������
	
		SPI1_write_read(0x90);
		SPI1_write_read(0x00);
		SPI1_write_read(0x00);
		SPI1_write_read(0x00);
	
		//�����ݣ������Ľ���Ǹ߰�λ���ȶ����߰�λ
		//����ֵ�ǽ�����߰�λ
		id |= SPI1_write_read(0x00);  
		//����һ��
		id = id << 8 ;
		//Ȼ���ٻ��Ϻ���ĵͰ�λ  �����η���2���ֽ�
		id |=  SPI1_write_read(0x00);
		//3.ȡ��Ƭѡ
		GPIO_SetBits(GPIOB,GPIO_Pin_2);
		return id;
}

//3дʹ�ܺ���
//��оƬ����ָ�
void write_enable()
{
			//1.Ƭѡ
			GPIO_ResetBits(GPIOB,GPIO_Pin_2);
			//2.��������
			SPI1_write_read(W25X_WriteEnable);
			//3.�ر�Ƭѡ
			GPIO_SetBits(GPIOB,GPIO_Pin_2);
}

//4���оƬ�Ƿ���æµ�к���
//��Ϊ��������Ҫʱ���
//�ȴ����к���
unsigned char w25q128_check_busy()
{
			unsigned char stat = 0 ;
			//Ƭѡ  
			GPIO_ResetBits(GPIOB,GPIO_Pin_2);
			//��������  д����
			SPI1_write_read(W25X_ReadStatusReg);
			//ѭ���ȴ� : ��ִ�ж�������ѭ���ȴ�
			do{
				
			//��������  ������  �Ĵ�����æ ֵ����0��
			stat = SPI1_write_read(0x00);
			
				
			}while(stat & 1);
			//ȡ��Ƭѡ  
			GPIO_SetBits(GPIOB,GPIO_Pin_2);
			return 0;
}
//5���Ĵ�������
//Ƭѡ- ���������ȡ�Ĵ��� -  ��ȡ�Ĵ�����ֵ - �������ֵ  
u8 w25q_readregister()
{
			u8 data = 0;
			//Ƭѡ
			GPIO_ResetBits(GPIOB,GPIO_Pin_2); 
			//��������
			SPI1_write_read(W25X_ReadStatusReg);
			//��ȡ�Ĵ�����״ֵ̬
			data = SPI1_write_read(0xff);
			//ȡ��Ƭѡ
			GPIO_SetBits(GPIOB,GPIO_Pin_2);
			return data ;
}

//6�ȴ����к���
void w25q_wait_busy()
{ 
			while((w25q_readregister()&0x01)==0x01);   // �ȴ�BUSYλ���
}
//�������̣�
	//	1.дʹ�ܺ���
	//	2.�ȴ����к���
	//	3.Ƭѡ
	//	4.���Ͳ�������
	//	5.�ȴ����к���

//7��״̬�Ĵ��������� 1Ƭѡ -2���Ͷ�״̬�Ĵ������� -3��ȡ���һ���ֽ�- 4�ر�Ƭѡ
//��������оƬ		  
//�ȴ�ʱ�䳬��...
void W25QXX_Erase_Chip()   
{          
		//дʹ�ܺ���
    write_enable();              //SET WEL 
		//æ�ȴ�����
    w25q_wait_busy();  
		//Ƭѡ-��������-ȡ��Ƭѡ
  	GPIO_ResetBits(GPIOB,GPIO_Pin_2);    
    SPI1_write_read(W25X_ChipErase);  
		GPIO_SetBits(GPIOB,GPIO_Pin_2);  
		//�ȴ�оƬ��������
		w25q_wait_busy();  			   
} 

//8��������оƬ����
//������д��ʱ���busy
unsigned char w25q128_eraser_chip_all()
{		
		write_enable();
		w25q128_check_busy();
		//1.Ƭѡ
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		//2.��������  ��ָ�����ѡ������
		SPI1_write_read(W25X_ChipErase);
		//������ֽڵĵڰ�λ����оƬ��cs�������ߣ����csû�����ߣ���ôоƬ��дָ��ᱻִ��
		//3.ȡ��Ƭѡ
		GPIO_SetBits(GPIOB,GPIO_Pin_2);
		//4.�ȴ���������  ��������Ҫʱ���
		w25q128_check_busy();
			
		return 0 ;
}

//9.�������ݺ���
//�����ݳɹ��ˣ����ǲ�����û�гɹ�
//��ַ + �ռ� + ���ȡ�
unsigned int w25q128_read_data(uint32_t addr,uint8_t *sbuff,uint8_t len)
{			
			w25q128_check_busy();
			//1.Ƭѡ
			GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	
			//2.���Ͷ�����ָ��
			SPI1_write_read(W25X_ReadData);
			//������ŵ��ǵ�ַ  //ȡ����С���֡�
			SPI1_write_read((addr >> 16) & 0xff); 
			SPI1_write_read((addr >> 8) & 0xff);
			SPI1_write_read((addr) & 0xff);
	
			//3.��������
			uint8_t i = 0 ;
			for(i = 0 ; i < len ; i++)
			{
					//��Ҳ���������������
					sbuff[i] = SPI1_write_read(0);
				
			}
			//4.ȡ��Ƭѡ
			GPIO_SetBits(GPIOB,GPIO_Pin_2);
			//�ȴ�������
			//w25q128_check_busy();// ��ȡ������ɺ�Flash���Զ���Ϊ��æ״̬��
			//����ʵ�ʶ������ֽ���
			return i ;
}
//10.д�豸���� д��ĳ��λ��
//һ��дһҳ 256���ֽ�

void w25q128_write_page(unsigned char *pbuff,unsigned char writeaddr,unsigned short int numbytes)
{	
	
	write_enable();
	//1Ƭѡ
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//2.дʹ��

	//3.��������
	SPI1_write_read(W25X_PageProgram);
	//4������д���ѵ�ַ����ȥ ѭ��д����
	SPI1_write_read((u8)(writeaddr)>>16);
	SPI1_write_read((u8)(writeaddr)>>8);
	SPI1_write_read((u8)writeaddr);
	//5.ѭ��д����
	int i =0;
	for(i = 0;i<numbytes;i++)
	SPI1_write_read(pbuff[i]);
	
	
	//6.ȡ��Ƭѡ
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	//7.����Ƿ�æµ	
	w25q128_check_busy();
	
}

