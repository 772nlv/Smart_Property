#ifndef __IIC
#define __IIC

#define ACK 0
#define NACK 1

//IICģ��
void IIC_Config(void);
//��ʼ�ź�
void IIC_Start(void);
//ֹͣ�ź�
void IIC_Stop(void);
//����һ���ֽں���
void IIC_Send_Byte(unsigned char data);
//IIC��ȡ����
unsigned char IIC_Get_Byte(void);
//��ȡACK�ź�
unsigned char IIC_Get_ACK(void);
//����һ���ߵ�ƽ�źţ���Ӧ���ź�
void IIC_SEND_ACK(unsigned char ack);
//����ģʽ
void IIC_INMODE(void);
//���ģʽ
void IIC_OUTMODE(void);


//OLEDģ��
//1.oledд�����
void WriteOLedCmd(uint8_t cmd);
//2 OLEDд���ݺ���
void WriteOLedData(uint8_t data);
//3 oled��㺯��
void OLed_Fill(unsigned char bmp_data);
void OLed_SetPos(unsigned char x, unsigned char y);
//5 OLED��ʼ������
void InitOLed(void);
//6.��ʾ��ĸ����
void Oled_print(uint8_t x, uint8_t y,char *str);
//7.��ʾ���ֺ���
void OLed_ShowChina(uint8_t x,uint8_t y,uint8_t *buf);
//AT24C02
//�豸��ʼ��
//����0 �豸ok
int AT24C02_INIT(void);
unsigned char AT24C02_Write_Bytes(unsigned char wordaddr,unsigned char newdata);//��at24c04�豸�� ĳ����ַ������
unsigned char  AT24C02_Read_Bytes(unsigned char wordaddr);
//AT24c04ģ��



#endif


