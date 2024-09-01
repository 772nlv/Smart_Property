#include "user.h"

//д����λ��0
//������λ��1
#define WRITE_AT24C02_ADDR 0xa0;
#define READ_AT24C02_ADDR 0xa1;
//�豸��غ���
//�豸��ʼ��
//����0�����豸û����
//����1�����豸����
int  AT24c02init()
{
        IIC_Config();
        IIC_Start();
        //�����豸��ַ��д������                  
        IIC_Send_Byte_Data(0xa0);
        if(IIC_Get_ACK())
        {        
            IIC_Stop();
            return 1;
        }
        return 0 ;
}


//��at24c02�豸��ĳ����ַд������
//�豸��ַ-�ֽڵ�ַ-����
unsigned char at24c02_write_byte(unsigned char word_addr,unsigned char dat)
{
        //1.��ʼ�ź�
        IIC_Start();
        
        //2.�����豸��ַ
        IIC_Send_Byte_Data(0xa0);
        //3.�ȴ�Ӧ���ź�
        if(IIC_Get_ACK())
        {
                IIC_Stop();
                return 1 ;//ͨ������ֵ�жϺ�����ִ����� ����1ʧ��
        }
        //4.�����Լ���ַ
        IIC_Send_Byte_Data(word_addr);
        //5.�ȴ�Ӧ���ź�
        if(IIC_Get_ACK())
        {
                IIC_Stop();
                return 1 ;
        }
        //6.������������
        IIC_Send_Byte_Data(dat);
        if(IIC_Get_ACK())             //���û��Ӧ��ֱ���˳���û��Ӧ�𷵻�1����Ӧ�𷵻�0.
        {
                   IIC_Stop();
                    return 1 ;                
        }
         IIC_Stop();
        return 0 ; //д�ɹ�����0��
        //8.�����źš�
}


//�����ݴ��ȥ�ٶ�������
//�洢һ���ַ������ٶ�������
//����λ�ö�����
//��ĳ���豸 ĳ����ַ ��������
//�����һ���ֽڣ�����Ҫ��
//ָ�����ĸ���ַ��ʼ����
//��ĳ����ַ�����ݣ�ʵ���Ͼ��ǰѵ�ַ���͹�ȥ��Ȼ���ٶ���
//����ʱ��Ҫ�󼴿ɡ�
unsigned char AT24c02_read_bytes(unsigned char word_addr)
{
        unsigned char buff = 0 ;
        //1������ʼ�ź�
        IIC_Start();
        //2�����豸��ַ д�͵�ƽ
        IIC_Send_Byte_Data(0xa0);
        //3�ȴ�Ӧ���ź�
        if(IIC_Get_ACK())             //���û��Ӧ��ֱ���˳���û��Ӧ�𷵻�1����Ӧ�𷵻�0.
        {
                  IIC_Stop();
                return 1 ;
        }
        //4�����ֽڵ�ַ
        IIC_Send_Byte_Data(word_addr);
        //5�ȴ�Ӧ���ź�
        if(IIC_Get_ACK())             //���û��Ӧ��ֱ���˳���û��Ӧ�𷵻�1����Ӧ�𷵻�0.
        {
                IIC_Stop();
                return 1 ;
        }
        //6�ٴη�����ʼ�ź�
        IIC_Start();
        //7�����豸��ַ �������ߵ�ƽ
        IIC_Send_Byte_Data(0XA1);
        //8�ȴ�Ӧ���ź�
        if(IIC_Get_ACK())             
        {
                IIC_Stop();
                return 1 ;
        }
        //9��ȡ��������
        buff = IIC_Get_Byte_Data();
        //10���ͷ�Ӧ���ź�
        IIC_Send_ACK(NACK);
        //11�����ź�
        IIC_Stop();       
        return buff ;

}

