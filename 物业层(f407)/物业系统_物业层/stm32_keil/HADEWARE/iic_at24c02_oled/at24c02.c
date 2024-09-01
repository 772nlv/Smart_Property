

#include "user.h"

//д ��λ�� 0
//�� ��λ�� 1 
#define WRITE_AT24C02_ADDR 0xa0
#define READ_AT24C02__ADDR 0xa1

//1�豸��ʼ��
//����0 �����豸ok
//����1 ���豸����
int AT24C02_INIT()
{
	//����豸�Ƿ����
	IIC_Config();
	IIC_Start();
	//д����  0xa0 
	IIC_Send_Byte(WRITE_AT24C02_ADDR);
	if(IIC_Get_ACK())
	{
		//ֹͣЭ��
		IIC_Stop();
		return 1;
	}
	else
		return 0;
}


//2���д����
//��at24c02�豸 ��ĳ����ַ д����
//ͨ������ֵ�жϺ�����ִ�����
//0:�ɹ�
//1:ʧ��
unsigned char AT24C02_Write_Bytes(unsigned char wordaddr,unsigned char newdata)
{
	//1.��ʼ�ź�
	IIC_Start();
	//2.�����豸��ַ 
	IIC_Send_Byte(WRITE_AT24C02_ADDR);
	//3.��ȡack�ź�
	if(IIC_Get_ACK())
	{
		//ֹͣЭ��
		IIC_Stop();
		return 1;
	}

	//4.�����ֽڵ�ַ
	IIC_Send_Byte(wordaddr);
	//5.��ȡack�ź�
	if(IIC_Get_ACK())
	{
		//ֹͣЭ��
		IIC_Stop();
		return 1;
	}
	
	//6.�������ݱ���
	IIC_Send_Byte(newdata);
	//7.��ȡack�ź�
	if(IIC_Get_ACK())
	{
		//ֹͣЭ��
		IIC_Stop();
		return 1;
	}
	//8.the end 
	IIC_Stop();
	return 0 ;
}


//3���������
//���ص������ݱ���
//������ �ֽڵ�ַ
unsigned char  AT24C02_Read_Bytes(unsigned char wordaddr)
{
	unsigned char ret = 0 ; 
	//1.��ʼ�ź�
	IIC_Start();
	//2.�����豸��ַ д
	IIC_Send_Byte(WRITE_AT24C02_ADDR);
	//3 ��ȡack
	if(IIC_Get_ACK())
	{
		//ֹͣЭ��
		IIC_Stop();
		return 1;
	}
	//4.�����ֽڵ�ַ
	IIC_Send_Byte(wordaddr);
	//5.��ȡack
	if(IIC_Get_ACK())
	{
		//ֹͣЭ��
		IIC_Stop();
		return 1;
	}
	//6.��ʼ�ź�
	IIC_Start();
	//7.�����豸��ַ ��
	IIC_Send_Byte(READ_AT24C02__ADDR);
	//8.��ȡack
	if(IIC_Get_ACK())
	{
		//ֹͣЭ��
		IIC_Stop();
		return 1;
	}
	//9.��������
	ret = IIC_Get_Byte();
	//10.����nack
	IIC_SEND_ACK(NACK);
	//11.����
	IIC_Stop();
	return ret;
}

