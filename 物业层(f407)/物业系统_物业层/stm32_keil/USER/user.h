#ifndef __USER
#define __USER

#include "stm32f4xx.h"
#include "delay.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "iic.h"
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"
#define LED1 1
#define LED2 2
#define LED3 3


#define us 4
#define ms 5

extern int PWM_LED2_flag;

extern uint8_t SHESHIDU[];
extern uint8_t BAIFENHAO[];
//���ܺ���
void My_Delay(unsigned int DelayCount);//��ʱ����

//ledģ��
void LED_config(void);//led��ʼ��
void LED_TurnOn(unsigned int LEDNUM);//��led����
void LED_TurnOff(unsigned int LEDNUM);//�ر�led
void LED_Shine(unsigned int LEDNUM);//led��˸
void LED_FLow(void);//led��ˮ

	
//beepģ��

//���÷�����
void BEEP_Config(void);
//�򿪷�����
void BEEP_TurnOn(void);
//�رշ�����
void BEEP_TurnOff(void);
//������alarm �޶�����
void BEEP_Alarm_Count(unsigned int count);
//������һֱ����
void BEEP_Alarm(void);
//��������ledͬ��
void BEEP_LED_To(unsigned int count);


//key����ģ��
//1����ʼ������key123
void KEY1_2_3_Config(void);
//key4
void KEY4_Config(void);
//2��ɨ�谴��
void KEY_Scan(void);


//�ⲿ�ж���غ�������
void INTERRUPT_KEY1_Config(void);
//�ж�KEY_2��غ�������
void INTERRUPT_KEY2_Config(void);
//�ж�KEY_3��غ�������
void INTERRUPT_KEY3_Config(void);
//�ж�KEY_4��غ�������
void INTERRUPT_KEY4_Config(void);


//Systick��ʱ��ģ��
void SYSTICK_Init(unsigned int n);
//systick ��ʱ����
void MY_Systick_Delay(unsigned int n);

//��ʱ��ģ��
//���ö�ʱ��4 ʵ�ֶ�ʱһ��
void Timer4_Config(unsigned short prec,unsigned short peri);

//pwmģ��
//����
void TIM12_CH2_PB15_Fan_Config(void);
//2.�򿪷��Ⱥ���
void Fan_TurnOn(void);
//3.�رշ���
void Fan_TurnOff(void);
//4�����Ʒ���
void Fan_Control(unsigned int value);
void Fan_Low_Control(void);
void Fan_MId_Control(void);
void Fan_High_Control(void);
//��ʼ��PWM_ LED2
void PWM_LED3_Config(void);	
void PWM_LED_ON(void);

void pwm2init(void);
void PWM_BEEP_ON(void);

//���ڳ�ʼ��
void USART1_Config(void);

//DHT11ģ��
//1��DHT11���ú���
void DHT11_Config(void);
//���ģʽ
void DHT11_OUTMode(void);
//����ģʽ
void DHT11_INMode(void);
//DHT11��ȡ�ֽ�
unsigned char DHT11_ReadBytes(void);
//DHT11 ������
char DHT11_Readdata(char *humiz,char *humix,char *tempz,char *tempx);


//spiģ��
//SPI��ʼ������
void SPI_Config(void);
//SPI��д����
unsigned char SPI1_Write_Read(unsigned char senddata);

//w25q64ģ��
//1���豸��ʼ������
void W25Q64_Config(void);
//��ȡ�豸ID����
unsigned short W25Q64_ReadID(void);
//д����ʹ�ܺ���
void W25Q64_Write_Enable(void);
unsigned char W25Q64_Check_Busy(void);
void W25Q64_Erase_All_Chip(void);
unsigned int W25Q64_Read_Data(unsigned int wordaddr,unsigned char buff[],unsigned char len);
int W25Q64_Write_Data(unsigned int writeaddr,char *pbuff,unsigned short byteNum);

//ADCģ��
//����ADC��·������������
void ADC1_Light_Config(void);
//��ʼ�ɼ��ĺ���
unsigned short Get_ADC_Channel(unsigned int channel);
//ͨ���� + �ɼ�ʱ��
unsigned short Get_ADC_Average(unsigned int channel,char times);


