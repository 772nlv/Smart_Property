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
//功能函数
void My_Delay(unsigned int DelayCount);//延时函数

//led模块
void LED_config(void);//led初始化
void LED_TurnOn(unsigned int LEDNUM);//打开led函数
void LED_TurnOff(unsigned int LEDNUM);//关闭led
void LED_Shine(unsigned int LEDNUM);//led闪烁
void LED_FLow(void);//led流水

	
//beep模块

//配置蜂鸣器
void BEEP_Config(void);
//打开蜂鸣器
void BEEP_TurnOn(void);
//关闭蜂鸣器
void BEEP_TurnOff(void);
//蜂鸣器alarm 限定次数
void BEEP_Alarm_Count(unsigned int count);
//蜂鸣器一直警报
void BEEP_Alarm(void);
//蜂鸣器和led同步
void BEEP_LED_To(unsigned int count);


//key按键模块
//1、初始化按键key123
void KEY1_2_3_Config(void);
//key4
void KEY4_Config(void);
//2、扫描按键
void KEY_Scan(void);


//外部中断相关函数声明
void INTERRUPT_KEY1_Config(void);
//中断KEY_2相关函数声明
void INTERRUPT_KEY2_Config(void);
//中断KEY_3相关函数声明
void INTERRUPT_KEY3_Config(void);
//中断KEY_4相关函数声明
void INTERRUPT_KEY4_Config(void);


//Systick定时器模块
void SYSTICK_Init(unsigned int n);
//systick 延时函数
void MY_Systick_Delay(unsigned int n);

//定时器模块
//配置定时器4 实现定时一秒
void Timer4_Config(unsigned short prec,unsigned short peri);

//pwm模块
//配置
void TIM12_CH2_PB15_Fan_Config(void);
//2.打开风扇函数
void Fan_TurnOn(void);
//3.关闭风扇
void Fan_TurnOff(void);
//4、控制风扇
void Fan_Control(unsigned int value);
void Fan_Low_Control(void);
void Fan_MId_Control(void);
void Fan_High_Control(void);
//初始化PWM_ LED2
void PWM_LED3_Config(void);	
void PWM_LED_ON(void);

void pwm2init(void);
void PWM_BEEP_ON(void);

//串口初始化
void USART1_Config(void);

//DHT11模块
//1、DHT11配置函数
void DHT11_Config(void);
//输出模式
void DHT11_OUTMode(void);
//输入模式
void DHT11_INMode(void);
//DHT11读取字节
unsigned char DHT11_ReadBytes(void);
//DHT11 读数据
char DHT11_Readdata(char *humiz,char *humix,char *tempz,char *tempx);


//spi模块
//SPI初始化函数
void SPI_Config(void);
//SPI读写函数
unsigned char SPI1_Write_Read(unsigned char senddata);

//w25q64模块
//1、设备初始化函数
void W25Q64_Config(void);
//读取设备ID函数
unsigned short W25Q64_ReadID(void);
//写数据使能函数
void W25Q64_Write_Enable(void);
unsigned char W25Q64_Check_Busy(void);
void W25Q64_Erase_All_Chip(void);
unsigned int W25Q64_Read_Data(unsigned int wordaddr,unsigned char buff[],unsigned char len);
int W25Q64_Write_Data(unsigned int writeaddr,char *pbuff,unsigned short byteNum);

//ADC模块
//配置ADC电路——光敏电阻
void ADC1_Light_Config(void);
//开始采集的函数
unsigned short Get_ADC_Channel(unsigned int channel);
//通道数 + 采集时间
unsigned short Get_ADC_Average(unsigned int channel,char times);


//ESP8266模块
void uart2init(void);

//配置定时器5 实现定时一秒
void Timer5_Config(unsigned short prec,unsigned short peri);
void ProcessReceivedString(char *str);
void usart_sendstr(USART_TypeDef * USATRX , char * str,int size);
void setWifi(void);
void Send_Client_Data(void);
void Show_Client_Data(void);


//USART6模块
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
#define KEY_NONE 0xFF  // 定义一个无按键按下的状态码 
#define   COL_Pin_0  GPIO_Pin_2
#define   COL_Pin_1  GPIO_Pin_3
#define   COL_Pin_2  GPIO_Pin_7 
#define   COL_Pin_3  GPIO_Pin_11 
extern uint8_t key_value1;
char key_4x4_scan(void);
extern char passwd[128];


//lcd.h



//LCD重要参数集
typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				//LCD ID
	u8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	u16	 wramcmd;		//开始写gram指令
	u16  setxcmd;		//设置x坐标指令
	u16  setycmd;		//设置y坐标指令	 
}_lcd_dev; 	

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数
/////////////////////////////////////用户配置区///////////////////////////////////	 
#define USE_HORIZONTAL  	 0//定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转

