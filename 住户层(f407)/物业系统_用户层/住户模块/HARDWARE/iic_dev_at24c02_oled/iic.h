#ifndef  __IIC
#define  __IIC
//iic函数声明
#define NACK 1
#define ACK 0
void IIC_Config(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Send_Byte_Data(unsigned char data);
unsigned char IIC_Get_Byte_Data(void);
unsigned char IIC_Get_ACK(void);
void IIC_Send_ACK(unsigned char ack);
void iic_outputmode(void);

//oled函数声明

void WriteOLedCmd(uint8_t cmd);
void WriteOLedData(uint8_t data); 
void OLed_Fill(unsigned char bmp_data);
void OLed_SetPos(unsigned char x, unsigned char y);
void InitOLed(void);
void Oled_print(uint8_t x, uint8_t y,char *str);
void OLed_ShowChina(uint8_t x,uint8_t y,uint8_t *buf);
void OLed_ShowImage(uint8_t *imageData);
extern uint8_t HZ13[];
extern uint8_t HZ12[];
extern unsigned char BMP1[];

//at24c02函数声明
int  AT24c02init(void);
unsigned char at24c02_write_byte(unsigned char word_addr,unsigned char dat);
unsigned char AT24c02_read_bytes(unsigned char word_addr);


#endif