//ESP8266ģ��
void uart2init(void);

//���ö�ʱ��5 ʵ�ֶ�ʱһ��
void Timer5_Config(unsigned short prec,unsigned short peri);
void ProcessReceivedString(char *str);
void usart_sendstr(USART_TypeDef * USATRX , char * str,int size);
void setWifi(void);
void Send_Client_Data(void);
void Show_Client_Data(void);


//USART6ģ��
#define EN_USART6_RX 1
#define USART_REC_LEN6 200
extern u8 USART_RX_BUF6[USART_REC_LEN6];
extern u16 USART_RX_STA6;



void uart6_init(void);
void Usart_SendData(u8 data);
void USART6_SendString(u8 *DAT, u8 len);
void SYN_FrameInfo(u8 *HZdata);
void YS_SYN_Set(u8 *Info_data);



//key_4x4
void key_4x4_init(void);
#define   ROW_Pin_0  GPIO_Pin_0
#define   ROW_Pin_1  GPIO_Pin_1
#define   ROW_Pin_2  GPIO_Pin_3 
#define   ROW_Pin_3  GPIO_Pin_4 
#define KEY_NONE 0xFF  // ����һ���ް������µ�״̬�� 
#define   COL_Pin_0  GPIO_Pin_2
#define   COL_Pin_1  GPIO_Pin_3
#define   COL_Pin_2  GPIO_Pin_7 
#define   COL_Pin_3  GPIO_Pin_11 
extern uint8_t key_value1;
char key_4x4_scan(void);
extern char passwd[128];


//lcd.h



//LCD��Ҫ������
typedef struct  
{										    
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;				//LCD ID
	u8  dir;			//���������������ƣ�0��������1��������	
	u16	 wramcmd;		//��ʼдgramָ��
	u16  setxcmd;		//����x����ָ��
	u16  setycmd;		//����y����ָ��	 
}_lcd_dev; 	

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����
/////////////////////////////////////�û�������///////////////////////////////////	 
#define USE_HORIZONTAL  	 0//����Һ����˳ʱ����ת���� 	0-0����ת��1-90����ת��2-180����ת��3-270����ת

//////////////////////////////////////////////////////////////////////////////////	  
//����LCD�ĳߴ�
#define LCD_W 240
#define LCD_H 320

//TFTLCD������Ҫ���õĺ���		   
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

////////////////////////////////////////////////////////////////////
//-----------------LCD�˿ڶ���---------------- 

#define LED      13        //�����������
#define CS   2       //Ƭѡ����
#define RS   7       //�Ĵ���/����ѡ������  
#define RST  3       //��λ����

//QDtechȫϵ��ģ������������ܿ��Ʊ��������û�Ҳ���Խ�PWM���ڱ�������
#define	LCD_LED PDout(LED) //LCD����    		 
#define LCD_CS  PEout(CS)
#define LCD_RS  PEout(RS)
#define LCD_RST PEout(RST)
//���ʹ�ùٷ��⺯���������еײ㣬�ٶȽ����½���14֡ÿ�룬���������˾�Ƽ�����
//����IO����ֱ�Ӳ����Ĵ���������IO������ˢ�����ʿ��Դﵽ28֡ÿ�룡 

#define	LCD_CS_SET  LCD_CS=1 //GPIO_TYPE->BSRRL=1<<LCD_CS    //Ƭѡ�˿�  	PB11
#define	LCD_RS_SET	LCD_RS=1 //GPIO_TYPE->BSRRL=1<<LCD_RS    //����/����  PB10	  
#define	LCD_RST_SET	LCD_RST=1 //GPIO_TYPE->BSRRL=1<<LCD_RST    //��λ			PB12

 							    
#define	LCD_CS_CLR  LCD_CS=0 //GPIO_TYPE->BSRRH=1<<LCD_CS     //Ƭѡ�˿�  	PB11
#define	LCD_RS_CLR	LCD_RS=0 //GPIO_TYPE->BSRRH=1<<LCD_RS     //����/����  PB10	 
#define	LCD_RST_CLR	LCD_RST=0 //GPIO_TYPE->BSRRH=1<<LCD_RST    //��λ			  PB12

				