//////////////////////////////////////////////////////////////////////////////////	  
//定义LCD的尺寸
#define LCD_W 240
#define LCD_H 320

//TFTLCD部分外要调用的函数		   
extern u16  POINT_COLOR;//默认红色    
extern u16  BACK_COLOR; //背景颜色.默认为白色

////////////////////////////////////////////////////////////////////
//-----------------LCD端口定义---------------- 

#define LED      13        //背光控制引脚
#define CS   2       //片选引脚
#define RS   7       //寄存器/数据选择引脚  
#define RST  3       //复位引脚

//QDtech全系列模块采用了三极管控制背光亮灭，用户也可以接PWM调节背光亮度
#define	LCD_LED PDout(LED) //LCD背光    		 
#define LCD_CS  PEout(CS)
#define LCD_RS  PEout(RS)
#define LCD_RST PEout(RST)
//如果使用官方库函数定义下列底层，速度将会下降到14帧每秒，建议采用我司推荐方法
//以下IO定义直接操作寄存器，快速IO操作，刷屏速率可以达到28帧每秒！ 

#define	LCD_CS_SET  LCD_CS=1 //GPIO_TYPE->BSRRL=1<<LCD_CS    //片选端口  	PB11
#define	LCD_RS_SET	LCD_RS=1 //GPIO_TYPE->BSRRL=1<<LCD_RS    //数据/命令  PB10	  
#define	LCD_RST_SET	LCD_RST=1 //GPIO_TYPE->BSRRL=1<<LCD_RST    //复位			PB12

 							    
#define	LCD_CS_CLR  LCD_CS=0 //GPIO_TYPE->BSRRH=1<<LCD_CS     //片选端口  	PB11
#define	LCD_RS_CLR	LCD_RS=0 //GPIO_TYPE->BSRRH=1<<LCD_RS     //数据/命令  PB10	 
#define	LCD_RST_CLR	LCD_RST=0 //GPIO_TYPE->BSRRH=1<<LCD_RST    //复位			  PB12

				


//画笔颜色
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
#define BROWN 			0XBC40 //棕色
#define BRRED 			0XFC07 //棕红色
#define GRAY  			0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	0X841F //浅绿色
#define LIGHTGRAY     0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 		0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE      	0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)
	    															  
void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(u16 Color);	 
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_DrawPoint(u16 x,u16 y);//画点
u16  LCD_ReadPoint(u16 x,u16 y); //读点
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

u16 LCD_RD_DATA(void);//读取LCD数据									    
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


//本测试程序使用的是模拟SPI接口驱动
//可自由更改接口IO配置，使用任意最少4 IO即可完成本款液晶驱动显示
/******************************************************************************
接口定义在lcd.h内定义，请根据接线修改并修改相应IO初始化LCD_GPIO_Init()
#define LCD_CTRL   	  	GPIOB		//定义TFT数据端口
#define LCD_LED        	GPIO_Pin_9  //PB9 连接至TFT -LED
#define LCD_RS         	GPIO_Pin_10	//PB10连接至TFT --RS
#define LCD_CS        	GPIO_Pin_11 //PB11 连接至TFT --CS
#define LCD_RST     	GPIO_Pin_12	//PB12连接至TFT --RST
#define LCD_SCL        	GPIO_Pin_13	//PB13连接至TFT -- CLK
#define LCD_SDA        	GPIO_Pin_15	//PB15连接至TFT - SDI
*******************************************************************************/

#define SCLK        14	//PB13--->>TFT --SCL/SCK
#define MISO        0	
#define MOSI        11	//PB15 MOSI--->>TFT --SDA/DIN

#define SPI_MOSI  PEout(MOSI)
#define SPI_SCLK  PEout(SCLK)
#define SPI_MISO  PDin(MISO)

//液晶控制口置1操作语句宏定义
#define	SPI_MOSI_SET  	SPI_MOSI=1 //LCD_CTRL->BSRR=SPI_MOSI    
#define	SPI_SCLK_SET  	SPI_SCLK=1 //LCD_CTRL->BSRR=SPI_SCLK    


//液晶控制口置0操作语句宏定义

#define	SPI_MOSI_CLR  	SPI_MOSI=0 //LCD_CTRL->BRR=SPI_MOSI    
#define	SPI_SCLK_CLR  	SPI_SCLK=0 //LCD_CTRL->BRR=SPI_SCLK    

void  SPIv_WriteData(u8 Data);

//fon.h
 
//常用ASCII表
//偏移量32
//ASCII字符集
//偏移量32
//大小:12*6

extern const unsigned char asc2_1206[95][12];
extern const unsigned char asc2_1608[95][16];
typedef struct 
{
       unsigned char Index[2];	
       char Msk[32];
}typFNT_GB16; 
//字体取模：宋体常规小四

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
void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p); //显示40*40 QQ图片
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