//������ɫ
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //��ɫ
#define BRRED 			0XFC07 //�غ�ɫ
#define GRAY  			0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	0X841F //ǳ��ɫ
#define LIGHTGRAY     0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 		0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE      	0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE          0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
	    															  
void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(u16 Color);	 
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_DrawPoint(u16 x,u16 y);//����
u16  LCD_ReadPoint(u16 x,u16 y); //����
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

u16 LCD_RD_DATA(void);//��ȡLCD����									    
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
void LCD_WR_DATA(u8 data);
u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
u16 LCD_ReadRAM(void);		   
u16 LCD_BGR2RGB(u16 c);
void LCD_SetParam(void);
void Lcd_WriteData_16Bit(u16 Data);
void LCD_direction(u8 direction );

//spi.h


//�����Գ���ʹ�õ���ģ��SPI�ӿ�����
//�����ɸ��Ľӿ�IO���ã�ʹ����������4 IO������ɱ���Һ��������ʾ
/******************************************************************************
�ӿڶ�����lcd.h�ڶ��壬����ݽ����޸Ĳ��޸���ӦIO��ʼ��LCD_GPIO_Init()
#define LCD_CTRL   	  	GPIOB		//����TFT���ݶ˿�
#define LCD_LED        	GPIO_Pin_9  //PB9 ������TFT -LED
#define LCD_RS         	GPIO_Pin_10	//PB10������TFT --RS
#define LCD_CS        	GPIO_Pin_11 //PB11 ������TFT --CS
#define LCD_RST     	GPIO_Pin_12	//PB12������TFT --RST
#define LCD_SCL        	GPIO_Pin_13	//PB13������TFT -- CLK
#define LCD_SDA        	GPIO_Pin_15	//PB15������TFT - SDI
*******************************************************************************/

#define SCLK        14	//PB13--->>TFT --SCL/SCK
#define MISO        0	
#define MOSI        11	//PB15 MOSI--->>TFT --SDA/DIN

#define SPI_MOSI  PEout(MOSI)
#define SPI_SCLK  PEout(SCLK)
#define SPI_MISO  PDin(MISO)

//Һ�����ƿ���1�������궨��
#define	SPI_MOSI_SET  	SPI_MOSI=1 //LCD_CTRL->BSRR=SPI_MOSI    
#define	SPI_SCLK_SET  	SPI_SCLK=1 //LCD_CTRL->BSRR=SPI_SCLK    


//Һ�����ƿ���0�������궨��

#define	SPI_MOSI_CLR  	SPI_MOSI=0 //LCD_CTRL->BRR=SPI_MOSI    
#define	SPI_SCLK_CLR  	SPI_SCLK=0 //LCD_CTRL->BRR=SPI_SCLK    

void  SPIv_WriteData(u8 Data);

//fon.h
 
//����ASCII��
//ƫ����32
//ASCII�ַ���
//ƫ����32
//��С:12*6

extern const unsigned char asc2_1206[95][12];
extern const unsigned char asc2_1608[95][16];
typedef struct 
{
       unsigned char Index[2];	
       char Msk[32];
}typFNT_GB16; 
//����ȡģ�����峣��С��

//gui.h
void GUI_DrawPoint(u16 x,u16 y,u16 color);
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
void Draw_Circle(u16 x0,u16 y0,u16 fc,u8 r);
void Draw_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2);
void Fill_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2);
void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len,u8 size,u8 mode);
void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode);
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);
void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p); //��ʾ40*40 QQͼƬ
void gui_circle(int xc, int yc,u16 c,int r, int fill);
void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);
void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2);


//test.h
void main_test(void);
void DrawTestPage(u8 *str);
void English_Font_test(void);
extern const unsigned char gImage_qq[];
void Pic_test(void);
void Start_screen(void);
#endif



